#pragma once
bool wybor_czesciowy(double** A, int* wektor_indeksow, int x, int n);
void dekompozycjaLU(double** A, double **L, int* wektor_indeksow, int n);
void zwolnij_pamiec(double** A, double** L, double* b, int* wektor_indeksow, double* x, int n);
void ustaw_tablice(double** A, double* b);
void wyswietl_tablice(double **x, int n);
template<class T>
void wyswietl_wektor(T *x, int n);
void wektorB(int* wektor_indeksow, double* b, int n);
void solve(double *b, double** A, double** L, double* x, int n);
