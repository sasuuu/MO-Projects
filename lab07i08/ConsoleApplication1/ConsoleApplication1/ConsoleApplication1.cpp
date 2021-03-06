// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#define N 4
#define IMAX 200
#define TOLR 1e-5
#define TOLE 1e-5
#define OMEGA 0.5

using namespace std;

double mnozenie_wektorow(double *x, double *y,int skip,int sposob) {
	double res = 0.;
	if (sposob == 1) {
		for (int i = skip+1; i < N; i++) {
			res += x[i] * y[i];
		}
	}
	else if(sposob==0 || sposob==2) {
		for (int i = 0; i < N; i++) {
			if (i == skip && sposob == 0)continue;
			if (i == skip && sposob == 2)break;
			res += x[i] * y[i];
		}
	}
	else {
		for (int i = skip + 1; i < N; i++) {
			res += x[i] * y[i];
		}
		res += (x[skip]*(1.-1./OMEGA)) * y[skip];
	}
	return res;
}

double normr(double **A, double *x, double *b) {
	double *r;
	double maxr;
	r = new double[N];
	for (int i = 0; i < N; i++) r[i] = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			r[i] += A[i][j] * x[j];
		}
		r[i] = r[i] - b[i];
	}
	maxr = abs(r[0]);
	for (int i = 1; i < N; i++) {
		if (abs(r[i]) > maxr) maxr = abs(r[i]);
	}
	return maxr;
}

double normw(double *x,double *y) {
	double *e;
	e = new double[N];
	for (int i = 0; i < N; i++) e[i] = x[i] - y[i];
	double max=abs(e[0]);
	for (int i = 1; i < N; i++) {
		if (abs(e[i]) > max) max = abs(e[i]);
	}
	return max;
}

void wys_wektor(double *x) {
	for (int i = 0; i < N; i++) cout <<setw(10)<< x[i] << "\t";
}

void metJakobiego(double **A, double *b, double *x) {
	double *xx;
	double *xn;
	double *ps;
	int i = 0;
	xx = new double[N];
	for (int i = 0; i < N; i++) xx[i] = x[i];
	xn = new double[N];
	ps = new double[N];
	cout << setprecision(10);
	cout << "Metoda Jakobiego:" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(3) << "i" << setw(30) << "x" << "\t\t\t\t\t\t" << setw(10)<< "tole" <<"\t\t"<< setw(10) << "tolr" << endl;
	do {
		for (int i = 0; i < N; i++) {
			ps[i] = -mnozenie_wektorow(A[i],xx,i,0) + b[i];
		}
		for (int i = 0; i < N; i++) {
			xn[i] = ps[i] / A[i][i];
		}
		i++;
		cout << setw(3) << i<<"\t"<<fixed;
		wys_wektor(xn);
		cout<<scientific<<"\t"<< setw(10) << normw(xn, xx) <<"\t"<< setw(10) << normr(A, xn, b) << endl;
		if (normw(xn, xx) < TOLE && normr(A, xn, b) < TOLR) break;
		if (normr(A, xn, b) < TOLR) break;
		for (int i = 0; i < N; i++) xx[i] = xn[i];
	} while (i<IMAX);
	cout << "Wynik:" <<fixed<< endl;
	for (int i = 0; i < N; i++) cout << xn[i] << "\t";
	cout << endl<<endl;
}

void metGaussaSeidela1(double **A, double *b, double *x) {
	double *xx;
	double *xn;
	double *ps;
	double sum = 0;
	int i = 0;
	xx = new double[N];
	for (int i = 0; i < N; i++) xx[i] = x[i];
	xn = new double[N];
	ps = new double[N];
	cout << setprecision(10);
	cout << "Metoda Gaussa-Seidela wariant 1:" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(3) << "i" << setw(30) << "x" << "\t\t\t\t\t\t" << setw(10) << "tole" << "\t\t" << setw(10) << "tolr" << endl;
	do {
		for (int i = 0; i < N; i++) {
			ps[i] = -mnozenie_wektorow(A[i], xx, i, 1) + b[i];
		}
		xn[0] = ps[0] / A[0][0];
		for (int i = 1; i < N; i++) {
			sum = 0;
			for (int j = 0; j < i; j++) sum += A[i][j] * xn[j];
			ps[i] = ps[i] - sum;
			xn[i] = ps[i] / A[i][i];
		}
		i++;
		cout << setw(3) << i << "\t" << fixed;
		wys_wektor(xn);
		cout << scientific << "\t" << setw(10) << normw(xn, xx) << "\t" << setw(10) << normr(A, xn, b) << endl;
		if (normw(xn, xx) < TOLE && normr(A, xn, b) < TOLR) break;
		if (normr(A, xn, b) < TOLR) break;
		for (int i = 0; i < N; i++) xx[i] = xn[i];
		
	} while (i<IMAX);
	cout << "Wynik:" << fixed << endl;
	for (int i = 0; i < N; i++) cout << xn[i] << "\t";
	cout << endl<<endl;
}

void metGaussaSeidela2(double **A, double *b, double *x) {
	double *xx;
	double *xn;
	double *ps;
	double sum = 0;
	int i = 0;
	xx = new double[N];
	for (int i = 0; i < N; i++) xx[i] = x[i];
	xn = new double[N];
	ps = new double[N];
	cout << setprecision(10);
	cout << "Metoda Gaussa-Seidela wariant 2:" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(3) << "i" << setw(30) << "x" << "\t\t\t\t\t\t" << setw(10) << "tole" << "\t\t" << setw(10) << "tolr" << endl;
	do {
		for (int i = 0; i < N; i++) {
			ps[i] = -mnozenie_wektorow(A[i], xx, i, 2) + b[i];
		}
		xn[N-1] = ps[N-1] / A[N-1][N-1];
		for (int i = N-2; i >= 0; i--) {
			sum = 0;
			for (int j = i+1; j < N; j++) sum += A[i][j] * xn[j];
			ps[i] = ps[i] - sum;
			xn[i] = ps[i] / A[i][i];
		}
		i++;
		cout << setw(3) << i << "\t" << fixed;
		wys_wektor(xn);
		cout << scientific << "\t" << setw(10) << normw(xn, xx) << "\t" << setw(10) << normr(A, xn, b) << endl;
		if (normw(xn, xx) < TOLE && normr(A, xn, b) < TOLR) break;
		if (normr(A, xn, b) < TOLR) break;
		for (int i = 0; i < N; i++) xx[i] = xn[i];
		
	} while (i<IMAX);
	cout << "Wynik:" << fixed << endl;
	for (int i = 0; i < N; i++) cout << xn[i] << "\t";
	cout << endl << endl;
}

void metSOR(double **A, double *b, double *x) {
	double *xx;
	double *xn;
	double *ps;
	double sum = 0;
	int i = 0;
	xx = new double[N];
	for (int i = 0; i < N; i++) xx[i] = x[i];
	xn = new double[N];
	ps = new double[N];
	cout << setprecision(10);
	cout << "Metoda SOR:" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(3) << "i" << setw(30) << "x" << "\t\t\t\t\t\t" << setw(10) << "tole" << "\t\t" << setw(10) << "tolr" << endl;
	do {
		for (int i = 0; i < N; i++) {
			ps[i] = -mnozenie_wektorow(A[i], xx, i, 3) + b[i];
		}
		xn[0] = ps[0] / (A[0][0]*(1/OMEGA));
		for (int i = 1; i < N; i++) {
			sum = 0;
			for (int j = 0; j < i; j++) sum += A[i][j] * xn[j];
			ps[i] = ps[i] - sum;
			xn[i] = ps[i] / (A[i][i]*(1/OMEGA));
		}
		i++;
		cout << setw(3) << i << "\t" << fixed;
		wys_wektor(xn);
		cout << scientific << "\t" << setw(10) << normw(xn, xx) << "\t" << setw(10) << normr(A, xn, b) << endl;
		if (normw(xn, xx) < TOLE && normr(A, xn, b) < TOLR) break;
		if (normr(A, xn, b) < TOLR) break;
		for (int i = 0; i < N; i++) xx[i] = xn[i];
		
	} while (i<IMAX);
	cout << "Wynik:" << fixed << endl;
	for (int i = 0; i < N; i++) cout << xn[i] << "\t";
	cout << endl << endl;
}

void alokuj_pamiec(double ***A, double **b, double **x) {
	*A = new double*[N];
	*b = new double[N];
	*x = new double[N];
	for (int i = 0; i < N; i++) (*A)[i] = new double[N];
}

void ustaw_tablice(double **A, double *b,double *x) {
	A[0][0] = 100.; A[0][1] = 1.; A[0][2] = -2.; A[0][3] = 3.;
	A[1][0] = 4.; A[1][1] = 300.; A[1][2] = -5.; A[1][3] = 6.;
	A[2][0] = 7.; A[2][1] = -8.; A[2][2] = 400.; A[2][3] = 9.;
	A[3][0] = -10.; A[3][1] = 11.; A[3][2] = -12.; A[3][3] = 200.;
	b[0] = 395.;
	b[1] = 603.;
	b[2] = -415.;
	b[3] = -606.;
	x[0] = 1.;
	x[1] = 1.;
	x[2] = 1.;
	x[3] = 1.;
}

int main()
{
	double **A;
	double *b;
	double *x;
	alokuj_pamiec(&A,&b,&x);
	ustaw_tablice(A,b,x);
	metJakobiego(A, b, x);
	metGaussaSeidela1(A, b, x);
	metGaussaSeidela2(A, b, x);
	metSOR(A, b, x);
	return 0;
}

