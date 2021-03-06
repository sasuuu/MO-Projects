// ConsoleApplication2.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

double a = -1.0;
double b = 1.0;
int n = 12;

double f(double x) {
	return x / (1.0+20.0*x*x*x*x);
}

void alokuj(double ***A, int n, int sposob) {
	double h = (b - a) / ((double)n-1.0);
	*A = new double*[n + 1];
	*A[0] = new double[n];
	for (int i = 0; i < n; i++) {
		(*A)[i+1] = new double[n-i];
	}
	if(sposob == 0) for (int i = 0; i < n; i++) (*A)[0][i] = a + i * h;
	else for (int i = 0; i < n; i++) (*A)[0][i] = (b+a)/2.0 + ((b-a)/2)*cos(((2.0*i+1.0)/(2.0*(n-1)+2.0))*(double)M_PI);
}

void oblicz_c(double **A, int n) {
	for(int i=1;i<=n;i++){
		for (int j = 0; j < n - (i-1); j++) {
			if (i == 1) {
				A[i][j] = f(A[0][j]);
			}
			else {
				A[i][j] = (A[i - 1][j + 1] - A[i - 1][j]) / (A[0][j + (i - 1)] - A[0][j]);
			}
		}
	}
}

double interpolant(double **A, double x, int n) {
	double wyn=A[n][0]*(x-A[0][n-2])+A[n-1][0];
	for (int i = n-3; i >= 0; i--) {
		wyn = wyn * (x-A[0][i])+A[i+1][0];
	}
	return wyn;
}


int main()
{
	ofstream fs;
	double **A;
	fs << setprecision(15);
	fs.open("funkcja.dat", fstream::out);
	for (double i = a; i <= b; i = i + 1e-3) {
		fs << setw(15) << left << i << '\t' << setw(15) << left << f(i) << endl;
	}
	fs.close();
	alokuj(&A, n , 0);
	oblicz_c(A, n);
	fs.open("funkcjainter.dat", fstream::out);
	for (double i = a; i <= b; i = i + 1e-3) fs << setw(15) << left << i << '\t' << setw(15) << left << interpolant(A, (double)i, n)<<endl;
	fs.close();
	for (int i = 0; i <= n; i++) delete[] A[i];
	delete[] A;
	alokuj(&A, n, 1);
	oblicz_c(A, n);
	fs.open("funkcjainterczybyszew.dat", fstream::out);
	for (double i = a; i <= b; i = i + 1e-3) fs << setw(15) << left << i << '\t' << setw(15) << left << interpolant(A, (double)i, n) << endl;
	fs.close();
	for (int i = 0; i <= n; i++) delete[] A[i];
	delete[] A;
    return 0;
}

