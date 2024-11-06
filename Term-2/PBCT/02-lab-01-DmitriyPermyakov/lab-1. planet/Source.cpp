#include "Header.h"

size_t Read(Planet* planet)
{
	size_t SizeFile = 0;
	std::ifstream fin("data.txt");
	if (!fin.is_open())
	{
		std::cout << "\x1b[31mОшибка открытия!\x1b[0m\n";
		exit(1);
	}
	char* help = new char [100];

	// пропуск шапку
	for (size_t i = 0; i < 4; i++)
		fin >> help;
		
	size_t i = 0;
	while (!fin.eof())
	{
		fin >> help;
		strcpy_s(planet[i].name, SIZE, help);
		//planet.SetName(help);

		fin >> help;
		planet[i].diameter = atoi(help);
		//planet.SetDimeter(atoi(help));

		fin >> help;
		planet[i].life = atoi(help);
		//planet.SetLife(atoi(help));

		fin >> help;
		planet[i].satellite = atoi(help);
		//planet.SetSatellite(atoi(help));

		++SizeFile; ++i;
	}
	return SizeFile;
}

void Add(Planet* planet, size_t& size)
{
	std::cout << "Введите имя планеты: ";
	std::cin >> planet[size].name;
	std::cout << "Введите диаметр: ";
	std::cin >> planet[size].diameter;
	std::cout << "Введите жизнь: ";
	std::cin >> planet[size].life;
	std::cout << "Введите кол-во спутников: ";
	std::cin >> planet[size].satellite;
	++size;
}

void Delete(Planet* planet, size_t& size)
{
	Sort(planet, size);
	bool flag = false;
	char word[30];
	std::cout << "Enter the word for the deletion: ";
	std::cout << "\x1b[35m";
	std::cin >> word;
	std::cout << "\x1b[0m";
	size_t l = 0;
	size_t r = size;
	size_t middle;
	while (l <= r)
	{
		middle = (l + r) / 2;
		if (strcmp(planet[middle].name, word) == 0)
		{
			flag = true;
			break;
		}
		if (strcmp(planet[middle].name, word) > 0)
			r = middle - 1;
		else
			l = middle + 1;
	}

	if (flag)
	{
		for (size_t i = middle; i < size - 1; i++)
		{
			strcpy_s(planet[i].name, strlen(planet[i + 1].name) + 1, planet[i + 1].name);
			planet[i].diameter = planet[i + 1].diameter;
			planet[i].life = planet[i + 1].life;
			planet[i].satellite = planet[i + 1].satellite;
		}
		--size;
	}
	else
		std::cout << "\x1b[31mNot found\x1b[0m\n\n"; 
}

void SaveToFile(Planet* planet, const size_t& size)
{
	std::ofstream fin("data.txt");
	fin << "Название \tДиаметр \tЖизнь \t   Спутники\n";
	for (size_t i = 0; i < size; i++)
	{
		int length = strlen(planet[i].name);
		fin << planet[i].name << std::setw(22 - length);
		fin << planet[i].diameter << std::setw(13);
		fin << planet[i].life << std::setw(13);
		fin << planet[i].satellite;
		if (i + 1 != size)
			fin << std::endl;
	}
	fin.close();
}

void Edit(Planet* planet, const size_t& size)
{
	std::ofstream fin("data.txt");
	char* timeName = new char[SIZE];
	bool NameWasFound = false;
	do
	{
	std::cout << "Данные какой планеты Вы хотите изменить?: ";
	std::cin >> timeName;
	for (size_t i = 0; i < size; i++)
	{
		bool ok = false;
		if (!strcmp(planet[i].name, timeName))
		{
			std::cout << "Вы хотите изм имя?(1/0): ";
			std::cin >> ok;
			if (ok)
			{
				std::cout << "Введите новое имя: ";
				std::cin >> planet[i].name;
			}

			std::cout << "Вы хотите изм диаметр?(1/0): ";
			std::cin >> ok;
			if (ok)
			{
				std::cout << "Введите новый диаметр: ";
				std::cin >> planet[i].diameter;
			}

			std::cout << "Вы хотите изм жизнь?(1/0): ";
			std::cin >> ok;
			if (ok)
			{
				std::cout << "Введите новую жизнь: ";
				std::cin >> planet[i].life;
			}

			std::cout << "Вы хотите изм кол-во спутников?(1/0): ";
			std::cin >> ok;
			if (ok)
			{
				std::cout << "Введите новое кол-во спутников: ";
				std::cin >> planet[i].satellite;
			}
			NameWasFound = true;
		}
	}

	if (!NameWasFound)
		std::cout << "Планета не найдена! Повторите попытку\n\n";
	} while (!NameWasFound);
	
	fin.close();
}

void Sort(Planet* planet, const size_t& size)
{
	for (size_t i = 1; i < size; i++)
	{
		for (size_t i2 = 0; i2 < size - i; i2++)
		{
			if (planet[i2] > planet[i2 + 1])
			{
				std::swap(planet[i2].name, planet[i2 + 1].name);
				std::swap(planet[i2].diameter, planet[i2 + 1].diameter);
				std::swap(planet[i2].life, planet[i2 + 1].life);
				std::swap(planet[i2].satellite, planet[i2 + 1].satellite);
			}
		}
	}
}

void Print(Planet* planet, const size_t& size)
{
	Sort(planet, size);
	std::cout << "\n-*-*-*-*-*-*-*-*-*-*-*-Print-*-*-*-*-*-*-*-*-*-*-*-*\n";
	std::cout << "\x1b[31mНазвание \tДиаметр \tЖизнь \t   Спутники\x1b[0m\x1b[36m\n";
	for (size_t i = 0; i < size; i++)
	{
		int length = strlen(planet[i].name);
		std::cout << planet[i].GetName() << std::setw(22 - length);
		std::cout << planet[i].GetDimeter() << std::setw(13);
		std::cout << planet[i].GetLife() << std::setw(13);
		std::cout << planet[i].GetSatellite() << std::endl;
	}
	std::cout << "\x1b[0m-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	std::cout << std::endl;
}

bool operator > (const Planet& planet, const Planet& planet2)
{
	return (strcmp(planet.name, planet2.name) > 0);
}

std::ofstream& operator << (std::ofstream fin, const Planet& planet)
{
	int length = strlen(planet.name);
	fin << planet.name << std::setw(22 - length);
	fin << planet.diameter << std::setw(13);
	fin << planet.life << std::setw(13);
	fin << planet.satellite;
	return fin;
}

int Menu()
{
	std::cout << "*-*-*-*- MENU -*-*-*-*\n"
		<< "1. Добавить\n"
		<< "2. Редактировать\n"
		<< "3. Сортировать\n"
		<< "4. Вывод в файл\n"
		<< "5. Печать\n"
		<< "6. Выход\n"
		<< "8. Удаление\n";
	int num;
	std::cout << "Выберите пунт: ";
	std::cin >> num;
	return num;
}

Planet& Planet::operator = (const Planet& planet)
{
	delete this;
	if (this != &planet)
	{
		std::cout << "Оператор присваивания\n";
		name = new char[SIZE];
		strcpy_s(name, SIZE, planet.name);
		diameter = planet.diameter;
		life = planet.life;
		satellite = planet.satellite;
	}
	else
		std::cout << "Самоприсваивание\n";

	return *this;
}
