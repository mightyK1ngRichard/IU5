#include <iostream>
#include <iomanip>
#include"dbmsLib.h"
#include <Windows.h>

int menu() {
	std::cout << "================= ���� ������� ==============================\n";
	std::cout << "1 - ������ ������� �� ����� ������ � ������� ������ �� �����\n";
	std::cout << "2 - ������ ������\n";
	std::cout << "3 - ���������� ������\n";
	std::cout << "4 - ������ � ����\n";
	std::cout << "5 - �������� �������\n";
	std::cout << "6 - �����\n";
	std::cout << "=============================================================\n";
	int choice; 
	bool flag; 
	string buff;
	while (true) {
		std::cout << "�������� �����: ";
		std::cin >> buff;
		for (auto el : buff) {
			if (isalpha(el)) {
				std::cout << "�������� ����!\n";
				flag = false;
				break;
			}
			else {
				flag = true;
			}
		}
		if (flag) {
			choice = stoi(buff);
			break;
		}
	}
	return choice;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	dbmsLib::DBTableTxt products("products.txt");
	dbmsLib::DBTableTxt order("order.txt");
	dbmsLib::Row row;
	std::vector<int> vec;
	size_t counter;
	std::string date_order;
	void* adress;
	void* buff;
	int buff_;
	int productID;
	bool help_wish;

	int count_new_product;
	int ID_new_product;
	string name_new_product;
	// ������ ����� ������� ��� �������� �����������
	products.ReadDBTable("products.txt");
	order.ReadDBTable("order.txt");

	while (true) {
		switch (menu()) {
		case 1: 
			order.ReadDBTable("order.txt"); 
			products.ReadDBTable("products.txt");
			break;

		case 2: 
			// ���� ������� ��� ��������
			std::cout << "\x1b[36m"; 
			products.PrintTable(80); 
			std::cout << "\x1b[0m";
			std::cout << "\x1b[33m";
			order.PrintTable(80); 
			std::cout << "\x1b[0m" << std::endl;
			break;

		case 3:
			std::cout << "| ������� ID ��������: ";
			std::cin >> productID;
			vec = products.IndexOfRecord(&productID, (std::string)"ProductID");

			// ���� ������� ������ ������, ������ �� ���
			if (vec.size() == 0) {
				std::cout << "\x1b[31m";
				std::cout << "| ID ������ �� ������!" << std::endl;
				std::cout << "\x1b[0m";
				break;
			}

			row = products.GetRow(vec[0]);
			buff = row[(std::string)"Count of Products"];
			// ���-�� ������ � �������
			buff_ = *(int*)buff;

			do {
				std::cout << "| ����� �� \"" << *(string*)row[(std::string)"ProductName"] << "\"";
				std::cout << " �������� \x1b[35m" << buff_ << "\x1b[0m ��. ������" << std::endl;
				std::cout << "| ������� ���-��: ";
				std::cin >> counter;
				help_wish = false;
				// ���� ���-�� ��������� ������ ��������� ���-�� �� ������
				if (counter > buff_) {
					std::cout << "\x1b[31m";
					std::cout << "| ������ ���-�� ������ ����!" << std::endl;
					std::cout << "| �� ����� �� " << counter - buff_ << " ��. ������" << std::endl;
					std::cout << "\x1b[0m";
					std::cout << "| �� ������ ��������� ����?(1/0): ";
					std::cin >> help_wish;
				}
			} while (help_wish);
			if (!help_wish && counter > buff_) {
				break;
			}

			// �������� ����� ���-�� ������
			adress = dbmsLib::GetValue((char*)to_string(buff_ - counter).c_str(), (string)"Count of Products", products.GetHeader());
			row[(std::string)"Count of Products"] = adress;	
			products.AddRow(row, vec[0]);
			std::cout << "\x1b[36m";
			products.PrintTable(80);
			std::cout << "\x1b[0m";

			std::cout << "| ������� ���� ������: ";
			std::cin >> date_order;
			adress = dbmsLib::GetValue((char*)date_order.c_str(), (std::string)"Date", order.GetHeader());
			row[(std::string)"Date"] = adress;

			adress = dbmsLib::GetValue((char*)to_string(counter).c_str(), (std::string)"Count of Products", products.GetHeader());
			row[(std::string)"Count of Products"] = adress;

			order.AddRow(row, order.GetSize());
			std::cout << "\x1b[33m";
			order.PrintTable(80);
			std::cout << "\x1b[0m";
			break;

		case 4: 
			//products.WriteDBTable("products.txt"); 
			//order.WriteDBTable("order.txt"); 
			std::cout << "| ������ ������� ��������!" << std::endl << std::endl;
			break;

		// ���������� � ���� ������ ��������
		case 5:			
			std::cout << "ID: ";
			std::cin >> ID_new_product;
			row[(std::string)"ProductID"] = (void*)(&ID_new_product);
			
			std::cout << "���-��: ";
			std::cin >> count_new_product;
			row[(std::string)"Count of Products"] = (void*)(&count_new_product);

			std::cout << "���: ";
			std::cin >> name_new_product;
			row[(std::string)"ProductName"] = (void*)(&name_new_product);
			products.AddRow(row, products.GetSize());

			// ����� ������� � ���� � ��������� ��� ��� �������� ������ ���������
			products.WriteDBTable("products.txt");
			products.ReadDBTable("products.txt");
			break;

		case 6:
			return 0;
			exit(0);

		case 7:
			system("cls");
			break;
		default: std::cout << "| ERROR!" << std::endl;
		}
	}
}
