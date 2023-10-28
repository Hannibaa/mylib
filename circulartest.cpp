#include <iostream>
#include "circular.h"

using namespace std;

int main()
{
	for (int i = 0; i < 10; i++)
	{
		cout << circ_add(60, i*10) << endl;
		int a = 60 + i * 20;
		cout << " circular of 360 " << i * 50 + 300 << " is " << circular(a) << endl;
		cout << " Period 111 : " << circular<int, 111>(a) << endl;
		cout << " Period 120 : " << circular<int, 120>(a) << endl;
		cin.get();
	}

	



	cin.get();
	return 0;
}