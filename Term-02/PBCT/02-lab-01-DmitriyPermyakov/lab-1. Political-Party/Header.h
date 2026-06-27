#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <Windows.h>
#include <iomanip>
class Party
{
	char* name;
	int countMemder{};
	double capital{};
	size_t IQ{};
public:
	Party() { size_t sizeName = 20; name = new char[sizeName]; strcpy_s(name, sizeName, ""); }

	Party(const Party& party)
	{
		std::cout << "Конструктор копирования\n";
		name = new char[strlen(party.name)+1];
		strcpy_s(name, strlen(party.name)+1, party.name);
		countMemder = party.countMemder;
		capital = party.capital;
		IQ = party.IQ;
	}

	~Party() { delete[] name; }


	void SetName(char* name) { strcpy_s(this->name, strlen(name)+1, name); }
	void SetCountMemder(int countMemder) { this->countMemder = countMemder; }
	void SetCapital(double capital) { this->capital = capital; }
	void SetIQ(size_t IQ) { this->IQ = IQ; }
	char* GetName() { return name; }
	int GetCountMemder() { return countMemder; }
	double GetCapital() { return capital; }
	size_t GetIQ() { return IQ; }

	friend size_t Read(Party* party);
	Party& operator = (const Party& party);
	friend bool operator > (const Party& party, const Party& party2);
	friend std::ostream& operator << (std::ostream& fin, const Party& party);
	friend void Add(Party* party, size_t& size);
	friend void SaveToFile(Party* party, const size_t& size);
	friend void Edit(Party* party, const size_t& size);
	friend void Sort(Party* party, const size_t& size);
	friend void Print(Party* party, const size_t& size);
	friend void Delete(Party* party, size_t& size);
};

int Menu();