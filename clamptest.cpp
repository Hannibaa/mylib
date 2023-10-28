#include <iostream>
#include "clamp_value.h"

using namespace std;

int main()
{
	ClampValue<int> a(10, 20);
	ClampValue<float> b(-10.23f, 2.1f);
	ClampValue<int> c(2, 4);


	b = -0.3f;

	cout << b << endl;
	cout << a << endl;
	cout << "-----------------------\n";
	for (int i = 0; i < 10; i+=1) {
		a = a + i;
		b = b - float(i);
		
		cout << " a " << a << endl;
		cout << " b " << b << endl;
		cout << " c " << c << endl;c = c + 1;
		cin.get();
	}



	cin.get();
	return 0;
}