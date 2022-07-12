#include "Header.h"
void fillarray(int* arr, const int size) {
	for (int i = 0; i < size; i++)
		arr[i] = rand() % 100;
}
void printarr(int* arr, const int size) {
	for (int i = 0; i < size; i++)
		cout << arr[i] << ' ';
	cout << endl;
}
void minmax(int* arr, const int size, int& com, int& sw, bool flag)
{
	sw = 0;
	com = 0;
	int fixed;
	for (int i = 0; i < size - 1; i++) {
		fixed = i;
		for (int j = i + 1; j < size; j++) {
			com++;
			if (arr[j] < arr[fixed] && flag || arr[j] > arr[fixed] && !flag)
				fixed = j;
		}
		if (fixed != i) {
			swap(arr[fixed], arr[i]);
			sw++;
		}
	}
}

void water(int* array, const int size, int& com, int& sw, bool flag)
{
	sw = 0, com = 0;
	bool array_sorted;
	for (int i = 0; i < size - 1; i++)
	{
		array_sorted = true;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j + 1] && !flag || array[j] < array[j + 1] && flag)
			{
				array_sorted = false;
				swap(array[j], array[j + 1]);
				sw++;
			}
			com++;
		}
		if (array_sorted)
			break;
	}
}