#include "Header.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Data one;
	std::cin >> one;
	Data two(one);
	two.Print();
	//std::list<Data> list;
	//ReadFile(list);
	/*while (true) {
		Menu();
		int reply = FromString<int>("Выберите пунт меню: ");
		switch (reply) {
		case 1: AddData(list); break;
		case 2: Analyis(list); break;
		case 3: Print(list); break;
		case 4: 
			SendToFile(list); 
			std::cout << "| Данные занесены в файл!\n";
			break;
		case 5: return 0;

		default:
			break;
		}
	}*/
}
