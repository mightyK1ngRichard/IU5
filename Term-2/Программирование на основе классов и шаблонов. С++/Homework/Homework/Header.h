#pragma once
#include <iostream>
#include <string>
#include <list>
#include <Windows.h>
#include <fstream>

void Menu();
template <typename T>
inline T FromString(const std::string& text_for_user);
enum Eduction_lvl {
	// начальное среднее высшее
	elementary = 1,
	middle,
	higher
};
enum Gender {
	Man = 1,
	Woman,
	Neutral
};
class Data {
public:
	Data();
	Data(const Data& info);
	~Data() = default;
	Data& operator=(const Data& info);
	friend std::ostream& operator<<(std::ostream& out, const Data& info);
	friend std::istream& operator>>(std::istream& fin, Data& info);
	void Print() const;
	friend void Print(const std::list<Data> info);
	friend void AddData(std::list<Data>& info);
	friend void ReadFile(std::list<Data>& info);
	friend void SendToFile(const std::list<Data>& info);
	friend void Analyis(const std::list<Data>& info);
private:
	std::string name__;
	size_t age__;
	Eduction_lvl eduction__;
	Gender gender__;
	bool question__;
};

// класс исключений. Отлавливает неизвестные символы и выводит сообщние
class SymbolExpocion {
public:
	SymbolExpocion() = default;
	SymbolExpocion(const char& ex) {
		text_for_user__ += ex;
		text_for_user__ += "\x1b[0m";
	}
	~SymbolExpocion() = default;
	std::string GiveException() const {
		return text_for_user__;
	}
private:
	char symbol;
	std::string text_for_user__ = "\x1b[31m| ERROR:\x1b[0m\a Найден неизвестный сивол: \x1b[31m";
};
// отлов исключений при вводе
template <typename T>
inline T FromString(const std::string& text_for_user) {
	return 0;
}
template <>
inline std::string FromString(const std::string& text_for_user) {
	std::string data;
	while (true) {
		try {
			std::cout << text_for_user;
			std::getline(std::cin, data);
			if (data.empty())
				throw "\x1b[31m| ERROR: Пусто! Вы ничего не ввели!\x1b[0m\a";

			for (size_t i = 0; i < data.length(); ++i) {
				if (data[i] >= '0' && data[i] <= '9')
					throw "\x1b[31m\n| ERROR: Найдена цифра!\x1b[0m\a";
			}

			for (size_t i = 0; i < data.length(); ++i) {
				if (!(data[i] >= static_cast<char>(65) && data[i] <= static_cast<char>(90) ||
					data[i] >= static_cast<char>(97) && data[i] <= static_cast<char>(122) ||
					data[i] >= static_cast<char>(-64) && data[i] <= static_cast<char>(-33) ||
					data[i] >= static_cast<char>(-32) && data[i] <= static_cast<char>(-1) ||
					data[i] == static_cast<char>(-72) || data[i] == static_cast<char>(-88) ||
					data[i] == static_cast<char>(32)))
					//throw "\x1b[31m\n| ERROR: Символ не распознан! Вводите буквы!\x1b[0m\a";
					throw SymbolExpocion(data[i]);
			}
			size_t countWhitespace = 0;
			for (size_t i = 0; i < data.length(); ++i) {
				if (data[i] == ' ')
					++countWhitespace;
			}

			if (countWhitespace == data.length())
				throw "\x1b[31m\n| ERROR: Имя состоит из только пробелов!\x1b[0m\a";

			return data;
		}
		catch (const SymbolExpocion& ex) {
			//"\x1b[31m\n| ERROR: Имя состоит из только пробелов!\x1b[0m\a"
			std::cout << ex.GiveException() << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
		catch (const char* ex) {
			std::cout << ex << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
	}
}
template <>
inline size_t FromString(const std::string& text_for_user) {
	std::string data;
	while (true) {
		try {
			std::cout << text_for_user;
			std::getline(std::cin, data);
			if (data.empty())
				throw "\x1b[31m| ERROR: Пусто! Вы ничего не ввели!\x1b[0m\a";

			for (size_t i = 0; i < data.length(); ++i) {
				if (data[i] == '-')
					continue;
				if (!(data[i] >= '0' && data[i] <= '9'))
					//throw "\n\x1b[31m| ERROR: Найдена буква в числе!\x1b[0m\a";
					throw SymbolExpocion(data[i]);
			}

			if (std::stoi(data) < 0)
				throw "\x1b[31m| ERROR: Вы ввели отрицательное число!\x1b[0m\a";
			if (std::stoi(data) == 0)
				throw "\x1b[31m| ERROR: Вы ввели 0!\x1b[0m\a";
			if (std::stoi(data) > 130)
				throw "\x1b[31m| ERROR: Вы ввели слишком большое число!\x1b[0m\a";
			return std::stoi(data);
		}
		catch (const SymbolExpocion& ex) {
			//"\x1b[31m\n| ERROR: Имя состоит из только пробелов!\x1b[0m\a"
			std::cout << ex.GiveException() << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
		catch (const char* ex) {
			std::cout << ex << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
	}
}
template <>
inline bool FromString(const std::string& text_for_user) {
	std::string data;
	while (true) {
		try {
			std::cout << text_for_user;
			std::getline(std::cin, data);
			if (data.empty())
				throw "\x1b[31m| ERROR: Пусто! Вы ничего не ввели!\x1b[0m\a";
			if (data == "Yes" || data == "yes" || data == "Да" || data == "да" ||
				data == "ДА" || data == "дА")
				return true;
			else if (data == "No" || data == "no" || data == "Нет" || data == "нет" ||
				data == "НЕТ")
				return false;
			else
				throw "\x1b[31m| ERROR: Ответ не распознан!\x1b[0m\a";
		}
		catch (const SymbolExpocion& ex) {
			//"\x1b[31m\n| ERROR: Имя состоит из только пробелов!\x1b[0m\a"
			std::cout << ex.GiveException() << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
		catch (const char* ex) {
			std::cout << ex << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
	}
}
template <>
inline Gender FromString(const std::string& text_for_user) {
	std::string data;
	while (true) {
		try {
			std::cout << text_for_user;
			std::getline(std::cin, data);
			if (data.empty())
				throw "\x1b[31m| ERROR: Пусто! Вы ничего не ввели!\x1b[0m\a";
			if (data == "М" || data == "м" || data == "Мужской" || data == "мужской" ||
				data == "Man" || data == "man")
				return Man;
			else if (data == "Ж" || data == "ж" || data == "Женский" || data == "ж" ||
				data == "Woman" || data == "woman")
				return Woman;
			else if (data == "Н" || data == "н" || data == "Нейтральный" || data == "нейтральный" ||
				data == "Neutral" || data == "n")
				return Neutral;
			else
				throw "\x1b[31m| ERROR: Ответ не распознан!\x1b[0m\a";
		}
		catch (const char* ex) {
			std::cout << ex << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
	}
}
template <>
inline Eduction_lvl FromString(const std::string& text_for_user) {
	std::string data;
	while (true) {
		try {
			std::cout << text_for_user;
			std::getline(std::cin, data);
			if (data.empty())
				throw "\x1b[31m| ERROR: Пусто! Вы ничего не ввели!\x1b[0m\a";
			if (data == "начальное" || data == "Начальное" || data == "elementary" || data == "Elementary" ||
				data == "низшее" || data == "школьное")
				return elementary;
			else if (data == "Среднее" || data == "среднее" || data == "middle" || data == "Middle")
				return middle;
			else if (data == "Высшее" || data == "высшее" || data == "higher" || data == "Higher" ||
				data == "Neutral" || data == "n")
				return higher;
			else
				throw "\x1b[31m| ERROR: Ответ не распознан!\x1b[0m\a";
		}
		catch (const char* ex) {
			std::cout << ex << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
	}
}
template <>
inline int FromString(const std::string& text_for_user) {
	std::string data;
	while (true) {
		try {
			std::cout << text_for_user;
			std::getline(std::cin, data);
			if (data.empty())
				throw "\x1b[31m| ERROR: Пусто! Вы ничего не ввели!\x1b[0m\a";

			for (size_t i = 0; i < data.length(); ++i) {
				if (data[i] == '-')
					continue;
				if (!(data[i] >= '0' && data[i] <= '9'))
					//throw "\x1b[31m\n| ERROR: Найдена буква в числе!\x1b[0m\a";
					throw SymbolExpocion(data[i]);
			}

			if (std::stoi(data) < 0)
				throw "\x1b[31m| ERROR: Вы ввели отрицательное число!\x1b[0m\a";
			if (std::stoi(data) == 0)
				throw "\x1b[31m| ERROR: Вы ввели 0!\x1b[0m\a";
			if (std::stoi(data) > 5)
				throw "\x1b[31m| ERROR: Вы ввели слишком большое число!\x1b[0m\a";
			return std::stoi(data);
		}
		catch (const SymbolExpocion& ex) {
			//"\x1b[31m\n| ERROR: Имя состоит из только пробелов!\x1b[0m\a"
			std::cout << ex.GiveException() << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
		catch (const char* ex) {
			std::cout << ex << std::endl;
			std::cout << "| Повторите ввод!\n";
		}
	}
}
