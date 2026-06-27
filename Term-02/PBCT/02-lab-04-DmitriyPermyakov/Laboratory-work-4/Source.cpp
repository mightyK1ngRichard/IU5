#include "Header.h"

size_t Menu() {
	std::cout << "1. Add the number.\n"
		<< "2. Delete the top.\n"
		<< "3. Read all list\n"
		<< "4. Read the Top number\n"
		<< "5. Is the list empty?\n"
		<< "6. Exit\n";
;	size_t item;
	std::cout << "Enter the menu item: ";
	std::cin >> item;
	return item;
}

void Apportion(Stack<int>& stack, const int number) {
	int x = number;
	int k = 2;
	std::cout << number << " = ";
	while (x != 1) {
		while (x % k == 0) {
			stack.Push(k);
			x /= k;
		}
		k += 1;
	}
	Stack<int> newStack;
	size_t trash = 0;
	while (!stack.Empty()) {
		if (trash == 0) 
			std::cout << stack.Top_inf();
		else std::cout << "*" << stack.Top_inf();
		newStack.Push(stack.Top_inf());
		stack.Pop();
		++trash;
	}
	std::cout << "\n--------------------------\n";
	trash = 0;
	std::cout << number << " = ";
	while (!newStack.Empty()) {
		if (trash == 0)
			std::cout << newStack.Top_inf();
		else std::cout << "*" << newStack.Top_inf();
		newStack.Pop();
		++trash;
	}
	std::cout << std::endl;
}
