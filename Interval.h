#pragma once
#include <iostream>
#include <type_traits>
#include <limits>
#include <vector>

namespace Math {

	template<typename T>
	class Interval {
		T lowerBound;
		T upperBound;
		static_assert(std::is_arithmetic<T>::value, "T should be arithmetic type");

		void Swap() {
			if (lowerBound > upperBound) std::swap(lowerBound, upperBound);
		}

	public:
		Interval()
			:lowerBound{std::numeric_limits<T>::lowest()}
			,upperBound{std::numeric_limits<T>::max()}
		{}

		Interval(const T& _lower, const T& _upper)
			:lowerBound{ _lower }
			,upperBound{ _upper }
		{
			Swap();
			// We should handle exception here;
		}

		void lowerValue(const T& value) {
			lowerBound = value;
			Swap();
		}
		void upperValue(const T& value) {
			upperBound = value;
			Swap();
		}

		void centerValue(const T& value) {
			// three case 
			// 1. value in center of interval
			if (value <= lowerBound) { lowerBound = value; return; }
			if (value >= upperBound) { upperBound = value; return; }
			// 2. value upper or equal to upper or lower bound
			if (upperBound - value > value - lowerBound) lowerBound = value; else upperBound = value;
		}

		T upperValue() const { return upperBound; }
		T lowerValue() const { return lowerBound; }

		bool contain(T value)           const { return value <= upperBound && value >= lowerBound; }
		bool contain(const Interval& I) const { return contain(I.lowerBound) && contain(I.upperBound); }

		// subdivition of interval to 2 or n equals intervals
		auto subdivision() {
			std::array<Interval, 2> 
				vInt{ Interval(lowerBound,(lowerBound + upperBound)/T(2))
				     ,Interval((lowerBound + upperBound) / T(2),upperBound) };

			return vInt;
		}

		auto subdivision(size_t n) {
			std::vector<Interval> vInt;
			for (int i = 0; i < n; ++i)
			{
				T a = lowerBound + (T(i) * (upperBound - lowerBound) / T(n));
				T b = lowerBound + (T(i + 1) * (upperBound - lowerBound) / T(n));
				vInt.push_back(Interval(a, b));
			}

			return vInt;
		}

		template<size_t n>
		auto constexpr subdivision() {
			std::array<Interval, n> vInt;
			for (int i = 0; i < n; ++i)
			{
				T a = lowerBound + (T(i) * (upperBound - lowerBound) / T(n));
				T b = lowerBound + (T(i+1) * (upperBound - lowerBound) / T(n));
				vInt[i] = Interval(a, b);
			}

			return vInt;
		}

		// defining union and intersection of two interval by + and -; between same type
		// 1. - for Intersection
		Interval operator - (const Interval& I) {
			if (upperBound < I.lowerBound || I.upperBound < lowerBound) return Interval{ T{} ,T{} };
			Interval J;
			J.upperBound = (upperBound < I.upperBound) ? upperBound : I.upperBound;
			J.lowerBound = (lowerBound > I.lowerBound) ? I.lowerBound : lowerBound;
			return J;
		}
		//2. + for Union
		Interval operator + (const Interval& I) {
			if (upperBound < I.lowerBound || I.upperBound < lowerBound) return Interval{ T{} ,T{} };
			Interval J;
			J.upperBound = (upperBound < I.upperBound) ? I.upperBound : upperBound;
			J.lowerBound = (lowerBound > I.lowerBound) ? I.lowerBound : lowerBound;
			return J;
		}

	};

	template<typename T>
	std::ostream& operator << (std::ostream& os, const Interval<T>& I) {
		os << "[ " << I.lowerValue() << " , " << I.upperValue() << " ]\n";
		return os;
	}

	std::ostream& operator << (std::ostream& os, const Interval<char>& I) {
		os << "[ " << (int)I.lowerValue() << " , " << (int)I.upperValue() << " ]\n";
		return os;
	}


	/*
		 define useful Interval in intInt, charInt, floatInt, doubleInt, uintInt, ucharInt, shortInt,
		 ushortInt, lintInt, ulintInt ,
	*/
	template<typename T>
	Interval<T> WholeInt{ std::numeric_limits<T>::min(), std::numeric_limits<T>::max() };

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//     INTERVAL MORE CONCRETE 
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, T min, T max>
	class _Interval : public Interval<T> {
		static_assert(min != max, "min and max should be differente");
		void lowerValue(const T&);
		void upperValue(const T&);
	public:
		_Interval():Interval<T>(min,max){}

		T lower() const { return Interval<T>::lowerValue(); }
		T upper() const { return Interval<T>::upperValue(); }
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//        Set template can be use for help in Interval also.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, template<typename,typename...>class SET>
	class Set {

		SET<T> set;

		T maxelement;
		T minelement;

	public:

		template<typename...Ts>
		Set(const Ts& ...ts) 
			:set(ts...)
		{

		}

		bool operator()(T x) {
			return set.contain(x);
		}

		bool operator()(T x)const {
			return set.contain(x);
		}
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    INTERVALS UNION : GENERALIZATION OF INTERVAL
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	class Intervals {
		std::vector<Interval> U_Interval;

	public:

		void interval_analyser() {
			// this function call every time when there are rearrangement of interval
			// always call in the begining of constructor to arrange the intervals.
		}
	};
}