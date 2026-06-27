#include "Header.h"

int menu()
{
	cout << "-*-*-*- MENU -*-*-*-*\n"
		 << "1. Добавление сотрудника\n"
		 << "2. Удаление coтpyдникa\n"
		 << "3. Поиск сотрудника\n"
		 << "4. корректировка сведений\n"
		 << "5. Вывод базы на экран\n" 
		 << "6. Вывод базы в файл\n"
	     << "7. Выход\n";
	cout << "Для выбора операции введите цифру от 1 до 7: ";
	int resp;
	cin >> resp;
	cin.clear();
	cin.ignore(10, '\n');
	cout << endl;
	return resp;
}

int add(Man* arr, int& n)
{
	cout << "Введите имя: ";
	cin >> arr[n].pName;
	cout << "Введите год: ";
	cin >> arr[n].birth_year;
	cout << "Введите зп: ";
	cin >> arr[n].pay;
	++n;
	return n;
}

int remove(Man* arr, int& n)
{
	cout << "Введите имя для удаления: ";
	char name[20];
	cin >> name;
	for (size_t i = 0; i < n; i++)
	{
		if (!strcmp(arr[i].pName, name))
		{
			for (size_t j = i+1; j < n; j++)
			{
				strcpy_s(arr[i].pName, l_name, arr[j].pName);
				arr[i].pay = arr[j].pay;
				arr[i].birth_year = arr[j].birth_year;
			}
			--n;
		}
	}

	return n;
}

// Чтение базы из файла
int read_dbase(char* filename, Man* arr, int& n)
{
	ifstream fin(filename, ios::in);
	if (!fin)
	{
		cout << "Heт файла " << filename << endl;
		return 1;
	}
	fin >> n;
	if (n > 100)
	{
		cout << "Переполнение БД. n= " << n << endl;
		return 1;
	}
	for (int i = 0; i < n; i++)
		fin >> arr[i].pName >> arr[i].birth_year >> arr[i].pay;

	fin.close();
	return 0;
}

int edit(Man* arr, int& n)
{
	cout << "Кого вы хотите изменить? ";
	char name[20];
	cin >> name;
	for (size_t i = 0; i < n; i++)
	{
		bool nice;
		if (!strcmp(arr[i].pName, name))
		{
			cout << " Найден: " << arr[i].pName << ' ' << arr[i].birth_year << ' ' << arr[i].pay << endl;
			cout << "изменить имя? (1/0): ";
			cin >> nice;
			if (nice)
			{
				cout << "Введите новое имя: ";
				cin >> arr[i].pName;
			}
			
			cout << "изменить год? (1/0): ";
			cin >> nice;
			if (nice)
			{
				cout << "Введите новый год: ";
				cin >> arr[i].birth_year;
			}
			
			cout << "Изменить зарплату? (1/0): ";
			cin >> nice;
			if (nice)
			{
				cout << "Введите новую з/п: ";
				cin >> arr[i].pay;
			}
		}
	}
	return n;
}

//Вывод базы в файл
int write_dbase(char* filename, Man* arr, int n)
{
	ofstream fout(filename, ios::out);
	if (!fout)
	{
		cout << "Ошибка открытия файла" << endl;
		return 1;
	}
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << arr[i].pName << ' ' << arr[i].birth_year << ' ' << arr[i].pay;
		if (i != n - 1)
			fout << endl;
	}

	fout.close();
	return 0;
}

//Вывод базы на экран
void print_dbase(Man* arr, int n)
{
	cout << " База Данных " << endl;
	for (int i = 0; i < n; i++)
		cout << setw(3) << i + 1 << ". " << arr[i].pName << setw(15 - strlen(arr[i].pName))
		<< arr[i].birth_year << setw(10) << arr[i].pay << endl;
	cout << endl;
}

// Поиск сотрудника в списке по фамилии. возвращает индес элемента с данными о сотруднике в БД,реализованной в виде массива
int find(Man* arr, int n, char* name) 
{
	int ind = -1;
	for (int i = 0; i < n; i++)
		if (!strcmp(arr[i].pName, name))
		{
			cout << arr[i].pName << setw(20 - strlen(arr[i].pName) + 6)
				<< arr[i].birth_year << setw(10) << arr[i].pay << endl;
			ind = i;
		}
	return ind;
}

// Поиск и вывод более старших по возрасту сотрудников
int find(Man* arr, int n, int birth_year)
{
	int ind = -1;
	for (int i = 0; i < n; i++)
		if (arr[i].birth_year < birth_year)
		{
			ind = i;
			cout << arr[i].pName << setw(20 - strlen(arr[i].pName) + 6)
				<< arr[i].birth_year << setw(10) << arr[i].pay << endl;
		}
	return ind;
}

// Поиск и вывод сотрудников с окладом, большим чем "pay"
int find(Man* arr, int n, float pay)
{
	int ind = -1;
	for (int i = 0; i < n; i++)
		if (arr[i].pay > pay)
		{
			ind = i;
			cout << arr[i].pName << setw(20 - strlen(arr[i].pName) + 6)
				<< arr[i].birth_year << setw(10) << arr[i].pay << endl;
		}
	return ind;
}

int menu_f()
{
	cout << "\n----------------- ПОИСК -----------------\n";
	cout << "1 - поиск по фамилии	 2 - по году рождения\n"
		<< "3 - по окладу		 4 - конец поиска\n ";
	cout << "Для выбора операции введите число от 1 до 4\n";
	int resp;
	cin >> resp;
	cin.clear();
	cin.ignore(10, '\n');
	return resp;
}

// Поиск
void find_man(Man* arr, int n)
{
	char buf[l_name];
	int birth_year;
	float pay;

	while (true)
	{
		switch (menu_f())
		{
		case 1: cout << "Введите фамилию сотрудника\n";
			cin >> buf;
			if (find(arr, n, buf) < 0)
				cout << "Сотрудника с фамилией " << buf << " в списке нет\n";
			break;
		case 2: cout << "Введите год рождения" << endl;
			cin >> birth_year;
			if (find(arr, n, birth_year) < 0)
				cout << "В списке нет сотрудников, родившихся до "
				<< birth_year << " года\n";
			break;
		case 3: cout << "Введите оклад" << endl;
			cin >> pay;
			if (find(arr, n, pay) < 0)
				cout << "В списке нет сотрудников с окладом, большим "
				<< pay << " руб.\n";
			break;
		case 4: return;
		default:
			cout << "Неверный ввод\n";
		}

	}
}
