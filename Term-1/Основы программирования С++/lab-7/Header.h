#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <clocale>
#include <Windows.h>
#include <stdio.h>
#include <cstdint>
using namespace std;

void encrypt(char& text, int* key, int& num, int j, ofstream& file, unsigned char letter, int ArrLetter[256][256]);
void decrypt(char& text, int* key, int& num, int j, ofstream& file);