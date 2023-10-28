#include <iostream>
#include "quadtree_utility.h"

using namespace std;

template<typename T>
struct Point {
	T x;
	T y;
};

int main()
{
	// Rect<float*> rect; // type is not arithmetic
	Rect<int> irect(10,10,10,10);
	Rect<float> frect(10.45f,10.2f,10.44f,10.01f);

	cout << irect << endl;
	cout << frect << endl;
	cout << " -- frect as int --\n";
	cout << frect.as<int>() << endl;

	Point<float> p = { 15.5f,12.3f },
		          p2 = {22.f,24.3f} ;

	Point<int> ip = { 12,14 },
		       ip2 = { 22,30 };

	if (irect.contain(ip2)) cout << " point inside rectangle \n";else cout << " point out side rectangle \n";
	if (frect.contain(p)) cout << " point inside rectangle \n";	else cout << " point out side rectangle \n";

	//irect.clear();
	//cout << "-- irect is cleared \n";
	//cout << irect << endl;

	SubRects<float> fsrect(frect, 5, 3);
	cout << fsrect;

	cin.get();
	return 0;
}