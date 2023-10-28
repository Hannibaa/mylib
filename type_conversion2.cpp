#include <iostream>
#include <thread>
#include <type_traits>
#include "MyLib/Console_Library/escape_code.h"
#include ""

/* 
         HERE WE GET TO GENERALIZE OUT EXAMPLE OF TYPE CONVERSION 
		 FOR ANY TYPE AND PACK OF ARGUMENT OR PARAMETER

*/

using namespace std;

// we making a type that have conversion function return roundemly any value randomly
// we can generalize in header file by NsValue 


int main()
{
	NsValue  t1{ 100.f,300.f };

	NsValue t3(100, 200, 400);

	NsValue t2{ {100,58,89} };

	int count_1{}, count_2{};

	for (int i = 0; i < 10; ++i) {

		int t_1 = t1;
		print_ << "the value of t1 is             " << t_1 << end_;

		if (t_1 == 100) ++count_1; else ++count_2;

		std::this_thread::sleep_for(200ms);


		int t_2 = t1;
		print_ << "the value of t1 after 200ms is " << t_2 << end_;
		if (t_2 == 100) ++count_1; else ++count_2;
	}

	newline_;
	Print_(color::Green, "the value 100 appear : ") << count_1 << " times\n";
	Print_(color::Green, "the value 400 appear : ") << count_2 << " times\n";

	cin.get();
	return 0;
}