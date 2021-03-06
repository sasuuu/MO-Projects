// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#define M_PI 3.14159265358979323846


template<class T>
T funkcja(T x) {
	return cos(x / (T)2);
}

template<class T>
T funkcjapochodna(T x) {
	return -0.5*sin(x / (T)2);
}

using namespace std;

template<class T>
void fun(ofstream *fs) {
	T h = 1e-15;
	T hpp = 0;
	T hp = 0;
	T f;
	T war;
	T blad1=0,blad2=0,blad3=0,blad4=0,blad5=0,blad6=0,blad7=0;
	T blad1p, blad2p, blad3p, blad4p, blad5p, blad6p, blad7p;
	for (h; h < (T)1; h = h * (T)10) {
		blad1p = blad1;
		blad2p = blad2;
		blad3p = blad3;
		blad4p = blad4;
		blad5p = blad5;
		blad6p = blad6;
		blad7p = blad7;
		*fs << fixed<<setprecision(16) << log10(h) << "\t";
		//Wewnetrzny wezel
		f = (funkcja<T>((T)M_PI / (T)2 + h) - funkcja<T>((T)M_PI / (T)2 - h)) / ((T)2*h);
		war = funkcjapochodna<T>((T)M_PI/(T)2);
		blad1 = abs(f - war);
		*fs << fixed << setprecision(16) << log10(blad1) << "\t";
		f = (funkcja<T>((T)M_PI / (T)2. + h) - funkcja<T>((T)M_PI / (T)2.)) / h;
		blad2 = abs(f - war);
		*fs << fixed << setprecision(16) << log10(blad2) << "\t";
		f = (funkcja<T>((T)M_PI / (T)2.) - funkcja<T>((T)M_PI / (T)2. - h)) / h;
		blad3 = abs(f - war);
		*fs << fixed << setprecision(16) << log10(blad3) << "\t";
		//Wezel poczatkowy
		f = (funkcja<T>((T)0 + h) - funkcja<T>((T)0)) / h;
		war = funkcjapochodna<T>((T)0);
		blad4 = abs(f - war);
		*fs << fixed << setprecision(16) << log10(blad4) << "\t";
		f = ((-(T)3/(T)2)*funkcja<T>((T)0) + (T)2 * funkcja<T>((T)0+h)-((T)1/(T)2)*funkcja<T>((T)0+(T)2*h)) / h;
		blad5 = abs(f - war);
		*fs << fixed << setprecision(16) << log10(blad5) << "\t";
		//Wezel koncowy
		f = (funkcja<T>((T)M_PI) - funkcja<T>((T)M_PI-h)) / h;
		war = funkcjapochodna<T>((T)M_PI);
		blad6 = abs(f - war);
		*fs << fixed << setprecision(16) << log10(blad6) << "\t";
		f = (((T)1/(T)2)*funkcja<T>((T)M_PI-(T)2*h) - (T)2 * funkcja<T>((T)M_PI - h) + ((T)3/(T)2)*funkcja<T>((T)M_PI)) / h;
		blad7 = abs(f - war);
		*fs << fixed << setprecision(16) << log10(blad7) << "\t"<<endl;
		hpp = hp;
		hp = h;
	}
	cout << "Rzad dokladnosci dla typu " << typeid(h).name() << ":" << endl;
	cout << "Wezel wewnetrzny roznica centralna: "<< (log10(blad1) - log10(blad1p))/(log10(hp)-log10(hpp)) << endl;
	cout << "Wezel wewnetrzny roznica progresywna: " << (log10(blad2) - log10(blad2p)) / (log10(hp) - log10(hpp)) << endl;
	cout << "Wezel wewnetrzny roznica wsteczna: " << (log10(blad3) - log10(blad3p)) / (log10(hp) - log10(hpp)) << endl;
	cout << "Wezel poczatkowy roznica progresywna: " << (log10(blad4) - log10(blad4p)) / (log10(hp) - log10(hpp)) << endl;
	cout << "Wezel poczatkowy roznca progresywna trzypunktowa: " << (log10(blad5) - log10(blad5p)) / (log10(hp) - log10(hpp)) << endl;
	cout << "Wezel koncowy roznica wsteczna: " << (log10(blad6) - log10(blad6p)) / (log10(hp) - log10(hpp)) << endl;
	cout << "Wezel koncowy roznica wsteczna trzypunktowa: " << (log10(blad7) - log10(blad7p)) / (log10(hp) - log10(hpp)) << endl;
}

int main()
{
	ofstream fs;
	fs.open("lab08double.dat", fstream::out);
	fun<double>(&fs);
	fs.close();
	fs.open("lab08float.dat", fstream::out);
	fun<float>(&fs);
	fs.close();
    return 0;
}

