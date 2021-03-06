// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "funkcje.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#define N 4
//#define Debug

using namespace std;

bool wybor_czesciowy(double** A,double** L, int* wektor_indeksow, int x, int n) {
	double max = abs(A[x][x]);
	int w = x;
	double *tempw;
	int temp;
	for (int i = x + 1; i < n; i++) {
		if (abs(A[i][x]) > max) {
			w = i;
			max = abs(A[i][x]);
		}
	}
	if (w == x) return false;
	tempw = A[x];
	A[x] = A[w];
	A[w] = tempw;
	tempw = L[x];
	L[x] = L[w];
	L[w] = tempw;
	temp = wektor_indeksow[x];
	wektor_indeksow[x] = wektor_indeksow[w];
	wektor_indeksow[w] = temp;
	return true;
}

void dekompozycjaLU(double** A, double **L, int* wektor_indeksow, int n) {
	int i, j, k;
	double wspol;
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (A[i][i] != 0.0) {
				wspol = A[j][i] / A[i][i];
				L[j][i] = wspol;
				for (k = i; k < n; k++) A[j][k] -= wspol * A[i][k];
			}
			else {
				if (!wybor_czesciowy(A,L, wektor_indeksow, i, n)) {
					cout << "Dekompozycja nie udala sie poniewaz nie mozna wykonac czesciowego wyboru elementu podstawowego !!!";
					return;
				}
				else j--;
			}
		}
	}

}


void zwolnij_pamiec(double** A, double** L, double* b, int* wektor_indeksow, double* x, int n) {
	int i;
	for (i = 0; i < n; i++) {
		delete[] A[i];
		delete[] L[i];
	}
	delete[] b;
	delete[] wektor_indeksow;
	delete[] A;
	delete[] L;
	delete[] x;
}

void ustaw_tablice(double** A, double* b) {
	A[0][0] = 1.; A[0][1] = 20.; A[0][2] = -30.; A[0][3] = -4.;
	A[1][0] = 4.; A[1][1] = 20.; A[1][2] = -6.; A[1][3] = 50.;
	A[2][0] = 9.; A[2][1] = -18.; A[2][2] = 12.; A[2][3] = -11.;
	A[3][0] = 16.; A[3][1] = -15.; A[3][2] = 14.; A[3][3] = 130.;
	b[0] = 0.;
	b[1] = 114.;
	b[2] = -5.;
	b[3] = 177.;
	/*A[0][0] = 1; A[0][1] = 20; A[0][2] = -30; A[0][3] = -4;
	A[1][0] = 4; A[1][1] = 20; A[1][2] = -6; A[1][3] = 50;
	A[2][0] = 9; A[2][1] = -18; A[2][2] = 0; A[2][3] = -11;
	A[3][0] = 16; A[3][1] = -15; A[3][2] = 14; A[3][3] = 130;
	b[0] = 0;
	b[1] = 114;
	b[2] = -5;
	b[3] = 177;*/
}

void wyswietl_tablice(double **x, int n) {
	cout << endl;
	cout << "---------------------------------------------------------------------------------";
	for (int i = 0; i < n; i++) {
		cout << endl;
		for (int j = 0; j < n; j++)
			cout << setw(15) << x[i][j];
	}
	cout << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
}
template<class T>
void wyswietl_wektor(T *x, int n) {
	cout << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++)
		cout << setw(15) << x[i];
	cout << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
}

void wektorB(int* wektor_indeksow, double* b, int n) {
	double* temp = new double[n];
	for (int i = 0; i < n; i++) temp[i] = b[i];
	for (int i = 0; i < n; i++) {
		if (i != wektor_indeksow[i]) b[i] = temp[wektor_indeksow[i]];
	}
}

void solve(double *b, double** A, double** L, double* x, int n) {
	int i, j;
	double temp = 0;
	double* y = new double[n];
	for (i = 0; i < n; i++) {
		for (j = i - 1; j >= 0; j--) {
			temp += L[i][j] * y[j];
		}
		y[i] = (b[i] - temp);
		temp = 0;
	}
	for (i = n - 1; i >= 0; i--) {
		for (j = i + 1; j < n; j++) {
			temp += A[i][j] * x[j];
		}
		x[i] = (y[i] - temp) / A[i][i];
		temp = 0;
	}
}

void alokuj_pamiec(double ***A, int **wektor_indeksow, double **b, double ***L, double **x,int n) {
	int i, j;
	*A = new double*[n];
	*L = new double*[n];
	for (i = 0; i < n; i++) {
		(*A)[i] = new double[n];
		(*L)[i] = new double[n];
	}
	*b = new double[n];
	*wektor_indeksow = new int[n];
	*x = new double[n];
	for (i = 0; i < n; i++) {
		(*b)[i] = 0.;
		(*x)[i] = 0.;
		(*wektor_indeksow)[i] = i;
		for (j = 0; j < n; j++) {
			(*A)[i][j] = 0.;
			if (i == j) (*L)[i][j] = 1.;
			else (*L)[i][j] = 0.;
		}
	}
}

int main()
{
	double **A=NULL;
	int *wektor_indeksow=NULL;
	double *b=NULL;
	double **L=NULL;
	double *x=NULL;
	alokuj_pamiec(&A, &wektor_indeksow, &b, &L, &x,N);
	ustaw_tablice(A,b);
#ifdef Debug
	cout << "A: ";
	wyswietl_tablice(A,N);
	cout << "b: ";
	wyswietl_wektor<double>(b,N);
	cout << "L: ";
	wyswietl_tablice(L,N);
	cout << "wektor_indeksow: ";
	wyswietl_wektor<int>(wektor_indeksow,N);
#endif
	dekompozycjaLU(A,L,wektor_indeksow,N);
	wektorB(wektor_indeksow,b,N);
#ifdef Debug
	cout << "A: ";
	wyswietl_tablice(A,N);
	cout << "L: ";
	wyswietl_tablice(L,N);
	cout << "b: ";
	wyswietl_wektor<double>(b,N);
	cout << "wektor_indeksow: ";
	wyswietl_wektor<int>(wektor_indeksow,N);
#endif
	solve(b,A,L,x,N);
	cout << "X: ";
	wyswietl_wektor<double>(x,N);
	zwolnij_pamiec(A,L,b,wektor_indeksow,x,N);
    return 0;
}

