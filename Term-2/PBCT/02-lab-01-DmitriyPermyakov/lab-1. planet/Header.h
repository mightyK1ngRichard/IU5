#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <Windows.h>
#include <iomanip>
#define SIZE 20
class Planet
{
	char* name;
	double diameter{};
	int life{};
	int satellite{};
public:
	Planet() { size_t sizeName = 20; name = new char[sizeName]; strcpy_s(name, sizeName, ""); }

	Planet(const Planet& planet) 
	{
		std::cout << "Конструктор копирования\n";
		
		name = new char[SIZE];
		strcpy_s(name, SIZE, planet.name);
		diameter = planet.diameter;
		life = planet.life;
		satellite = planet.satellite;
		
	}

	~Planet() { delete[] name; }


	void SetName(char* name) { strcpy_s(this->name, SIZE, name); }
	void SetDimeter(double diameter) { this->diameter = diameter; }
	void SetLife(int life) { this->life = life; }
	void SetSatellite(int satellite) { this->satellite = satellite; }
	char* GetName() { return name; }
	double GetDimeter() { return diameter; }
	int GetLife() { return life; }
	int GetSatellite() { return satellite; }

	friend size_t Read(Planet* planet);
	Planet& operator = (const Planet& planet);
	friend bool operator > (const Planet& planet, const Planet& planet2);
	friend std::ofstream& operator << (std::ofstream fin, const Planet& planet);
	friend void Add(Planet* planet, size_t& size);
	friend void SaveToFile(Planet* planet, const size_t& size);
	friend void Edit(Planet* planet, const size_t& size);
	friend void Sort(Planet* planet, const size_t& size);
	friend void Print(Planet* planet, const size_t& size);
	friend void Delete(Planet* planet, size_t& size);
};

int Menu();
