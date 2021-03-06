// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#define PI 3.14159265358979323846

using namespace std;

double a = 0.0f;
double bb = (double)PI / 4.0;
double alfa = 0.0;
double beta = 1.0;
double gamma = 0.0;
double fi = 0.0;
double psi = 1.0;
double teta = -(1.0/2.0);

double p(double x) {
	return 1.0;
}

double q(double x) {
	return 0.0;
}

double rr(double x) {
	return 4.0;
}

double s(double x) {
	return tan(x);
}

double analityczne(double x) {
	return (1.0 / 4.0)*(2.0*x*cos(2.0*x) + 2.0*sin(2.0*x) - log(2.0)*sin(2.0*x) - 2.0*log(cos(x))*sin(2.0*x));
}

void eta(double *D, double *L, double *U, int N) {
	for (int i = 0; i < N; i++) D[i] = D[i] - (L[i - 1] / D[i - 1]) * U[i - 1];
}

void r(double *b, double *L, double *D, double *U, double *x, int N) {
	int i;
	for (i = 1; i <= N; i++) b[i] = b[i] - (L[i - 1] / D[i - 1])*b[i - 1];
	x[N] = b[N] / D[N];
	for (i = N - 1; i >= 0; i--) x[i] = ((b[i] - (x[i + 1] * U[i])) / D[i]);
}

void thomas(double *L, double *D, double *U, double *x, double *b, int N) {
	eta(D, L, U, N);
	r(b, L, D, U, x, N);
}

void konwencjonalna(double *b,double *D,double *L,double *U,double *x, int N) {
	double h = bb / (double)(N);
	int i;
	b[0] = -gamma;
	b[N] = -teta;
	for (i = 1; i < N; i++) b[i] = -s(0.0 + (double)i * h);
	D[0] = beta - (alfa / h);
	D[N] = (fi / h) + psi;
	for (i = 1; i < N; i++) { D[i] = rr(0.0 + (double)i * h) - ((2.0*p(0.0 + (double)i * h)) / (h*h)); }
	U[0] = alfa / h;
	for (i = 1; i <= N - 1; i++) U[i] = (p(0.0 + (double)i * h) / (h*h)) + (q(0.0 + (double)i * h) / (2.0*h));
	L[N - 1] = -(fi / h);
	for (i = 0; i < N - 1; i++) L[i] = (p(0.0 + (double)(i + 1) * h) / (h*h)) - (q(0.0 + (double)(i + 1) * h) / (2.0*h));
	thomas(L, D, U, x, b, N);
	//for (int i = 0; i <= N; i++) cout << b[i] << endl;

}

void numerowa(double *b, double *D, double *L, double *U, double *x, int N) {
	double h = bb / (double)(N);
	int i;
	b[0] = -gamma;
	b[N] = -teta;
	for (i = 1; i < N; i++) b[i] = (-1.0/12.0)*s(0.0 + (double)(i-1) * h)-(10.0/12.0)*s(0.0 +(double)i *h)-(1.0/12.0)*s(0.0+(double)(i+1)*h);
	D[0] = beta - (alfa / h);
	D[N] = (fi / h) + psi;
	for (i = 1; i < N; i++) D[i] = ((rr(0.0 + (double)i * h)*10.0)/12.0) - ((2.0*p(0.0 + (double)i * h)) / (h*h));
	U[0] = alfa / h;
	for (i = 1; i <= N - 1; i++) U[i] = (p(0.0 + (double)i * h) / (h*h)) + (rr(0.0+ (double)i*h)/12.0);
	L[N - 1] = -(fi / h);
	for (i = 0; i < N - 1; i++) L[i] = (p(0.0 + (double)(i + 1) * h) / (h*h)) + (rr(0.0 + (double)i * h) / 12.0);
	thomas(L, D, U, x, b, N);
}

double max_blad(double *x,int N) {
	double max_blad = abs(x[0] - analityczne(0.0));
	double blad=0.0;
	for (int i = 1; i <= N; i++) {
		blad = abs(x[i] - analityczne(0.0 + i * (bb / (double)N)));
		if (blad > max_blad) max_blad = blad;
	}
	return max_blad;
}

int main()
{
	double blad1 = 0.0;
	double blad2 = 0.0;
	double *x;
	double *b;
	double *L;
	double *D;
	double *U;
	double h = 0.0;
	double ost_blad1;
	double ost_blad2;
	double ost_h;
	ofstream fs1,fs2;
	fs1.open("konwencjonalna.dat", fstream::out);
	fs2.open("Numerowa.dat", fstream::out);
	fs1 << fixed << setprecision(15);
	fs2 << fixed << setprecision(15);
	x = new double[21];
	b = new double[21];
	D = new double[21];
	L = new double[20];
	U = new double[20];
	konwencjonalna(b,D,L,U,x, 20);
	for (int i = 0; i <= 20; i++) {
		fs1 << setw(15) << left << 0.0 + i * bb/20.0 << "\t" << setw(15) << left << x[i] << "\t" << setw(15) << left << analityczne(0.0 + i * bb/20.0) << endl;
	}
	numerowa(b, D, L, U, x, 20);
	for (int i = 0; i <= 20; i++) {
		fs2 << setw(15) << left << 0.0 + i * bb / 20.0 << "\t" << setw(15) << left << x[i] << "\t" << setw(15) << left << analityczne(0.0 + i * bb/20.0) << endl;
	}
	fs1.close();
	fs2.close();
	delete x;
	delete b;
	delete D;
	delete L;
	delete U;
	fs1.open("bledykonwencjonalna.dat", fstream::out);
	fs2.open("bledynumerowa.dat", fstream::out);
	fs1 << fixed <<setprecision(15);
	fs2 << fixed << setprecision(15);
	for (long long i = 1e+7; i >= 10; i=i/2) {
		x = new double[i+1];
		b = new double[i+1];
		D = new double[i+1];
		L = new double[i];
		U = new double[i];
		ost_blad1 = blad1;
		ost_blad2 = blad2;
		ost_h = h;
		h = bb / (double)i;
		konwencjonalna(b, D, L, U, x, i);
		blad1 = max_blad(x, i);
		fs1 << setw(15) << left << log10(h) << "\t" << setw(15) << left << log10(blad1) << "\t" << endl;
		numerowa(b, D, L, U, x, i);
		blad2 = max_blad(x, i);
		fs2 << setw(15) << left << log10(h) << "\t" << setw(15) << left << log10(blad2) << "\t" << endl;
		delete x;
		delete b;
		delete D;
		delete L;
		delete U;
	}
	cout << "Rzad dokladnosci dla dyskretyzacji konwencjonalnej: "<< (log10(blad1)-log10(ost_blad1))/(log10(h)-log10(ost_h))<<endl;
	cout << "Rzad dokladnosci dla dyskretyzacji Numerowa: " << (log10(blad2) - log10(ost_blad2)) / (log10(h) - log10(ost_h)) << endl;
	fs1.close();
	fs2.close();
	return 0;
}