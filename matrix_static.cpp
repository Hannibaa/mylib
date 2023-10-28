#include <iostream>
#include "C:\Users\Acer\source\MyLib\matrix_static.h"

#define end_   '\n'
#define line_   std::cout << "---------------------------------------------------------------------\n"
#define wait_  std::cin.get()
#define print  std::cout 

using namespace std;



int main()
{
	matrix::Matrix<int, 2, 2> mat;

	mat(0, 0) = 23;
	mat(1, 1) = 11;
	mat(0, 1) += mat(0, 0) * mat(1, 1);
	mat(1, 0) =  3;

	printMat(mat);


	cin.get();
	return 0;
}