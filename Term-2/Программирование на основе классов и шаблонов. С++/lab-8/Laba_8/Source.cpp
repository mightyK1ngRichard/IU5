#include "Header.h"

void EditText(std::string& word) {
	size_t i = 0;
	for (auto it = word.begin(); it != word.end(); ++it) {
		/*if (word[i] == ',' || word[i] == '.' || word[i] == '!' || word[i] == '?' || 
			word[i] == '-' || word[i] == ':' || word[i] == ';') {
			word.erase(it);
		}*/
		if (!((word[i] >= 'à' && word[i] <= 'ÿ') || word[i] == '¸' || (word[i] >= 'À' && word[i] <= 'ß') || word[i] == '¨' || 
			(word[i] >= '0' && word[i] <= '9') || (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') ||
			word[i] == ' ')) {
			word.erase(it);
		}
		++i;
	}
}
void PrintVector(const std::vector<float>& vec) {
	for (auto it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}
void Printlist(const std::list<int>& list) {
	for (auto it = list.begin(); it != list.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;
}
size_t CountPositive(const std::list<int>& list) {
	size_t count = 0;
	for (auto it = list.begin(); it != list.end(); ++it) {
		if (*it >= 0)
			++count;
	}
	return count;
}
