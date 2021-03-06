// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

void odejmowanieWektorow(double* x, double* y, int size, double* res) { for (int i = 0; i < size; i++) res[i] = x[i] - y[i]; }

void fun(double* x, double* res) {
	int i;
	for (i = 0; i < 3; i++) {
		switch (i) {
		case 0:
			res[i] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 2;
			break;
		case 1:
			res[i] = x[0] * x[0] + x[1] * x[1] - 1;
			break;
		case 2:
			res[i] = x[0] * x[0] - x[1];
			break;
		}
	}
}

double normmax(double* x, int size) {
	int i;
	double normmax = x[0];
	for (i = 1; i < size; i++) if (abs(x[i]) > abs(normmax)) normmax = x[i];
	return normmax;
}

double residuum(double* x, int size) {
	double* res;
	double residuum;
	res = new double[size];
	fun(x, res);
	residuum = abs(normmax(res, size));
	delete[] res;
	return residuum;
}

double estymator(double* x,double* y, int size) {
	double* res;
	double estymator;
	res = new double[size];
	odejmowanieWektorow(x, y, size, res);
	estymator = abs(normmax(res, size));
	delete[] res;
	return estymator;
}

void pokaz(double *tab, int size) {

	for (int i = 0; i < size; i++) {
		cout << setw(15) << *(tab + i) << " ";
	}
}

void mjakob(double* x,double** res) {
	double mianownik = -4.0 * x[2] * x[0] * (1.0 + 2.0*x[1]);
	if (mianownik == 0) { 
		cout << "Nie mozna obliczyc wyznacznika!!!!" << endl;
		return;
	}
	double det = 1.0 / mianownik;
	int i;
	for (i = 0; i < 9; i++) {
		switch (i) {
		case 1:
			res[(int)(i/3)][i%3] = (-2.0*x[2])*det;
			break;
		case 2:
			res[(int)(i / 3)][i % 3] = (-4.0*x[2]*x[1])*det;
			break;
		case 4:
			res[(int)(i / 3)][i % 3] = (-4.0*x[2]*x[0])*det;
			break;
		case 5:
			res[(int)(i / 3)][i % 3] = (4.0*x[2]*x[0])*det;
			break;
		case 6:
			res[(int)(i / 3)][i % 3] = (-2.0*x[0]-4.0*x[0]*x[1])*det;
			break;
		case 7:
			res[(int)(i / 3)][i % 3] = (2.0*x[0]+4.0*x[0]*x[1])*det;
			break;
		default:
			res[(int)(i / 3)][i % 3] = 0;
		}
	}
}

void mnozenie(double** x, double* y, double *res) {
	int i, j;
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) res[i] += x[i][j] * y[j];
}

void kopiuj(double* x, double *y, int size) { for (int i = 0; i < size; i++) y[i] = x[i]; }

int main()
{
	double* xn;
	double* x;
	double* ro;
	double* pom;
	double** jak;
	double tole = 1e-8;
	double tolr = 1e-8;
	int i = 0;
	int imax = 1000;
	xn = new double[3];
	x = new double[3];
	ro = new double[3];
	pom = new double[3];
	jak = new double*[3];
	for (int j = 0; j < 3; j++) jak[j] = new double[3];
	xn[0] = 20.0;
	xn[1] = 1.0;
	xn[2] = 0.3;
	cout << setw(5)<< "i" << setw(15) << "f(x)" << setw(15) << "estymator" << setw(15) << "residuum"<<endl;
	do {
		do {
			i++;
			kopiuj(xn, x, 3);
			mjakob(x, jak);
			fun(x, pom);
			mnozenie(jak, pom, ro);
			odejmowanieWektorow(x, ro, 3, xn);
			fun(xn, pom);
			cout << setw(5) << i << setw(3) << "|" << "\t";
			pokaz(pom, 3);
			cout << setw(3) << "|";
			cout << setw(15) << estymator(xn, x, 3) << setw(3) << "|" << setw(15) << residuum(xn, 3) << endl;
		} while (i < imax && estymator(xn, x, 3)>tole );
	} while (i<imax && residuum(xn, 3) > tolr);
	cout << endl<<endl;
	pokaz(xn, 3);
	cout << endl;
	delete[] x;
	delete[] xn;
	delete[] ro;
	delete[] pom;
	for(int j=0;j<3;j++) delete[] jak[j];
	delete[] jak;
	return 0;
}

