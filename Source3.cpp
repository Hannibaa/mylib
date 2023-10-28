#include <iostream>
#include "random_walk.h"
#include "C:\Users\Acer\source\SFML Projects\Lib utility\periodic_var.h"
//#include "random_generator.h"

using namespace std;

int main()
{
	//RG<void> r;
	RW1<float> x(40.f, { 0.f,100.f }, { 0.05f,0.1f }, { 500ms,1s });

	//Periodic<float> y(1.f, 2s);


	while (true) {

		cout << " x " << x <<  endl;

		//if (cin.get() == 'e') break;
	}

	cin.get();
	return 0;
}
