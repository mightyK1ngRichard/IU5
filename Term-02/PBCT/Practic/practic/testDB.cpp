#include <iostream>
#include <iomanip>
#include"dbmsLib.h"
#include <Windows.h>

int menu() {
	std::cout << "================= СУБД ТОВАРОВ ==============================\n";
	std::cout << "1 - Чтение таблицы об учёте склада и таблицы продаж из файла\n";
	std::cout << "2 - Печать таблиц\n";
	std::cout << "3 - Оформление заказа\n";
	std::cout << "4 - Запись в файл\n";
	std::cout << "5 - Добавить продукт\n";
	std::cout << "6 - Выход\n";
	std::cout << "=============================================================\n";
	int choice; 
	bool flag; 
	string buff;
	while (true) {
		std::cout << "Выберите пункт: ";
		std::cin >> buff;
		for (auto el : buff) {
			if (isalpha(el)) {
				std::cout << "Неверный ввод!\n";
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
	// читаем файлы заранее для удобства пользования
	products.ReadDBTable("products.txt");
	order.ReadDBTable("order.txt");

	while (true) {
		switch (menu()) {
		case 1: 
			order.ReadDBTable("order.txt"); 
			products.ReadDBTable("products.txt");
			break;

		case 2: 
			// цвет консоли для удобства
			std::cout << "\x1b[36m"; 
			products.PrintTable(80); 
			std::cout << "\x1b[0m";
			std::cout << "\x1b[33m";
			order.PrintTable(80); 
			std::cout << "\x1b[0m" << std::endl;
			break;

		case 3:
			std::cout << "| Введите ID продукта: ";
			std::cin >> productID;
			vec = products.IndexOfRecord(&productID, (std::string)"ProductID");

			// если вернули пустой вектор, заказа не суш
			if (vec.size() == 0) {
				std::cout << "\x1b[31m";
				std::cout << "| ID товара не найден!" << std::endl;
				std::cout << "\x1b[0m";
				break;
			}

			row = products.GetRow(vec[0]);
			buff = row[(std::string)"Count of Products"];
			// кол-во товара в таблице
			buff_ = *(int*)buff;

			do {
				std::cout << "| Товар от \"" << *(string*)row[(std::string)"ProductName"] << "\"";
				std::cout << " доступно \x1b[35m" << buff_ << "\x1b[0m шт. товара" << std::endl;
				std::cout << "| Введите кол-во: ";
				std::cin >> counter;
				help_wish = false;
				// если кол-во введённого товара превышает кол-во на складе
				if (counter > buff_) {
					std::cout << "\x1b[31m";
					std::cout << "| Такого кол-во товара нету!" << std::endl;
					std::cout << "| Вы ввели на " << counter - buff_ << " шт. больше" << std::endl;
					std::cout << "\x1b[0m";
					std::cout << "| Вы хотите повторить ввод?(1/0): ";
					std::cin >> help_wish;
				}
			} while (help_wish);
			if (!help_wish && counter > buff_) {
				break;
			}

			// получаем новое кол-во товара
			adress = dbmsLib::GetValue((char*)to_string(buff_ - counter).c_str(), (string)"Count of Products", products.GetHeader());
			row[(std::string)"Count of Products"] = adress;	
			products.AddRow(row, vec[0]);
			std::cout << "\x1b[36m";
			products.PrintTable(80);
			std::cout << "\x1b[0m";

			std::cout << "| Введите дату заказа: ";
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
			std::cout << "| Данные успешно занесены!" << std::endl << std::endl;
			break;

		// добавление в файл нового продукта
		case 5:			
			std::cout << "ID: ";
			std::cin >> ID_new_product;
			row[(std::string)"ProductID"] = (void*)(&ID_new_product);
			
			std::cout << "Кол-во: ";
			std::cin >> count_new_product;
			row[(std::string)"Count of Products"] = (void*)(&count_new_product);

			std::cout << "Имя: ";
			std::cin >> name_new_product;
			row[(std::string)"ProductName"] = (void*)(&name_new_product);
			products.AddRow(row, products.GetSize());

			// сразу заносим в файл и считываем его для удобства показа программы
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
