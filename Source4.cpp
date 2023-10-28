#include <iostream>
#include "random_vector.h"
#include <list>
#include <map>

using namespace std;

int main()
{
	vector<int> v{ 0,1,3,4,5,6,7,8,9 };
	vector<string> vstr{ "one", "two","three", "four" };
	list<float> l{ 1.1f,2.2f,3.3f,4.4f };

	auto s = (v.begin()+3)[2];

	cout << " first function take contenair        " << get_random_element(v) << '\n';
	cout << " from function use iterator           " << get_random_element(v.begin(), 8) << '\n';
	cout << " first last function                  " << get_random_element(v.begin() + 1, v.end() - 1) << '\n';
	cout << " firs last for list                   " << get_random_element(l.begin(), l.end());
	cout << " first function take container string " << get_random_element(vstr) << '\n';



	cin.get();
	return 0;
}