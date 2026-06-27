#include "Header.h"

// matrix
/*
int main() {
	const size_t row = 3;
	const size_t column = 2;
	std::string** arr = CreatArr<std::string>(row, column);

	FillArr(arr, row, column);
	PrintArr(arr, row, column);

	for (size_t i = 0; i < row; ++i) {
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}
*/

int main() {
	shop sh;
	sh.Creat_shop();
	std::cout << sh << std::endl;
}
