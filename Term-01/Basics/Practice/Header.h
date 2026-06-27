#pragma once

#include <iostream>
#include <string>
#include <fstream>
//#include <Windows.h>
//#include <conio.h>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
struct dis {
    string name;
    size_t hour;
    size_t sem;
};

void Read(vector<dis> &data);

void Add(vector<dis> &data);

void Delete(vector<dis> &data);

void Print(vector<dis> &data);

void FillFile(vector<dis> &data);

void Sort(vector<dis> &data);

void Edit(vector<dis> &data);

bool ControlName(string name);

bool ControlStrinhgForInt(string name);

void FindData(vector<dis> &data);

string GetDataStrinhgForInt();

string GetDataString();

size_t FindMax(vector<dis> &data);

size_t GetDataInt();

size_t Menu();