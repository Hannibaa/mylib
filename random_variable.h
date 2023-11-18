#pragma once
#include "MyLib\random_generator.h"
#include <chrono>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//           GENERALIZATION OF RANDOM VARIABLE EACH TIME WE CALL IT 
//           GENERALIZATION OF RANDOM VARIABLE CHANGED RANDOMLY EVERY DURATION FO TIME
//           
//           UNDER NAMESPACE namespace RV 'Random Variable'
//           
////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace RV {

	////////////////////////////////////////////////////////////////////////////////////////
	//
	//        RANDOM VARIABLE GENERALIZED 
	//        RANDOM VARIABLE VECTORIZED.
	//
	////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class RV {

		RNG::RG<T> random;

	public: 
		RV():RV(T(0), T(1)) {}

		RV(T min, T max)
			: random{min,max}
		{}

		operator T() {
			return random();
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////
	//
	//            RANDOM VECTOR 
	//
	////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class RVec {

		std::vector<T> m_vector;
		RNG::RG<size_t> random;

	public:
		//RVec()
		//	:m_vector{}
		//    , random{}
		//{}

		RVec(const std::vector<T>& vec) 
			: m_vector{vec}
			, random{0,vec.size() - 1}
		{}

		template<size_t N>
		RVec(const std::array<T,N>& Array)
			:random{0,N - 1}
		{
			for (auto& element : Array) m_vector.emplace_back(element);
		}

		RVec(T* Array, size_t N)
			:random{ 0, N - 1 }
		{
			for (size_t i = 0; i != N; ++i) m_vector.emplace_back(Array[i]);
		}

		template<typename...Ts>
		RVec(const Ts&...ts)
			: random{ 0,sizeof...(Ts) - 1 }
		{
			static_assert(sizeof...(Ts) != 0, "there are no value");
			int damn[] = { ((void)m_vector.push_back(T(ts)), 0)... };
		}

		T operator() () {
			return m_vector[random()];
		}

		void push_back(const T& value) {
			m_vector.push_back(value);
			random.setRange(0, m_vector.size() - 1);
		}

	};


	///////////////////////////////////////////////////////////////////////////////////////////
	//
	//			SMOOTH RANDOM VARIABLE         
	// 
	//////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class SRV {  // Smooth Random Variable
		T x;
		T m_initial;
		T m_target;
		T m_step;
		T m_min;
		RNG::RG<T> random;

		using Float = typename std::conditional<std::is_integral<T>::value, T, float>::type;

	public:
		SRV(T initial, T target, T step)
			:random{ initial,target }
			, x{ initial }
			, m_initial{ initial }
			, m_target{ target }
			, m_step{ step }
			, m_min {initial}
		{}

		SRV(T initial,T target,T step,  T min, T max) 
			:random{min,max}
			, x{initial}
			, m_initial{ initial }
			, m_target{target}
			, m_step{step}
			, m_min{min}
		{}

		SRV() : SRV(T{}, T{}, T{}) {};
		SRV(const SRV&) = default;

		void setStep(T step) {
			m_step = step;
		}

		void start_value(T value) {
			x = std::clamp(value, m_initial, m_target);
		}

		operator T() {
			update();
			return x;
		}

	private:
		void update() {

			if (m_initial == m_target) {
				m_target = m_initial + m_step;
			}
			
			if (m_initial < m_target) {
				x += m_step;
				if (x > m_target) {
					m_initial = m_target;
					m_target  = random();
					//std::cout << "----up----" << m_target << '\n';
				}
			}

			if (m_initial > m_target) {
				x -= m_step;

				if (x < m_target) {
					m_initial = m_target;
					m_target  = random();
					//std::cout << "-----down----" << m_target << '\n';
				}
			}
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////
    //
    //			SMOOTH RANDOM VARIABLE VECTOR     
    // 
    //////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class SRVVec {  // Smooth Random Variable
		T          x;
		T          m_initial;
		T          m_target;
		T          m_step;
		RVec<T>    rVector;

	public:

		SRVVec(const std::vector<T>& _vector, T step)
			: rVector{_vector}
			, m_step{step}
		{
			x = _vector[0] ;
			m_initial = rVector() ;
			m_target  = rVector() ;
		}

		void setStep(T step) {
			m_step = step;
		}

		operator T() {
			update();
			return x;
		}

	private:
		void update() {

			if (m_initial == m_target) {
				m_target = m_initial + m_step;
			}

			if (m_initial < m_target) {
				x += m_step;
				if (x > m_target) {
					m_initial = m_target;
					m_target = rVector();
				}
			}

			if (m_initial > m_target) {
				x -= m_step;

				if (x < m_target) {
					m_initial = m_target;
					m_target = rVector();
				}
			}
		}
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//      RANDOM VARIABLE WITH TIMING.
	//      RVTime(min,max,duration_millisec).  
	//      each duration defined we gave as random value between min and max
	//      we can change duration and all other parameter.           
	//              
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class RVTime {

		T x;
		T m_max;
		T m_min;
		std::chrono::milliseconds m_duration_ms;
		std::chrono::steady_clock::time_point tp{};
		RNG::RG<T> m_random;

	public:
		RVTime(const RVTime<T>&) = default;
		RVTime<T>& operator=(const RVTime<T>&) = default;

		RVTime() :RVTime(T{}, T{ 1 }, 1s) {}
		RVTime(T min, T max, std::chrono::milliseconds _duration)
			: m_random{min,max}
			,m_max{max}
			,m_min{min}
			, m_duration_ms{_duration}
		{
			tp = std::chrono::steady_clock::now();
			x = m_random();
		}

		void setDuration(std::chrono::milliseconds  _duration) {
			m_duration_ms = _duration;
		}

		constexpr T max_() const { return m_max; }
		constexpr T min_() const { return m_min; }

		operator T() {

			if (std::chrono::steady_clock::now() - tp < m_duration_ms)
			{
				return x;
			}
			else {
				x = m_random();
				tp = std::chrono::steady_clock::now();
			}

			return x;

		}

	};

}


