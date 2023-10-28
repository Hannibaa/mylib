#include <iostream>

using namespace System;
using namespace System::IO;
using namespace System::Collections;

#define end_     '\n'
#define newline_  std::cout << '\n'


int main() {

	array<int>^ arr_int = { 33,55,66 };
	array<String^>^ arr_string = { "one" , "two" , "three" };
	array<char>^ arr_char = { 'A', 'B' , 'C' , 'C' };


	for each (int e in arr_int) {
		std::cout << e << " ";
	}

	newline_;
	

	for each (String ^ s in arr_string) Console::WriteLine(s);
	newline_;

	arr_string->Reverse(arr_string);
	arr_string->Resize(arr_string,2);
	std::cout << "length of new array resized : " << arr_string->Length << end_;
	for (int i = 0; i < arr_string->Length; ++i) {
		Console::WriteLine(arr_string[i]->Length);
		Console::WriteLine(arr_string[i]);
	}

	std::cin.get();
	return 0;
}