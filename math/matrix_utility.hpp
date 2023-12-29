#pragma once
#include "MyLib/Console_Library/escape_code.h"
#include <numbers>
#include <Eigen/Dense>
#include <MyLib/random_generator.h>


namespace matrix {

	template<typename NumberType, typename Matrix>
	Matrix convert_to(const Matrix& m) {

	}

	template<typename _Func> // we can added some concepts about function f.
	Eigen::MatrixXd make_matrixd(int i, int j, _Func f) {

		Eigen::MatrixXd m(i, j);

		for (int k = 0; k != i; ++k)
			for (int l = 0; l != j; ++l)
				m(k, l) = f(k, l);

		return m;
	}

	template<typename Matrix, typename Comment>
	void print_matrix(const Matrix& m, const Comment comment = "") {

		Print_(color::Green, comment) << end_;
		Print_(color::Fuchsia, "{") << end_;
		Print_(color::Red, m) << end_;
		Print_(color::Fuchsia, "}") << end_;

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Print matrix in text file temp:
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename Matrix, typename Comment>
	void print_matrix(std::ofstream& os, const Matrix& m, const Comment comment = "") {

		os << comment << end_
		   << "{"
		   << m << end_
		   << "}\n";

	}



	template<typename Matrix, typename T = typename Matrix::value_type>
	Matrix make_matrixX(const T& min,
		                const T& max, int raw, int col) {

		Matrix m(raw, col);

		RNG::RG<T> rg(min, max);

		for (int i = 0; i != raw; ++i)
			for (int j = 0; j != col; ++j)
			{
				if constexpr (std::is_floating_point<T>::value)
					m(i, j) = rg(0.1f);
				else
					m(i, j) = rg();
			}

		return m;
	}

	template<typename T, int raw, int col>
	Eigen::Matrix<T, raw, col> make_random_matrix(T min, T max) {

		Eigen::Matrix<T, raw, col> m;

		RNG::RG<T> _random(min,max);

		for(int i = 0 ; i != raw ; ++i)
			for (int j = 0; j != col; ++j)
			{
				if constexpr (std::is_floating_point_v<T>)
					m(i, j) = _random(0.1);
				else
					m(i, j) = _random();
			}
		return m;
	}

}