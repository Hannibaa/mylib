#include <iostream>
#include "c:\Users\Acer\source\MyLib/Console_Library/escape_code.h"
#include <MyLib/static_vector.h>

template<typename Container>
void print_vec(const Container C) {

	int i{};
	print_ << "container of size [" << C.size() << "]" << end_;
	for (auto element : C)
		print_ << CELL(5, left, ++i) << CELL(15, left, element) << end_;

}


int main() {

	static_vector<std::string, 3> vec_str;

	print_ << "capacity " << vec_str.capacity() << " size " << vec_str.size() << end_;

	vec_str.push_back("first"); 
	vec_str.push_back("second");
	vec_str.push_back("third");
	vec_str.push_back("forth");

	print_vec(vec_str);

	print_ << "changing second composent " << end_;
	vec_str[1] = "SECOND";

	print_vec(vec_str);


	wait_;
	return 0;
}






//int main()
//{
//	static_vector<int, 10> vec(3);
//	static_vector<float, 4> fvec{ 2.0f, 4.f, 6.6f, 7.1f     ,6.66f,10.3f };
//
//	print_ << "capacity of vector : " << vec.capacity() << end_;
//	print_vec(vec);
//	print_ << "capactiy of float vec " << fvec.capacity() << end_;
//	print_vec(fvec);
//	// insert some element at ...
//
//	vec.push_back(45);
//	fvec.push_back(55.6);
//
//	print_vec(vec);
//
//	print_ << "capacity " << fvec.capacity() << " size " << fvec.size() << end_;
//	print_vec(fvec);
//
//	float sum{};
//	for (int i = 0; i < fvec.size(); ++i)
//		sum += fvec[i];
//
//	print_ << COLOR(color::Green, sum) << end_;
//
//	wait_;
//	return 0;
//}