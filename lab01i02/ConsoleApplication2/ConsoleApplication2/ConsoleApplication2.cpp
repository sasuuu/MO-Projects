// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

double fun(double x) {
	double result;
	result = (- exp(-x) + 1) / x;
	return result;
}

double szereg(double x) {
	double result=1;
	int i = 1;
	double wyraz=1;
	while(fabs(wyraz)+1.0>1.0) {
		wyraz = wyraz * (-x / ((double)i+1.));
		result += wyraz;
		i++;
	}
	return result;
}

int main()
{
	fstream fs;
	double x,result;
	double check_x,c;
	fs.open("dane.txt",ios::in);
	cout << setw(30) << setprecision(20)<< setiosflags(ios::left) <<"x" << setw(30) << setprecision(20) << "fun(x)" << setw(30) << setprecision(20) << "(1-exp(-x))/x" << "Blad wzgledny: " << endl;
	while (!fs.eof()) {
		fs >> x;
		fs >> check_x;
		if (x < 0.25) {
			result = szereg(x);
			c = abs((result - check_x) / check_x);
		}
		else {
			result = fun(x);
			c = abs((result - check_x) / check_x);
		}
			cout << setw(30) << setprecision(20)<<setiosflags(ios::left)<<scientific;
		cout<<x << setw(30) << setprecision(20) << result  << setw(30) << setprecision(20) << check_x << setw(30) << setprecision(20) << c << endl;
	}
	fs.close();
    return 0;
}

