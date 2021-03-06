// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

double fun(double x) { return sin(x / 4)*sin(x / 4) - x; }
double fun1(double x) { return tan(2 * x) - x - 1; }
double funpochodna(double x) { return (1 / 4)*sin(x / 2) - 1; }
double fun1pochodna(double x) { return 2 / (cos(2 * x)*cos(2 * x)) - 1; }
double funpochodnapic(double x) { return sin(x / 4)*cos(x / 4) / 2; }
double fun1pochodnapic(double x) { return (2 / pow(cos(2 * x), 2)); }
double funpic(double x) { return sin(x / 4)*sin(x / 4); }
double fun1pic(double x) { return tan(2 * x) - 1; }

void picard(double x, double(*fun)(double), double(*fun2)(double), double(*fun3)(double)) {
	cout << "Metoda Picarda:" << endl;
	cout << setw(6) << "i" << setw(15) << "x" << setw(15) << "fun(x)" << setw(15) << "e" << setw(15) << "residuum" << endl;
	double ex;
	double efun;
	double tolx = 1e-8;
	double tolfun = 1e-8;
	int i = 0;
	double prevx = 0;
	double nxtx = x;
	int imax = 1000;
	do {
		do {
			prevx = nxtx;
			if (abs(fun3(prevx)) > 1) break;
			nxtx = fun2(prevx);
			i++;
			efun = abs(fun(nxtx));
			ex = abs(nxtx - prevx);
			cout << setw(6) << i << setw(3)<<"|"<<setw(15) << nxtx << setw(3) << "|" << setw(15) << fun(nxtx)<<setw(3) << "|" << setw(15) << ex << setw(3) << "|" << setw(15) << efun <<  endl;
		} while (ex > tolx && i < imax);
		if (abs(fun3(prevx)) > 1) {
			cout << "Metoda rozbiezna!!!" << endl;
			break;
		}
	} while (efun > tolfun && i < imax);
}

void bisekcja(double xx, double y, double(*fun)(double)) {
	cout << "Metoda bisekcji:" << endl;
	cout << setw(6) << "i" << setw(15) << "x" << setw(15) << "fun(x)" << setw(15) << "e" << setw(15) << "residuum" << endl;
	double ex;
	double efun;
	double tolx = 1e-8;
	double tolfun = 1e-8;
	int i = 0;
	double a = xx;
	double b = y;
	double x;
	int imax = 1000;
	if ((fun(a)<0 && fun(b)<0) || (fun(a)>0 && fun(b)>0)) {
		cout << "Wartosci na koncach przedzialu musza byc roznego znaku!!!" << endl;
		return;
	}
	do {
		do {
			i++;
			x = (a + b) / 2.0;
			efun = abs(fun(x));
			ex = abs((b - a) / 2.0);
			if ((fun(a)<0 && fun(x)>0) || (fun(a)>0 && fun(x)<0)) b = x;
			else a = x;
			cout << setw(6) << i << setw(3) << "|" << setw(15) << x << setw(3) << "|" << setw(15) << fun(x) << setw(3) << "|" << setw(15) << ex << setw(3) << "|" << setw(15) << efun <<  endl;
		} while (ex > tolx && i < imax && efun!=0);
	} while (efun > tolfun && i < imax);
}

void newton(double x, double(*fun)(double), double(*fun2)(double)) {
	cout << "Metoda Newtona:" << endl;
	cout << setw(6) << "i" << setw(15) << "x" << setw(15) << "fun(x)" << setw(15) << "e" << setw(15) << "residuum" << endl;
	double ex;
	double efun;
	double tolx = 1e-8;
	double tolfun = 1e-8;
	int i = 0;
	double prevx = 0;
	double nxtx = x;
	int imax = 1000;
	do {
		do {
			prevx = nxtx;
			if (fun2(prevx) == 0) break;
			nxtx = prevx - (fun(prevx) / fun2(prevx));
			i++;
			efun = abs(fun(nxtx));
			ex = abs(nxtx - prevx);
			cout << setw(6) << i << setw(3) << "|" << setw(15) << nxtx << setw(3) << "|" << setw(15) << fun(nxtx) << setw(3) << "|" << setw(15) << ex << setw(3) << "|" << setw(15) << efun << endl;
		} while (ex > tolx && i < imax);
		if (fun2(prevx) == 0) {
			cout << "Pochodna wynisla 0!!!" << endl;
			break;
		}
	} while (efun > tolfun && i < imax);
}

void siecznych(double x,double x2, double(*fun)(double)) {
	cout << "Metoda Siecznych:" << endl;
	cout << setw(6) << "i" << setw(15)<<"x" << setw(15) <<"fun(x)" << setw(15) <<"e" << setw(15) <<"residuum" << endl;
	double ex;
	double efun;
	double tolx = 1e-8;
	double tolfun = 1e-8;
	int i = 0;
	double prevx = x2;
	double prevx2 = 0;
	double nxtx = x;
	int imax = 1000;
	do {
		do {
			prevx2 = prevx;
			prevx = nxtx;
			nxtx = prevx - (fun(prevx) / ((fun(prevx) - fun(prevx2)) / (prevx - prevx2)));
			i++;
			efun = abs(fun(nxtx));
			ex = abs(nxtx - prevx);
			cout << setw(6) << i << setw(3) << "|" << setw(15) << nxtx << setw(3) << "|" << setw(15) << fun(nxtx) << setw(3) << "|" << setw(15) << ex << setw(3) << "|" << setw(15) << efun << endl;
		} while (ex > tolx && i < imax && efun != 0);
	} while (efun > tolfun && i < imax);
}

int main()
{
	// Funkcja 1
	cout << "Funkcja 1:" << endl;
	picard(100, fun, funpic,funpochodnapic);
	bisekcja(2, -4, fun);
	newton(-0.2, fun, funpochodna);
	siecznych(-3,-1.7, fun);
	// Funkcja 2
	cout << "Funkcja 2:" << endl;
	picard(-1.7, fun1, fun1pic, fun1pochodnapic);
	bisekcja(0.3,0.7, fun1);
	newton(-0.3, fun1, fun1pochodna);
	siecznych(0.2, 1.2, fun1);
    return 0;
}

