#pragma once
#include <string>
#include <iostream>

using namespace std;

class Int { // Redesigne Natural Number or ...

	int i;

public:
	Int() = default;
	explicit Int(int k) : i(k) {};

	int& operator ()() { return i; }

	/*operator int() {
		return i;
	}*/

	const string& operator () (int base) { // convert to base 
		stringstream s;
		s << i;

		return s.str();
	}

	Int operator + (const Int& rhs)  { return Int(i + rhs.i); }
	Int operator + (const int& rhs)  { return Int(i + rhs);   }
	Int operator - (const Int& rhs)  { return Int(i - rhs.i); }
	Int operator - (const int& rhs ) { return Int(i - rhs );  }
	//Int operator / (const Int& rhs)     { return Int(i / rhs.i); }
	double operator / (const Int& rhs) { return double(i) / double(rhs.i); }
	Int operator * (const int& scalar) { Int tmp = Int(this->i * scalar); return tmp; }
	Int operator * (const Int& rhs) { return Int(i * rhs.i); }
	friend int operator + (int& n, Int& I);

	// Theory of Number and Analytical Number Theory ...
	string toHex() {};
	string toBin() {};
	string String() {};
	char* c_str() {};
	Int& reverse() {};
	void phi() {};
	bool is_prime() { return false; };
	void number_divisor() {};
	void is_square() {};
	void print() { cout << i << endl; }

	friend ostream& operator << (ostream& os, Int& i);
	friend Int operator + (const int&, Int&);
	friend Int operator * (const int&, Int&);
	friend Int operator - (const int&, Int&);
	//friend Int operator - (const Int&, int&);

};

Int operator + (const int& n, Int& I) {
	return Int(n + I.i);

}

Int operator - (const int& n, Int& I) {
	return Int(n - I.i);

}

//Int operator - (const Int& I, int& n) {
//	return Int(I.i - n);
//}

Int operator * (const int& n, Int& I) {
	return Int(n * I.i);
}

ostream& operator << (ostream& os, Int& i) {
	os << i.i;
	return os;
}
