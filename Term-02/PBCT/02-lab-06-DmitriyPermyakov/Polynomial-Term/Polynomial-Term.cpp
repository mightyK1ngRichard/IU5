#include "Polynomial.h"
size_t GetSize() {
	char data[100];
	while (true) {
		try {
			std::cin.getline(data, 100);
			if (std::atoi(data) < 0)
				throw "\n| ERROR: Size < 0!\a";
			for (size_t i = 0; i < strlen(data); ++i) {
				if (!(data[i] >= '0' && data[i] <= '9'))
					throw "\n| ERROR: The letter in the number!\a";
			}
			
			return static_cast<size_t>(std::atoi(data));
		}
		catch (const char* text) {
			std::cout << text << std::endl;
			std::cout << "| Repeat the input: SIZE = ";
		}
	}
}

int main() {
	size_t SIZE;
	std::cout << "| SIZE = ";
	SIZE = GetSize();
	//std::cin.ignore();
	Term<int>* arr = new Term<int>[SIZE];
	for (size_t i = 0; i < SIZE; ++i) {
		std::cout << "[" << i << "] = ";
		std::cin >> arr[i];
	}
	std::cout << std::endl;
	size_t SIZE2;
	std::cout << "| SIZE_2 = ";
	SIZE2 = GetSize();
	Term<int>* arr2 = new Term<int>[SIZE2];
	for (size_t i = 0; i < SIZE2; ++i) {
		std::cout << "[" << i << "] = ";
		std::cin >> arr2[i];
	}
	Polynomial<int> polynom1(arr, SIZE);
	Polynomial<int> polynom2(arr2, SIZE2);
	std::cout << "\n------------POLINOM-1--------------\n";
	std::cout << polynom1 << std::endl;
	std::cout << "------------POLINOM-2--------------\n";
	std::cout << polynom2 << std::endl;

	Polynomial<int> polynom3 = polynom1 * polynom2;
	Polynomial<int> polynom4 = polynom1 + polynom2;
	
	std::cout << "----------MULTIPLICATION-----------\n";
	std::cout << polynom3 << std::endl;
	std::cout << "---------------SUM-----------------\n";
	std::cout << polynom4 << std::endl;

	return 0;
}

/*
 5x^3 - x^3
 2x^2 + 4x^2
 5x - 6x + x
 4x
 2x^2 - x^2
 5x^3
 4x^4
*/

/*
2
0x^5
5
4
-1
x
x^0
x^2
*/