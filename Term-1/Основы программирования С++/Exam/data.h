#pragma once
#include "Header.h"

template <class T>
class Human {
public:
	Human();
	Human(const std::string& name, const std::string& surname);
	~Human();
	void SendToFile(const std::string& file_name) const;
	void ReadFile(const std::string& file_name);

private:
	std::string _name;
	std::string _surname;
	size_t _income;
};
template <class T>
Human<T>::Human() : _income(0) {}
template<class T>
Human<T>::Human(const std::string& name, const std::string& surname) 
	: _name(name), _surname(surname), _income(0) {}
template<class T>
Human<T>::~Human() = default;
template<class T>
void Human<T>::SendToFile(const std::string& file_name) const {
	std::ofstream fin(file_name);
	if (!fin.is_open()) {
		std::ofstream(file_name);
	}
	fin << _name << std::endl
		<< _surname << std::endl
		<< _income << std::endl
		<< "--" << std::endl;
}
template<class T>
void Human<T>::ReadFile(const std::string& file_name) {
	std::ifstream fin(file_name);
	while (!fin.eof()) {
		std::string temp;
		std::getline(fin, temp);
		std::cout << temp;
		std::getline(fin, temp);
		std::cout << temp;
		std::getline(fin, temp);
		std::cout << temp;
	}

}
