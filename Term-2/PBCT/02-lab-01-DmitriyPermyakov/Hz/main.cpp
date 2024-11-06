#include "..\MathLibrary\MathLibrary.h";


int main()
{
	double a, b;
	MathLibrary::Boss::LogoBoss();

	std::cout << "a = "; std::cin >> a;
	std::cout << "b = "; std::cin >> b;
	std::cout << MathLibrary::Arithmetic::Sum(a, b) << std::endl;
	std::cout << MathLibrary::Arithmetic::Subtract(a, b) << std::endl;
	std::cout << MathLibrary::Arithmetic::Multiply(a, b) << std::endl;
	std::cout << MathLibrary::Arithmetic::Divide(a, b) << std::endl;
}