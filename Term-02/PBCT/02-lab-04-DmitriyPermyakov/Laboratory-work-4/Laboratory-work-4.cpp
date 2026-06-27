#include "Header.h"

int main()
{
    Stack<int> stack;
	int number{};
	
	std::cout << "Enter the number: ";
	std::cin >> number;
	Apportion(stack, number);
	Stack<int> stackNew;

	/*ДОП ЗАДАНИЕ*/
	stack.Push(10);
	stack.Push(20);
	stack.Push(30);
	stack.Push(40);
	// оператор копирования
	stackNew = stack;
	stackNew.Read();

	stackNew.Push(1);
	stackNew.Push(2);
	stackNew.Push(3);
	stackNew.Push(4);
	Stack<int> UltraNewStack(stackNew);
	UltraNewStack.Read();
	return 0;
	/*while (true) {
		switch (Menu())
		{
		case 1:
			int number;
			std::cout << "\nEnter the number: ";
			std::cin >> number;
			stackList.Push(number);
			std::cout << std::endl;
			break;
		case 2: stackList.Pop(); std::cout << std::endl;; break;
		case 3: std::cout << std::endl; stackList.Read(); break;
		case 4: std::cout << std::endl << stackList.Top_inf() << std::endl; break;
		case 5: 
			std::cout << std::endl;
			if (stackList.Empty()) std::cout << "  Yes\n\n";
			else std::cout << "   No\n\n";
			break;
		case 6: return 0;
		case 7: system("cls");
		default: break;
		}
	}*/
}