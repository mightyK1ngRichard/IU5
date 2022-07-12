#pragma once
#include <iostream>
#include <ctime>
#include "Header.h"
#include <iomanip>
using namespace std;
void fillarray(int* arr, const int size);
void printarr(int* arr, const int size);
void minmax(int* arr, const int size, int& com, int& sw, bool flag);
void water(int* arr, int size, int& com, int& sw, bool flag);
