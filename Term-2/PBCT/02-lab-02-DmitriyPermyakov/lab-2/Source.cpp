#include "Header.h"

int menu()
{
	cout << "-*-*-*- MENU -*-*-*-*\n"
		 << "1. ���������� ����������\n"
		 << "2. �������� co�py����a\n"
		 << "3. ����� ����������\n"
		 << "4. ������������� ��������\n"
		 << "5. ����� ���� �� �����\n" 
		 << "6. ����� ���� � ����\n"
	     << "7. �����\n";
	cout << "��� ������ �������� ������� ����� �� 1 �� 7: ";
	int resp;
	cin >> resp;
	cin.clear();
	cin.ignore(10, '\n');
	cout << endl;
	return resp;
}

int add(Man* arr, int& n)
{
	cout << "������� ���: ";
	cin >> arr[n].pName;
	cout << "������� ���: ";
	cin >> arr[n].birth_year;
	cout << "������� ��: ";
	cin >> arr[n].pay;
	++n;
	return n;
}

int remove(Man* arr, int& n)
{
	cout << "������� ��� ��� ��������: ";
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

// ������ ���� �� �����
int read_dbase(char* filename, Man* arr, int& n)
{
	ifstream fin(filename, ios::in);
	if (!fin)
	{
		cout << "He� ����� " << filename << endl;
		return 1;
	}
	fin >> n;
	if (n > 100)
	{
		cout << "������������ ��. n= " << n << endl;
		return 1;
	}
	for (int i = 0; i < n; i++)
		fin >> arr[i].pName >> arr[i].birth_year >> arr[i].pay;

	fin.close();
	return 0;
}

int edit(Man* arr, int& n)
{
	cout << "���� �� ������ ��������? ";
	char name[20];
	cin >> name;
	for (size_t i = 0; i < n; i++)
	{
		bool nice;
		if (!strcmp(arr[i].pName, name))
		{
			cout << " ������: " << arr[i].pName << ' ' << arr[i].birth_year << ' ' << arr[i].pay << endl;
			cout << "�������� ���? (1/0): ";
			cin >> nice;
			if (nice)
			{
				cout << "������� ����� ���: ";
				cin >> arr[i].pName;
			}
			
			cout << "�������� ���? (1/0): ";
			cin >> nice;
			if (nice)
			{
				cout << "������� ����� ���: ";
				cin >> arr[i].birth_year;
			}
			
			cout << "�������� ��������? (1/0): ";
			cin >> nice;
			if (nice)
			{
				cout << "������� ����� �/�: ";
				cin >> arr[i].pay;
			}
		}
	}
	return n;
}

//����� ���� � ����
int write_dbase(char* filename, Man* arr, int n)
{
	ofstream fout(filename, ios::out);
	if (!fout)
	{
		cout << "������ �������� �����" << endl;
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

//����� ���� �� �����
void print_dbase(Man* arr, int n)
{
	cout << " ���� ������ " << endl;
	for (int i = 0; i < n; i++)
		cout << setw(3) << i + 1 << ". " << arr[i].pName << setw(15 - strlen(arr[i].pName))
		<< arr[i].birth_year << setw(10) << arr[i].pay << endl;
	cout << endl;
}

// ����� ���������� � ������ �� �������. ���������� ����� �������� � ������� � ���������� � ��,������������� � ���� �������
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

// ����� � ����� ����� ������� �� �������� �����������
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

// ����� � ����� ����������� � �������, ������� ��� "pay"
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
	cout << "\n----------------- ����� -----------------\n";
	cout << "1 - ����� �� �������	 2 - �� ���� ��������\n"
		<< "3 - �� ������		 4 - ����� ������\n ";
	cout << "��� ������ �������� ������� ����� �� 1 �� 4\n";
	int resp;
	cin >> resp;
	cin.clear();
	cin.ignore(10, '\n');
	return resp;
}

// �����
void find_man(Man* arr, int n)
{
	char buf[l_name];
	int birth_year;
	float pay;

	while (true)
	{
		switch (menu_f())
		{
		case 1: cout << "������� ������� ����������\n";
			cin >> buf;
			if (find(arr, n, buf) < 0)
				cout << "���������� � �������� " << buf << " � ������ ���\n";
			break;
		case 2: cout << "������� ��� ��������" << endl;
			cin >> birth_year;
			if (find(arr, n, birth_year) < 0)
				cout << "� ������ ��� �����������, ���������� �� "
				<< birth_year << " ����\n";
			break;
		case 3: cout << "������� �����" << endl;
			cin >> pay;
			if (find(arr, n, pay) < 0)
				cout << "� ������ ��� ����������� � �������, ������� "
				<< pay << " ���.\n";
			break;
		case 4: return;
		default:
			cout << "�������� ����\n";
		}

	}
}
