#include "Header.h"

void encrypt(char& text, int* key, int& num, int j, ofstream& file, unsigned char letter, int ArrLetter[256][256])
{
	// Аналитика
	unsigned char text1 = text;
	if (letter == text1)
		++ArrLetter[(int)letter][((int)text1 + key[num % j]) % 256];
	// кек
	text1 = static_cast<char>((static_cast<int>(text1) + key[num % j]) % 256);
	file << text1;
	++num;
}

void decrypt(char& text, int* key, int& num, int j, ofstream& file)
{
	text = static_cast<char>((static_cast<int>(text) - key[num % j]) % 256);
	file << text;
	++num;
}