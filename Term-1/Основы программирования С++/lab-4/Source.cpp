#include <iostream>
#include <math.h>	
#include <iomanip>

using namespace std;
double f(double x, double k)
{
	return x - k * cos(x);
}
double f_pr(double x, double k)
{
	return 1 + k * sin(x);
}
void newton(double eps, double k)
{
	double x = 0;
	int i = 0;
	while (fabs(f(x, k)) > eps)
	{
		x = x - (double)f(x, k) / f_pr(x, k);

		i++;
		if (i > 1000000)
			break;
	}
	if (k == 1)
		cout << "Метод Ньютона:      " << setprecision(6) << x << " |" << " " << i;
	else
		cout << "Метод Ньютона:      " << setprecision(8) << x << "  |" << " " << i;
	cout << endl;
}

void des_2(double k, double eps)
{
	double x1 = 0, x2;
	if (f(x1, k) < 0)
	{
		x2 = 1;
		while (f(x2, k) < 0)
			x2 *= 10;
	}

	else
	{
		x2 = 0;
		x1 = -1;
		while (f(x1, k) < 0)
			x1 *= 10;
	}

	double x;
	int i = 0;
	do
	{
		x = (double)((x1 + x2) / 2);
		if (f(x1, k) * f(x, k) < 0)
			x2 = x;
		else
			x1 = x;

		i++;
		if (i > 1000000)
			break;
	} while (fabs(f(x, k)) > eps);

	if (k == 1)
		cout << "Половинное деление: " << setprecision(6) << x << " |" << " " << i << endl;
	else
		cout << "Половинное деление: " << setprecision(8) << x << "  |" << " " << i << endl;

}

void des_3(double k, double eps)  // простой интеграцией
{
	double x = 0;
	int i = 0;
	while (fabs(f(x, k)) > eps)
	{
		x = k * cos(x);

		i++;
		if (i > 1000000)
			break;
	}
	if (k == 1)
		cout << "Интеграция:         " << setprecision(6) << x << " |" << " " << i;
	else
		cout << "Интеграция:         " << setprecision(8) << x << " |" << " " << i;
}

