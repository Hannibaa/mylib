#include <iostream>
#include "C:\Users\Acer\source\MyLib\File_data.h"

#define end_   '\n'
#define line_   std::cout << "---------------------------------------------------------------------\n"
#define wait_  std::cin.get()
#define print  std::cout 

using namespace std;


int main()
{
	string filename = "photo15.bmp";

	auto v = File::makeGraphicalFile<float>(filename, 1000, 700);

	print << "size " << v.size() << end_;

	for (int i = 0; i < 100; ++i) {
		print << "[" << v[i].first << " , " << v[i].second << end_;

		if (v[i].second < 0) cin.get();
	}



	cin.get();
	return 0;
}