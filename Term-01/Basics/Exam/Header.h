#pragma once
#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "data.h"
#include "User.h"
#include "game.h"

template <typename T>
void PrintArr(T** arr, const size_t& row, const size_t& column) {
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < column; j++) {
			std::cout << arr[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}
template <typename T>
T** CreatArr(const size_t& row, const size_t& column) {
	T** arr = new T * [row];
	for (size_t i = 0; i < row; ++i) {
		arr[i] = new T[column];
		for (size_t j = 0; j < column; ++j) {
			arr[i][j] = 0;
		}
	}
	return arr;
}
template <>
std::string** CreatArr(const size_t& row, const size_t& column) {
	std::string** arr = new std::string * [row];
	for (size_t i = 0; i < row; ++i) {
		arr[i] = new std::string[column];
	}
	return arr;
}
template <typename T>
void FillArr(T** arr, const size_t& row, const size_t& column) {}
template <>
void FillArr(std::string** arr, const size_t& row, const size_t& column) {
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < column; ++j) {
			std::cout << "| Enter the text: ";
			std::cin >> arr[i][j];
		}
	}

}

//------DATE-------
class Date {
public:
	Date() = default;
	~Date() = default;
	friend std::ostream& operator<<(std::ostream& fin, const Date& date);

	void CreatDate();
	void CreatDate(const size_t& day, const size_t& month, const size_t& year);
private:
	// format 11.11.2022
	std::string _date;
};
std::ostream& operator<<(std::ostream& fin, const Date& date) {
	fin << date._date;
	return fin;
}
void Date::CreatDate() {
	size_t num;
	while (true) {
		try {
			std::cout << "| Enter the day: ";
			std::cin >> num;
			if (num == 0) {
				throw static_cast<std::string>("ERROR, found 0 or a word");
			}
			else if (num < 0) {
				throw static_cast<std::string>("ERROR, found a negative number");
			}
			else if (num > 31) {
				throw static_cast<std::string>("ERROR, found number greater than 31");
			}
			_date += std::to_string(num);
			_date += '.';
			break;
		}
		catch (const std::string& ex) {
			std::cout << ex << std::endl;
		}
	}
	while (true) {
		try {
			std::cout << "| Enter the month: ";
			std::cin >> num;
			if (num == 0) {
				throw static_cast<std::string>("ERROR, found 0");
			}
			else if (num < 0) {
				throw static_cast<std::string>("ERROR, found a negative number");
			}
			else if (num > 31) {
				throw static_cast<std::string>("ERROR, found number greater than 31");
			}
			_date += std::to_string(num);
			_date += '.';
			break;
		}
		catch (const std::string& ex) {
			std::cout << ex << std::endl;
		}
	}
	while (true) {
		try {
			std::cout << "| Enter the year(Ex: 2021): ";
			std::cin >> num;
			if (num == 0) {
				throw static_cast<std::string>("ERROR, found 0");
			}
			else if (num < 0) {
				throw static_cast<std::string>("ERROR, found a negative number");
			}
			else if (num > 5000) {
				throw static_cast<std::string>("ERROR, found number greater than 5000");
			}
			_date += std::to_string(num);
			return;
		}
		catch (const std::string& ex) {
			std::cout << ex << std::endl;
		}
	}
}
void Date::CreatDate(const size_t& day, const size_t& month, const size_t& year) {
	if (day > 0 && day < 32) {
		_date += std::to_string(day);
		_date += '.';
	}
	else {
		return;
	}
	if (month > 0 && month < 32) {
		_date += std::to_string(month);
		_date += '.';
	}
	else {
		return;
	}
	if (year > 0 && year < 5000) {
		_date += std::to_string(year);
		return;
	}
	else {
		return;
	}
}
//-----------------

class shop {
public:
	shop() = default;
	~shop() = default;
	friend std::ostream& operator<<(std::ostream& fin, const shop& _shop);
	void Creat_shop();
private:
	struct product {
		std::string _name_of_product;
		size_t _count_of_produts;
		size_t _price;
	};

private:
	std::string _name;
	Date _date_of_creation;
	std::string _owner;
	std::vector<product> _products;
};
std::ostream& operator<<(std::ostream& fin, const shop& _shop) {
	fin << _shop._name << std::endl;
	fin << _shop._owner << std::endl;
	fin << _shop._date_of_creation << std::endl;
	auto it = _shop._products.begin();
	for ( ; it != _shop._products.end(); ++it) {
		fin << (*it)._name_of_product << " " << (*it)._count_of_produts << " " << (*it)._price << std::endl;
	}
	return fin;
}
void shop::Creat_shop() {
	std::cout << "| Enter the name of the shop: ";
	std::getline(std::cin, _name);
	_date_of_creation.CreatDate();
	std::cout << "| Enter the name of the owner: ";
	std::cin.ignore();
	std::getline(std::cin, _owner);
	//std::cin.ignore();

	product temp_product;
	system("cls");
	for (size_t i = 0; true; ++i) {
		std::cout << "| ! If You wonna to stop, writing \"stop\" !" << std::endl;
		std::cout << "| Enter the name of the produst: ";
		std::getline(std::cin, temp_product._name_of_product);
		if (temp_product._name_of_product == "stop" || temp_product._name_of_product == "Stop") {
			return;
		}
		std::cout << "| Enter the count of the produsts: ";
		std::cin >> temp_product._count_of_produts;
		std::cout << "| Enter the price of the produst: ";
		std::cin >> temp_product._price;
		_products.push_back(temp_product);
		std::cin.ignore();
		system("cls");
	}
}

class Man {
public:
	Man() = default;
	~Man() = default;



private:


};