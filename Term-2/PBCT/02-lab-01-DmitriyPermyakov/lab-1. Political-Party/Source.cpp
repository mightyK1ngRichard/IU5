#include "Header.h"

size_t Read(Party* party)
{
	size_t SizeFile = 0;
	std::ifstream fin("party.txt");
	if (!fin.is_open())
	{
		std::cout << "\x1b[31mОшибка открытия!\x1b[0m\n";
		exit(1);
	}
	char* help = new char[100];

	// пропуск шапку
	for (size_t i = 0; i < 4; i++)
		fin >> help;

	size_t i = 0;
	while (!fin.eof())
	{
		fin >> help;
		strcpy_s(party[i].name, strlen(help)+1, help);
		//planet.SetName(help);

		fin >> help;
		party[i].countMemder = atoi(help);
		//planet.SetDimeter(atoi(help));

		fin >> help;
		party[i].capital = atoi(help);
		//planet.SetLife(atoi(help));

		fin >> help;
		party[i].IQ = atoi(help);
		//planet.SetSatellite(atoi(help));

		++SizeFile; ++i;
	}
	delete[] help;
	return SizeFile;
}

void Add(Party* party, size_t& size)
{
	std::cout << "Введите имя партии: ";
	std::cin >> party[size].name;
	std::cout << "Введите число участников: ";
	std::cin >> party[size].countMemder;
	std::cout << "Введите капитал: ";
	std::cin >> party[size].capital;
	std::cout << "Введите уровень IQ участника: ";
	std::cin >> party[size].IQ;
	++size;
}

void Delete(Party* party, size_t& size)
{
	Sort(party, size);
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
		if (strcmp(party[middle].name, word) == 0)
		{
			flag = true;
			break;
		}
		if (strcmp(party[middle].name, word) > 0)
			r = middle - 1;
		else
			l = middle + 1;
	}

	if (flag)
	{
		for (size_t i = middle; i < size - 1; i++)
		{
			strcpy_s(party[i].name, strlen(party[i + 1].name) + 1, party[i + 1].name);
			party[i].countMemder = party[i + 1].countMemder;
			party[i].capital = party[i + 1].capital;
			party[i].IQ = party[i + 1].IQ;
		}
		--size;
	}
	else
		std::cout << "\x1b[31mNot found\x1b[0m\n\n";
}

void SaveToFile(Party* party, const size_t& size)
{
	std::fstream fin("party.txt", std::ios::out);
	fin << "Название \tЧисло \tКапитал \t   IQ\n";
	//fin << party;
	for (size_t i = 0; i < size; i++)
	{
		fin << party[i];
		if (i + 1 != size)
			fin << std::endl;
	}
	fin.close();
}

void Edit(Party* party, const size_t& size)
{
	char* timeName = new char[30];
	bool NameWasFound = false;
	do
	{
		std::cout << "Данные какой партии Вы хотите изменить?: ";
		std::cin >> timeName;
		for (size_t i = 0; i < size; i++)
		{
			bool ok = false;
			if (!strcmp(party[i].name, timeName))
			{
				std::cout << "Вы хотите изм имя партии?(1/0): ";
				std::cin >> ok;
				if (ok)
				{
					std::cout << "Введите новое имя: ";
					std::cin >> party[i].name;
				}

				std::cout << "Вы хотите изм диаметр?(1/0): ";
				std::cin >> ok;
				if (ok)
				{
					std::cout << "Введите кол-во участников: ";
					std::cin >> party[i].countMemder;
				}

				std::cout << "Вы хотите изменить капитал?(1/0): ";
				std::cin >> ok;
				if (ok)
				{
					std::cout << "Введите новую жизнь: ";
					std::cin >> party[i].capital;
				}

				std::cout << "Вы хотите изм кол-во спутников?(1/0): ";
				std::cin >> ok;
				if (ok)
				{
					std::cout << "Введите новое IQ: ";
					std::cin >> party[i].IQ;
				}
				NameWasFound = true;
			}
		}

		if (!NameWasFound)
			std::cout << "Планета не найдена! Повторите попытку\n\n";
	} while (!NameWasFound);
}

void Sort(Party* party, const size_t& size)
{
	for (size_t i = 1; i < size; i++)
	{
		for (size_t i2 = 0; i2 < size - i; i2++)
		{
			if (party[i2] > party[i2 + 1])
			{
				std::swap(party[i2].name, party[i2 + 1].name);
				std::swap(party[i2].countMemder, party[i2 + 1].countMemder);
				std::swap(party[i2].capital, party[i2 + 1].capital);
				std::swap(party[i2].IQ, party[i2 + 1].IQ);
			}
		}
	}
}

void Print(Party* party, const size_t& size)
{
	Sort(party, size);
	std::cout << "\n-*-*-*-*-*-*-*-*-*-*-*-Print-*-*-*-*-*-*-*-*-*-*-*-*\n";
	std::cout << "\x1b[31mНазвание \tЧисло   \t Капитал \t   IQ\x1b[0m\x1b[36m\n";
	for (size_t i = 0; i < size; i++)
	{
		int length = strlen(party[i].name);
		std::cout << party[i].GetName() << std::setw(22 - length);
		std::cout << party[i].GetCountMemder() << std::setw(16);
		std::cout << party[i].GetCapital() << std::setw(14);
		std::cout << party[i].GetIQ() << std::endl;
	}
	std::cout << "\x1b[0m-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
	std::cout << std::endl;
}

bool operator > (const Party& party, const Party& party2)
{
	return (strcmp(party.name, party2.name) > 0);
}

std::ostream& operator << (std::ostream& fin, const Party& party)
{
	int length = strlen(party.name);
	fin << party.name << std::setw(22 - length);
	fin << party.countMemder << std::setw(13);
	fin << party.capital << std::setw(13);
	fin << party.IQ;
	return fin;
}

Party& Party::operator = (const Party& party)
{
	delete name;
	if (this != &party)
	{
		std::cout << "Оператор присваивания\n";
		name = new char[strlen(party.name)+1];
		strcpy_s(name, strlen(party.name)+1, party.name);
		countMemder = party.countMemder;
		capital = party.capital;
		IQ = party.IQ;
	}
	else
		std::cout << "Самоприсваивание\n";

	return *this;
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