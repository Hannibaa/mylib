#include <iostream>
#include <vector>
#include "MyLib/Console_Library/escape_code.h"
#include <MyLib/function_utility.h>


//           Type comparing functions and mesure 
using namespace std::literals;

int main()
{
	std::vector v1{ 23.4,44.3,55.5 };
	std::vector v2{ 23,44,55 };

	// Function::Indicator(343, v1);  // compile Error not same type int and double
	Function::Indicator(44, v2);

	// using increment in float : 
	float f = 3.334f;
	double d = 23.4445454;
	print_ << "f = " << f << ", d = " << d << end_;

	for (int i = 0 ; i < 100 ; ++i){
		print_ << "increment : " << Function::float_inc(f,100) << end_;
		print_ << "double inc: " << Function::float_inc(d,100i16) << end_;
		newline_; wait_;
	}
	
	print_ << "f = " << f << ", d = " << d << end_;

	wait_;
	return 0;
}