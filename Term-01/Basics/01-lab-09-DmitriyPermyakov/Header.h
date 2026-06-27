#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <Windows.h>

using namespace std;
struct d {
    char *eng, *rus;
};

void Add(d *words, size_t &size);

void Delete(d *words, size_t &size);

void TranslateToRus(d *words, size_t size);

void TranslateToEng(d *words, size_t size);

void Print(d *words, size_t size);

void FillFile(d *words, size_t size);

size_t read(d *words);

size_t Menu();

void dict_sort(d *dict, size_t size);

size_t GetDataInt();