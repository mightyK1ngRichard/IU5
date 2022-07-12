#include "Header.h"

int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string word;
	// -1-
	std::cout << "| Введите два слова: ";
	std::getline(std::cin, word);
	size_t i = 0;
	size_t help_count = 0;
	// the first letter of the word
	for (; i < word.length(); ++i) {
		if (!((word[i] >= 'а' && word[i] <= 'я') || word[i] == 'ё' || (word[i] >= 'А' && word[i] <= 'Я') || word[i] == 'Ё' || 
			(word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) && help_count == 0)
			continue;
		if (help_count == 0) {
			std::cout << "первая буква: " << word[i] << std::endl;
			help_count = 0;
		}
		if (word[i] == ' ') {
			++i;
			while (!((word[i] >= 'а' && word[i] <= 'я') || word[i] == 'ё' || (word[i] >= 'А' && word[i] <= 'Я') || word[i] == 'Ё' ||
				(word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) && i < word.length())
				++i;
			break;
		}
		++help_count;
	}
	std::cout << "первая буква: " << word[i] << std::endl;
	// -2-
	EditText(word);
	std::cout << word << std::endl;
	// -3-
	std::fstream fin, fin2;
	fin.open("File_A.txt");
	fin2.open("File_B.txt");
	if (!fin.is_open()) {
		std::cout << "| ERROR: Ошибка открытия файла!" << std::endl;
		std::fstream("File_A.txt");
		std::cout << "| Новый файл создан!" << std::endl;
	}
	if (!fin2.is_open()) {
		std::cout << "| ERROR: Ошибка открытия файла!" << std::endl;
		std::fstream("File_B.txt");
		std::cout << "| Новый файл создан!" << std::endl;
	}
	while (!fin.eof()) {
		std::string text;
		std::getline(fin, text);
		EditText(text);
		fin2 << text;
		fin2 << std::endl;
	}
	fin.close();
	fin2.close();
	// -4-
	std::vector<float> vec1;
	std::vector<float> vec2;
	std::vector<float> vec3;
	// fill vectors
	for (size_t i = 0; i < 25; ++i) {
		vec1.push_back(rand() % 100);
		vec2.push_back(rand() % 100);
	}
	std::cout << "-----vec_1------\n";
	PrintVector(vec1);
	std::cout << "\n-----vec_2------\n";
	PrintVector(vec2);

	// sum elements
	auto it = vec1.begin();
	auto it2 = vec2.begin();
	for (; it != vec1.end() || it2 != vec2.end(); ++it, ++it2) 
		vec3.push_back(*it + *it2);
	std::cout << "\n-----vec_3------\n";
	PrintVector(vec3);

	// -5-
	Planet* all = new Planet[9];
	std::string NamesPlanet[]{"Меркурий", "Венера", "Земля", "Марс", "Юпитер", "Сатурн", "Уран", "Нептун", "Плутон"};
	size_t countSatellite[]{ 0,0,1,2,69,62,7,14,10 };
	size_t max_index = 0;
	size_t max = countSatellite[0];
	// fill class Planet
	for (i = 0; i < 9; ++i) {
		all[i].SetDataName(NamesPlanet[i]);
		all[i].SetDataSatellite(countSatellite[i]);
		if (countSatellite[i] > max) {
			max = countSatellite[i];
			max_index = i;
		}
	}
	// print class planet
	for (i = 0; i < 9; ++i) 
		std::cout << all[i];
	// print MAX
	std::cout << "\n-----MAX------\n";
	std::cout << all[max_index];

	// -6-
	std::list<int> list;
	auto it_list = list.begin();
	for (size_t i = 0; i < 10; ++i)
		list.push_back(rand() % 20 - 10);
	std::cout << "\n-----Print list------\n";
	Printlist(list);
	std::cout << "\n-----countPositive------\n";
	size_t countPositive = CountPositive(list);
	std::cout << countPositive << std::endl;

	// -8-
	std::map<int, double> map;
	double arr_double[]{ 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
	// fill map
	for (i = 0; i < 9; ++i) 
		map[i] = arr_double[i];
	std::cout << "\n-----Print Map Before------\n";
	auto it_map = map.begin();
	for (; it_map != map.end(); ++it_map) 
		std::cout << it_map->first << ' ' << it_map->second << std::endl;	
	for (it_map = map.begin(); it_map != map.end(); ) {
		if (it_map->first % 2 == 0)
			it_map = map.erase(it_map);
		else
			++it_map;
	}
	std::cout << "\n-----Print Map After------\n";
	for (it_map = map.begin(); it_map != map.end(); ++it_map) 
		std::cout << it_map->first << ' ' << it_map->second << std::endl;	
	
	// -9-
	std::cout << std::endl;
	std::map <std::string, std::string> phoneData;
	std::string phone_numbers[]{ "89168559950","89168547784","81562357789","8162922863" };
	std::string phone_names[]{ "Владимир Петров", "Анатолий Паравозов", "Стас Сильвернейм", "Назин Николай" };
	std::string all_phone_numbers[]{ "89154251145","891542511441", "89154251145", "89154251145", "89154261145", "89184251145","81562357789","8162922863" };
	// fill map
	for (i = 0; i < 4; ++i) 
		phoneData[phone_numbers[i]] = phone_names[i];
	// print of all data
	for (auto it_phone = phoneData.begin(); it_phone != phoneData.end(); ++it_phone)
		std::cout << "|  " << it_phone->first << ' ' << it_phone->second << std::endl;
	std::cout << std::endl;
	for (auto it_phone = phoneData.begin(); it_phone != phoneData.end(); ++it_phone) {
		for (i = 0; i < 8; ++i) {
			if (all_phone_numbers[i] == it_phone->first) {
				std::cout << "| Пользователь: " << it_phone->second << std::endl;
				break;
			}
		}
	}
	
	delete[] all;
	return 0;
}
