#include "Header.h"

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// получаем сумму ключей
	int* key = new int[1000]{ 0 };
	char ch;
	int i = -1;
	ifstream fin("key.txt", ios::binary);
	bool newLetter = true;
	while (fin.get(ch))
	{
		unsigned char ch_old = static_cast<unsigned char>(ch);
		if (ispunct(ch_old) || isspace(ch_old))
		{
			newLetter = true;
			continue;
		}

		if (newLetter)
		{
			++i;
			newLetter = false;
		}
		key[i] += static_cast<int>(ch_old);
		if (i == 1000)
			break;
	}
	fin.close();
	for (int index = 0; index <= i; ++index)
		cout << key[index] << ' ';
	cout << endl << endl;
	//кек

	unsigned char letter;
	cout << "Enter the letter for analytic: ";
	cout << "\x1b[35m";
	cin >> letter;
	cout << "\x1b[0m\n";
	int ArrLetter[256][256]{ 0 };


	// шифруем
	int num = 0;
	ifstream text("text.txt", ios::binary);
	ofstream fin22("encrypt.txt", ios::binary);
	while (text.get(ch))
		encrypt(ch, key, num, i+1, fin22, letter, ArrLetter);
	//cout << endl;
	text.close();
	fin22.close();
	// кек

	// читаем файл и расшифровываем
	num = 0;
	ifstream fin2("encrypt.txt", ios::binary);
	ofstream fin3("decrypt.txt", ios::binary);
	while (fin2.get(ch))
		decrypt(ch, key, num, i + 1, fin3);
	fin2.close();
	fin3.close();
	cout << endl;
	// кек


	cout << endl << "Analytics" << endl;
	cout << setw(8) << "symbol " << '|' << setw(12) << "its kod " << '|' << setw(10) << "numbers " << '|' << endl;

	for (int j = 0; j < 256; j++)
	{
		if (ArrLetter[(int)letter][j] > 0)
			cout << setw(4) << (char)(j) << setw(5) << '|'
			<< setw(8) << j << setw(5) << '|'
			<< setw(6) << ArrLetter[(int)(letter)][j] << setw(5) << '|' << endl;
	}

	delete[] key;
	return 0;
}

