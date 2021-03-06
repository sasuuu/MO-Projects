// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#define N 6
//#define Debug

using namespace std;

void wyswietl_wektor(double *x,int n) {
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++)
		cout << setw(15) << x[i];
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------" << endl;
}

void zwolnij_pamiec(double *D,double *L, double *U,double *x, double *b) {
	delete[] D;
	delete[] L;
	delete[] U;
	delete[] x;
	delete[] b;
}

void ustaw_tablice(double *D,double *L,double *U,double *b) {
	D[0] = 30.0;
	D[1] = 20.0;
	D[2] = 10.0;
	D[3] = 10.0;
	D[4] = 20.0;
	D[5] = 30.0;
	L[0] = 3.0/4.0;
	L[1] = 7.0/8.0;
	L[2] = 11.0/12.0;
	L[3] = 15.0/16.0;
	L[4] = 19.0/20.0;
	U[0] = 2.0/3.0;
	U[1] = 5.0/6.0;
	U[2] = 9.0/10.0;
	U[3] = 13.0/14.0;
	U[4] = 17.0/18.0;
	b[0] = 94.0/3.0;
	b[1] = 173.0 / 4.0;
	b[2] = 581.0 / 20.0;
	b[3] = -815.0 / 28.0;
	b[4] = -6301.0 / 144.0;
	b[5] = -319.0 / 10.0;
}

void eta(double *D,double *L,double *U) {
	int i;
	for (i = 1; i < N; i++) D[i] = D[i] - (L[i-1] / D[i - 1]) * U[i-1];
}

void r(double *b,double *L,double *D,double *U,double *x) {
	int i;
	for (i = 1; i < N; i++) b[i] = b[i] - (L[i-1] / D[i-1])*b[i - 1]; 
	x[N - 1] = b[N - 1]/D[N-1];
	for (i = N - 2; i >= 0; i--) x[i] = ((b[i] - (x[i + 1] * U[i])) / D[i]);
}

void alokuj_pamiec(double **L, double **D, double **U, double **b, double **x,int n) {
	*D = new double[n];
	*L = new double[n - 1];
	*U = new double[n - 1];
	*b = new double[n];
	*x = new double[n];
}

int main()
{
	double *L;
	double *D;
	double *U;
	double *b;
	double *x;
	alokuj_pamiec(&L,&D,&U,&b,&x,N);
	ustaw_tablice(D,L,U,b);
#ifdef Debug
	cout << "U: ";
	wyswietl_wektor(U,N-1);
	cout << "D: ";
	wyswietl_wektor(D,N);
	cout << "L: ";
	wyswietl_wektor(L,N-1);
	cout << "b: ";
	wyswietl_wektor(b,N);
#endif
	eta(D,L,U);
	r(b,L,D,U,x);
#ifdef Debug
	cout << "U: ";
	wyswietl_wektor(U,N-1);
	cout << "D: ";
	wyswietl_wektor(D,N);
	cout << "L: ";
	wyswietl_wektor(L,N-1);
	cout << "b: ";
	wyswietl_wektor(b,N);
#endif
	cout << "x: ";
	wyswietl_wektor(x, N);
	zwolnij_pamiec(D,L,U,x,b);
    return 0;
}

