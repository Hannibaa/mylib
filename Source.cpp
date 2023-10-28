#include <iostream>
#include "stringfunctionhelper.h"

#define print std::cout 
#define end_ '\n'

using namespace std;

int main()
{

	// CONDUCT TEST 
	std::string str = "abcdefghijklmnopqrstuvwxyz";
	std::wstring wstr = L"abcdefghijklmnopqrstuvwxyz";

	//reversing it 
	print << "Original string ..." << str << end_;
	print << "Reversed string ..." << Str::reverseString(str) << end_;
	wcout << L"Reversed string ..." << Str::reverseString(wstr) << end_;

	//get all digit that we need it in base B
	const int b = 12;
	print << "all digit for base " << b << " is : " << Str::digitOfBase(b) << end_;
	print << "all digit for base " << b+10 << " is : " << Str::digitOfBase(b+10) << end_;

	// IS STRING A NUMBER WRITEN IN BASE 'B'
	std::string str1 = "123233439"; // minimal base of that string?
	std::string str2 = "12333334444bbbal//*90()";

	print << " check if str number  " << Str::is_string_number<10>(str1) << end_;
	print << " check str2 is number " << Str::is_string_number<10>(str2) << end_;

	// Shift function test 

	print << " ----- check for Shifting function of string -------\n";
	print << "shift empty string : " << Str::shift_left_string("", 23) << end_;
	print << "shif these string " << end_;
	print << "shift left : " << Str::shift_left_string("123456", 3)<< end_;
	print << "shift right : " << Str::shift_left_string("123456", -3)<< end_;

	// Remove unuseful Zero from string number
	// 000023424243 = 2342443
	print << " ------------------------ test remove unusefull 0 from number ---------------\n";
	print << "000234200034300 = " << Str::remove_unusefullZero("000234200034300") << end_;
	print << "000000 = " << Str::remove_unusefullZero("0000000") << end_;
	print << "0 = " << Str::remove_unusefullZero("0") << end_;

	// test conversion from to any string kind 
	print << "------------------- test of conversion -------------------------------\n";
	wcout << L"convert str to wchar_t " << Str::to_char<wchar_t>(str) << end_;
	wstring wstr = L"Hello World "+0x2344;
	print << "convert to string char " << Str::to_char<char>(wstr) << end_;

	cin.get();
	return 0;
}