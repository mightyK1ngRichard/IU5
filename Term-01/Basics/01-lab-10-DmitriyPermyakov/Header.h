#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>

using namespace std;

void Fill(long double **arr, size_t m, size_t n);

void FillUnit(long double **arr, size_t m, size_t n);

void PrintArr(long double **arr, size_t rows, size_t cols, bool typeMatrix, size_t precision);

void Multiplication(long double **arr_old, long double **arr, size_t m, size_t n, bool typeMatrix, size_t precision);

bool StraightCourse(long double **arr, long double **arr1, size_t m, size_t n, bool typeMatrix, size_t precision);

void BackCourse(long double **arr, long double **arr1, size_t m, size_t n, bool typeMatrix, size_t precision);

size_t GetDataInt();