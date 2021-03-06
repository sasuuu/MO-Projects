// ConsoleApplication2.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

double analityczne(double t) {
	return 1.0 - exp(-10.0*(t+atan(t)));
}

double a(double t) {
	return (10.0*t*t + 20.0) / (t*t + 1);
}

double f(double t, double y) {
	double wyn = a(t)*(y-1.0)*-1.0;
	return wyn;
}

double bme(double dt) {
	double maxb = 0.0;
	double y = 0.0;
	double t = 0.0;
	double an;
	for (int i = 0; i < 200; i++) {
		y = y + f(t, y) * dt;
		t = t + dt;
		an = analityczne(t);
		if (abs(an - y) > maxb) maxb = abs(an - y);
	}
	return maxb;
}

void bme(ofstream *fs, double dt, int iter) {
	double y = 0.0;
	double t = 0.0;
	double an;
	*fs << setw(15) << left << 0.0 << '\t' << setw(15) << left << 0.0 << '\t' << setw(15) << left << 0.0 << endl;
	for (int i = 0; i < iter; i++) {
		y = y + f(t, y) * dt;
		t = t + dt;
		an = analityczne(t);
		*fs << setw(15) << left << t <<'\t'<< setw(15) << left << y << '\t' << setw(15)<<left << an<< endl;
	}
}

double pme(double dt) {
	double maxb = 0.0;
	double y = 0.0;
	double t = 0.0;
	double an;
	for (int i = 0; i < 200; i++) {
		y = (y+a(t+dt)*dt)/(a(t+dt)*dt+1.0);
		t = t + dt;
		an = analityczne(t);
		if (abs(an - y) > maxb) maxb = abs(an - y);
	}
	return maxb;
}

void pme(ofstream *fs, double dt) {
	double y = 0.0;
	double t = 0.0;
	double an;
	*fs << setw(15) << left << 0.0 << '\t' << setw(15) << left << 0.0 << '\t' << setw(15) << left << 0.0 << endl;
	for (int i = 0; i < 100; i++) {
		y = (y + a(t + dt)*dt) / (a(t + dt)*dt + 1.0);
		t = t + dt;
		an = analityczne(t);
		*fs << setw(15) << left << t << '\t' << setw(15) << left << y << '\t' << setw(15) << left << an << endl;
	}
}

double pmt(double dt) {
	double maxb = 0.0;
	double y = 0.0;
	double t = 0.0;
	double an;
	for (int i = 0; i < 200; i++) {
		y = (2.0*y+f(t,y)*dt+a(t+dt)*dt)/(2.0+a(t+dt)*dt);
		t = t + dt;
		an = analityczne(t);
		if (abs(an - y) > maxb) maxb = abs(an - y);
	}
	return maxb;
}

void pmt(ofstream *fs, double dt) {
	double y = 0.0;
	double t = 0.0;
	double an;
	*fs << setw(15) << left << 0.0 << '\t' << setw(15) << left << 0.0 << '\t' << setw(15) << left << 0.0 << endl;
	for (int i = 0; i <100; i++) {
		y = (2.0*y + f(t, y)*dt + a(t + dt)*dt) / (2.0 + a(t + dt)*dt);
		t = t + dt;
		an = analityczne(t);
		*fs << setw(15) << left << t << '\t' << setw(15) << left << y << '\t' << setw(15) << left << an << endl;
	}
}

int main()
{
	ofstream fs;
	double last_blad;
	double blad=0.0;
	double i;
	fs << fixed;
	fs << setprecision(15);
	fs.open("bme.dat", ofstream::out);
	bme(&fs, 0.01,100);
	fs.close();
	fs.open("bmens.dat", ofstream::out);
	bme(&fs, 0.25,10);
	fs.close();
	fs.open("bmeblad.dat", ofstream::out);
	for (i = 1e-16; i < 0.1; i = i * 10) {
		last_blad = blad;
		blad = log10(bme(i));
		fs << setw(15) << left << log10(i) << '\t' << setw(15) << left << blad << endl;
	}
	cout << "Rzad dokladnosci BME: " << (blad - last_blad) / (log10(i/10.0)-log10(i/100.0)) << endl;
	fs.close();
	fs.open("pme.dat", ofstream::out);
	pme(&fs, 0.01);
	fs.close();
	fs.open("pmeblad.dat", ofstream::out);
	for (i = 1e-16; i < 0.1; i = i * 10.0) {
		last_blad = blad;
		blad = log10(pme(i));
		fs << setw(15) << left << log10(i) << '\t' << setw(15) << left << blad << endl;
	}
	cout << "Rzad dokladnosci PME: " << (blad - last_blad) / (log10(i / 10.0) - log10(i / 100.0)) << endl;
	fs.close();
	fs.open("pmt.dat", ofstream::out);
	pmt(&fs, 0.01);
	fs.close();
	fs.open("pmtblad.dat", ofstream::out);
	for (i = 1e-16; i < 0.1; i = i * 10.0) {
		last_blad = blad;
		blad = log10(pmt(i));
		fs << setw(15) << left << log10(i) << '\t' << setw(15) << left << blad << endl;
	}
	cout << "Rzad dokladnosci PMT: " << (blad - last_blad) / (log10(i / 10.0) - log10(i / 100.0)) << endl;
	fs.close();
    return 0;
}

