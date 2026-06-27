#pragma once

#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>

#define NAME1 new char[7]{ "y = x " }
#define NAME2 new char[12]{ "y=sin(22x)" }
#define NAME3 new char[12]{ "y = x^4 " }
#define NAME4 new char[12]{ "y = atanx " }
#define NAME5 new char[12]{ "y = x^5 " }
using namespace std;

typedef double(*TPF)(double);

typedef double(*TPFEV)();

enum constant_variables {
    A = -1,
    B = 3,
    SIZE = 5
};
struct INTEGRALS {
    char *name;
    double i_sum;
    double i_toch;
    int n;
};

double Exactness_F1();

double Exactness_F2();

double Exactness_F3();

double Exactness_F4();

double Exactness_F5();

double F1(double x);

double F2(double x);

double F3(double x);

double F4(double x);

double F5(double x);

double rectangle(TPF, double a, double b, double eps, int &n);

double trapeze(TPF, double a, double b, double eps, int &n);

void PrintTabl(INTEGRALS i_prn[], int k);
