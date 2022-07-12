#include "Header.h"
void main() {
	int com = 0;
	int sw = 0;
	srand(time(NULL));
	int size = 5;
	// первый массив
	int* arr = new int[size];
	fillarray(arr, size);
	cout << "Our Array:" << endl;
	printarr(arr, size);
	// второй массив
	int* arr2 = new int[size];
	for (int i = 0; i < size; i++)
		arr2[i] = arr[i];
	cout << endl;
	// сортировка методом минмакс
	cout << "\x1b[31mOur Array after the minmax sorting:\x1b[0m" << endl << endl;
	minmax(arr2, size, com, sw, true);
	cout << "The first sorting to up" << endl;
	printarr(arr2, size);
	cout << "comparison: " << com << " | swaps: " << sw << endl;
	cout << endl;
	minmax(arr2, size, com, sw, true);
	cout << "The second sorting to up" << endl;
	printarr(arr2, size);
	cout << "comparison: " << com << " | swaps: " << sw << endl;
	cout << endl;
	minmax(arr2, size, com, sw, false);
	cout << "The first sorting to down" << endl;
	printarr(arr2, size);
	cout << "comparison: " << com << " | swaps: " << sw << endl;
	cout << endl;
	// сортировка методом пузырька
	cout << "\x1b[31mOur array after the bubble sorting:\x1b[0m" << endl << endl;
	water(arr, size, com, sw, false);
	cout << "The first sorting to up" << endl;
	printarr(arr, size);
	cout << "comparison: " << com << " | swaps: " << sw << endl;
	cout << endl;
	water(arr, size, com, sw, false);
	cout << "The second sorting to up" << endl;
	printarr(arr, size);
	cout << "comparison: " << com << " | swaps: " << sw << endl;
	cout << endl;
	water(arr, size, com, sw, true);
	cout << "The sorting to down" << endl;
	printarr(arr, size);
	cout << "comparison: " << com << " | swaps: " << sw << endl;
	delete[] arr2;
	delete[] arr;
	cout << "__________________________" << endl;
	// Задание 2.
	int n[]{ 5, 50, 500 };
	int* arr3;
	int* arr4;
	cout << "method" << setw(13) << "|comparison" << '|' << setw(5) << "swaps" << '|' << endl;
	for (int i = 0; i <= 2; i++) {
		arr3 = new int[n[i]];
		fillarray(arr3, n[i]);
		arr4 = new int[n[i]];
		for (int i = 0; i < n[i]; i++)
			arr4[i] = arr3[i];
		minmax(arr3, n[i], com, sw, true);
		cout << setw(4) << "n=" << n[i] << endl;
		cout << "Minmax" << setw(3) << '|' << setw(10) << com << '|' << setw(5) << sw << '|' << endl;
		delete[] arr3;
		fillarray(arr4, n[i]);
		water(arr4, n[i], com, sw, false);
		cout << "Bubble" << setw(3) << '|' << setw(10) << com << '|' << setw(5) << sw << '|' << endl;
		delete[] arr4;
	}
}
