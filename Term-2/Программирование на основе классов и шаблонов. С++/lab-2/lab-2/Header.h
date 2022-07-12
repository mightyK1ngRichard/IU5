#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>        
#include <Windows.h>
#include <string.h>
#define l_name 20

using namespace std;

class Man {
	char* pName;
	int birth_year{};
	float pay{};
public:
	Man(int I_name = 20){ pName = new char[I_name]; strcpy_s(pName, I_name, "");};
	~Man() { delete[] pName; };
	void SetBirth(int B) { birth_year = B; }
	void SetPay(float P) { pay = P; }
	void SetName(char* timeName) 
	{ 
		timeName = new char[l_name];
		cin.getline(timeName, l_name);	
		strcpy_s(pName, l_name, timeName);
		delete[] timeName;
	}

	int GetBirth() { return birth_year; }
	float GetPay() { return pay; }
	char* GetName() { return pName; };

	friend void print_dbase(Man* arr, int n);
	friend int find(Man* arr, int n, char* name);
	friend int find(Man* arr, int n, int birth_year);
	friend int find(Man* arr, int n, float pay);
	friend void find_man(Man* arr, int n);
	friend int write_dbase(char* filename, Man* arr, int n);
	friend int read_dbase(char* filename, Man* arr, int& n);
	friend int add(Man* arr, int& n);
	friend int remove(Man* arr, int& n);
	friend int edit(Man* arr, int& n);

};
int  menu();
int menu_f();
