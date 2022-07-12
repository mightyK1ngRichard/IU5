#include "Header.h"

int main() {
    // putting the fraction
    std::cout << "Enter the fraction: ";
    Fraction z;
    std::cin >> z;
    std::cout << "z=" << z << std::endl;
    // check of the construction
    Fraction fr1(10, 14), fr2;
    std::cout << "fr2=" << fr2 << std::endl;
    std::cout << "fr1=" << fr1 << std::endl;
    Fraction fr = "-1 4/8";
    std::cout << "fr=" << fr << std::endl;
    Fraction x(z), y;
    std::cout << "x=" << x << std::endl;
    double dbl = -1.25;
    Fraction f = dbl;
    std::cout << "f=" << f << std::endl;
    // check of the reloading "+"
    std::cout << "-*-*-*-*-*-*--*--*-*-\n";
    std::cout << x << " + " << z;
    y = x + z;
    std::cout << " = " << y << std::endl;
    std::cout << y << " + " << x;
    y += x;
    std::cout << " = " << y << std::endl;
    std::cout << f << " + " << dbl / 2;
    f += dbl / 2;
    std::cout << " = " << f << std::endl;
    std::cout << x << " + " << dbl;
    y = x + dbl;
    std::cout << " = " << y << std::endl;
    std::cout << dbl << " + " << y;
    y = dbl + y;
    std::cout << " = " << y << std::endl;
    std::cout << y << " + " << dbl;
    y += dbl;
    std::cout << " = " << y << std::endl;
    int i = 5;
    std::cout << y << " + " << i;
    y += i;
    std::cout << " = " << y << std::endl;
    std::cout << i << " + " << x;
    y = i + x;
    std::cout << " = " << y << std::endl;
    std::cout << x << " + " << i;
    y = x + i;
    std::cout << " = " << y << std::endl;
    std::cout << y << " + " << dbl << " + " << i << " + " << x;
    y += dbl + i + x;
    std::cout << " = " << y << std::endl;
    return 0;
}
