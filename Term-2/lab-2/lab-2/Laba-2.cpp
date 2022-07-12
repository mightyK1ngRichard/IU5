#include "Header.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N = 20;
	Man* arr = new Man[N];
	
	char* filename = new char[20];
	strcpy_s(filename, 20, "dbase.txt");
	int n;

	if (read_dbase(filename, arr, n)) {
		cout << "Ошибка чтения БД" << endl;
		return 1;
	}
	print_dbase(arr, n);
	while (true) {
		switch (menu())
		{
		case 1: add(arr, n); break; 
		case 2: remove(arr,n); break;
		case 3: find_man(arr, n);  break;
		case 4: edit(arr,n); break; 
		case 5: print_dbase(arr, n); break;
		case 6: write_dbase(filename, arr, n); break;
		case 7: delete[] arr; delete[] filename; return 0;
		case 8: system("cls"); break;
		default: cout << " Недопустимый номер операции!\n\n"; break;
		}
	}

}