// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	double x = 1.5, dx = 0.25;
	int i = 0;
	while (x > 1.) {
		x = x - dx;
		dx = dx / 2.;
		i++;
	}
	cout << i << endl;
	float x2 = 1.5, dx2 = 0.25;
	int i2 = 0;
	while (x2 > 1) {
		x2 = x2 - dx2;
		dx2 = dx2 / 2.;
		i2++;
	}
	cout << i2 << endl;
	double x3 = 1, dx3 = 0.5,last_dx3;
	while (x3 + dx3 > 1.) {
		last_dx3 = dx3;
		dx3 = dx3 / 2.;
	}
	cout << last_dx3 << endl;
	float x4 = 1, dx4 = 0.5, last_dx4;
	while (x4 + dx4 > 1) {
		last_dx4 = dx4;
		dx4 = dx4 / 2.;
	}
	cout << last_dx4 << endl;
    return 0;
}

