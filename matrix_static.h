#pragma once
#include <array>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////////////
//
//      MATRIX CLASS NxM.    
//      1. define operator +
//      2. define operator - 
//      3. define operator == ;
//      4. define operator *;
//
////////////////////////////////////////////////////////////////////////////////////////////

namespace Matrix {

	template<typename T, size_t N, size_t M>
	class Matrix {
		static_assert(std::is_scalar<T>::value, "T type should be scalar type");

		std::array<T, N* M> Mat;

	public:
		Matrix() :Mat{} {}

		Matrix(std::initializer_list<T> mat)
		{
			// calculate from size and N, M;
			auto real_size = N * M;

			for (size_t i = 0 ; i != N ; ++i)
				for (size_t j = 0; j != M; ++j)
				{
					if (i * M + j < mat.size())
						Mat[i * M + j] = *(mat.begin() +i * M + j);
					else
						Mat[i * M + j] = T{};
				}

		}

		T& operator()(size_t i, size_t j) {
			return Mat[i * M + j];
		}

		T operator()(size_t i, size_t j) const {
			return Mat[i * M + j];
		}

		std::pair<size_t, size_t> size() const {
			return std::make_pair(N, M);
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//          OPERATOR * AND +
	//          WE SITE RESTRICTION OBOUT * AND +
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, size_t N, size_t M, size_t L>
	Matrix<T, N, M> constexpr operator* (const Matrix<T, N, L>& m1, const Matrix<T, L, M>& m2)
	{
		Matrix<T, N, M> m;

		for (int i = 0; i != N; ++i)
		{
			for (int j = 0; j != M; ++j)
			{
				for (int k = 0; k != L; ++k) m(i, j) += m1(i, k) * m2(k, j);
			}
		}

		return m;
	}

}



/////////////////////////////////////////////////////////////////////////////////////////////////
//
//                      PRINTING A MATRIX 
//
/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T, size_t N, size_t M>
void printMat(const Matrix::Matrix<T, N, M>& mat) {
	for (size_t i = 0; i != N; ++i)
	{
		std::cout << "{ ";
		for (size_t j = 0; j != M; ++j) {
			std::cout << mat(i, j) << "  ";
		}
		std::cout << " }\n";
	}
}
