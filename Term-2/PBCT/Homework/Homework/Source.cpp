#include "Header.h"
inline Data::Data() : age__(0), name__(""), eduction__(middle), question__(true), gender__(Man) {}
Data::Data(const Data& info) : age__(info.age__), name__(info.name__), eduction__(info.eduction__), question__(info.question__), gender__(info.gender__) {}
Data& Data::operator=(const Data& info) {
	if (&info == this) {
		name__ = info.name__;
		age__ = info.age__;
		gender__ = info.gender__;
		eduction__ = info.eduction__;
		question__ = info.question__;
	}
	return *this;
}
inline std::ostream& operator<<(std::ostream& out, const Data& info) {
	out << info.name__ << std::endl;
	out << info.age__ << std::endl;
	out << info.gender__ << std::endl;
	out << info.eduction__ << std::endl;
	out << info.question__;
	return out;
}
std::istream& operator>>(std::istream& fin, Data& info) {
	info.name__ = FromString<std::string>("| ������� ���� ���: ");
	info.gender__ = FromString<Gender>("| ������� ��� ��� (�/�/�)?: ");
	info.age__ = FromString<size_t>("| ������� ��� �������: ");
	info.eduction__ = FromString<Eduction_lvl>("| ����� � ��� �����������: ");
	info.question__ = FromString<bool>("| ����������� �� �� �������?: ");
	return fin;
}
void AddData(std::list<Data>& info) {
	Data person;
	person.name__ = FromString<std::string>("| ������� ���� ���: ");
	system("cls");
	person.gender__ = FromString<Gender>("| ������� ��� ��� (�/�/�)?: ");
	system("cls");
	person.eduction__ = FromString<Eduction_lvl>("| ����� � ��� �����������: ");
	system("cls");
	person.age__ = FromString<size_t>("| ������� ��� �������: ");
	system("cls");
	person.question__ = FromString<bool>("| ����������� �� �� �������?: ");
	system("cls");
	std::cout << "| �� �����: \n";
	std::cout << "���: " << person.name__ << std::endl;
	switch (person.gender__)
	{
	case 1: std::cout << "���: �������\n"; break;
	case 2: std::cout << "���: �������\n"; break;
	case 3: std::cout << "���: �����������\n"; break;
	default:
		break;
	}
	std::cout << "�������: " << person.age__ << std::endl;
	std::cout << "�����������: ";
	switch (person.eduction__)
	{
	case 1: std::cout << "���������\n"; break;
	case 2: std::cout << "�������\n"; break;
	case 3: std::cout << "������\n"; break;
	default:
		break;
	}

	if (person.question__)
		std::cout << "�����: ��" << std::endl;
	else
		std::cout << "�����: ���" << std::endl;
	if (!FromString<bool>("\n| ������ ����������?: ")) {
		std::cout << "| ����� � �����������. ������ �������!" << std::endl;
		return;
	}
	std::cout << "| ������ ������� ��������!" << std::endl;
	info.push_back(person);
}
void ReadFile(std::list<Data>& info) {
	std::ifstream fin("BasaData.txt");
	if (!fin.is_open()) {
		std::cout << "| ���� �� ������!\n";
		std::cout << "| ������ �����!\n";
		std::ofstream("BasaData.txt");
	}
	// ���� ������ ������� ����� ���� ����� �����(�����)
	else if (fin.peek() == EOF) {
		std::cout << "| ERROR: ���� ������!" << std::endl;
		return;
	}
	while (!fin.eof()) {
		Data person;
		std::getline(fin, person.name__);
		if (person.name__ == "****END***") {
			return;
		}
		fin >> person.age__;
		std::string temp;
		fin >> temp;
		switch (std::stoi(temp))
		{
		case 1: person.gender__ = Man; break;
		case 2: person.gender__ = Woman; break;
		case 3: person.gender__ = Neutral; break;
		default:
			break;
		}
		temp.clear();

		fin >> temp;
		switch (std::stoi(temp))
		{
		case 1: person.eduction__ = elementary; break;
		case 2: person.eduction__ = middle; break;
		case 3: person.eduction__ = higher; break;
		default:
			break;
		}
		fin >> person.question__;
		info.push_back(person);
		// ��-�� getline ���������
		fin.ignore();
		fin.clear();
	}
	fin.close();
}
void SendToFile(const std::list<Data>& info) {
	std::ofstream fin("BasaData.txt");
	if (!fin.is_open()) {
		std::cout << "| ���� �� ������!\n";
		std::cout << "| ������ �����!\n";
		std::ofstream("BasaData.txt");
	}
	for (auto it = info.begin(); it != info.end(); ++it) {
		fin << *it << std::endl;
	}
	fin << "****END***";
	fin.close();
}
void Data::Print() const {
	std::cout << "���: " << name__ << std::endl;
	switch (gender__)
	{
	case 1: std::cout << "���: �������\n"; break;
	case 2: std::cout << "���: �������\n"; break;
	case 3: std::cout << "���: �����������\n"; break;
	default:
		break;
	}
	std::cout << "�������: " << age__ << std::endl;
	std::cout << "�����������: ";
	switch (eduction__)
	{
	case 1: std::cout << "���������\n"; break;
	case 2: std::cout << "�������\n"; break;
	case 3: std::cout << "������\n"; break;
	default:
		break;
	}

	if (question__)
		std::cout << "�����: ��" << std::endl;
	else
		std::cout << "�����: ���" << std::endl;
}
void Print(const std::list<Data> info) {
	if (info.empty()) {
		std::cout << "| �����!" << std::endl;
		return;
	}
	auto it = info.begin();
	std::cout << std::endl << "\x1b[36m";
	for (; it != info.end(); ++it) {
		std::cout << "���: " << it->name__ << std::endl;
		switch (it->gender__) 
		{
		case 1: std::cout << "���: �������\n"; break;
		case 2: std::cout << "���: �������\n"; break;
		case 3: std::cout << "���: �����������\n"; break;
		default:
			break;
		}
		std::cout << "�������: " << it->age__ << std::endl;
		std::cout << "�����������: ";
		switch (it->eduction__)
		{
		case 1: std::cout << "���������\n"; break;
		case 2: std::cout << "�������\n"; break;
		case 3: std::cout << "������\n"; break;
		default:
			break;
		}

		if (it->question__)
			std::cout << "�����: ��" << std::endl;
		else
			std::cout << "�����: ���" << std::endl;
		std::cout << "------------------------------------\n";
	}
	std::cout << std::endl << "\x1b[0m";
}
void Analyis(const std::list<Data>& info) {
	auto it = info.begin();
	size_t countOldMan = 0;
	size_t countYoungWoman = 0;
	size_t countYoungMan = 0;
	for (; it != info.end(); ++it) {
		if (it->gender__ == Man && it->eduction__ == higher && it->age__ >= 40 && it->question__) {
			++countOldMan;
		}
		// ����������� ������ ������� (������ (���� ������� ���� �����) �� ����������� �� �������)
		else if (it->gender__ == Woman && it->age__ <= 30 && it->eduction__ == middle && !it->question__) {
			++countYoungWoman;
		}
		else if (it->gender__ == Man && it->age__ <= 25 && it->eduction__ == elementary && it->question__) {
			++countYoungMan;
		}
	}
	std::cout << std::endl << "\x1b[36m";
	std::cout << "====================================== ������ ======================================\n";
	std::cout << "M����� ������ 40 ���, ������� ������ �����������, �������� �� �� ������ ������:    | " << countOldMan << " ���." << std::endl;
	std::cout << "������ ������ 30 ���, ������� ������� �����������, �������� ��� �� ������ ������:  | " << countYoungWoman << " ���." << std::endl;
	std::cout << "������ ������ 25 ���, ������� ��������� �����������, �������� �� �� ������ ������: | " << countYoungMan << " ���." << std::endl;
	std::cout << std::endl << "\x1b[0m";
}
void Menu() {
	std::cout << "-*-*-*-*-*- Menu -*-*-*-*-*-\n";
	std::cout << "1. �������� �����������.\n"
		<< "2. ������ ������.\n"
		<< "3. ������ ������.\n"
		<< "4. ����� � ����.\n"
		<< "5. �����.\n";
}
