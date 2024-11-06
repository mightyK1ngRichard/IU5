#include "Header.h"
int SearchLCD(int a, int b) {
    int max, min;
    if (a > b) { max = a, min = b; }
    else if (a == b)
        return a;
    else { max = b; min = a; }
    for (int i = max; i >= 1; --i) {
        if (a % i == 0 && b % i == 0)
            return i;
    }
}

Fraction& Fraction::operator + (const Fraction& fraction)
{
    Fraction temp;
    int NOD = SearchLCD(numerator, denominator);
    while (NOD != 1)
    {
        numerator /= NOD;
        denominator /= NOD;
        NOD = SearchLCD(numerator, denominator);
    }
    if (denominator != fraction.denominator) {
        temp.numerator = fraction.numerator * denominator + fraction.denominator * numerator;
        temp.denominator = denominator * fraction.denominator;
    }
    else {
        temp.numerator = fraction.numerator + numerator;
        temp.denominator = denominator;
    }

    return temp;
}

Fraction& Fraction::operator + (const double& fractionDouble)
{
    Fraction temp;
    Fraction fraction(fractionDouble);
    int NOD = SearchLCD(fraction.numerator, fraction.denominator);
    while (NOD != 1)
    {
        fraction.numerator /= NOD;
        fraction.denominator /= NOD;
        NOD = SearchLCD(fraction.numerator, fraction.denominator);
    }
    if (denominator != fraction.denominator)
    {
        temp.numerator = numerator * fraction.denominator + fraction.numerator * denominator;
        temp.denominator = denominator * fraction.denominator;
    }

    else
    {
        temp.numerator = numerator + fraction.numerator;
        temp.denominator = denominator;
    }

    return temp;
}

Fraction& Fraction::operator + (const int& fractionInt)
{
    Fraction temp;
    Fraction fraction(fractionInt);
    int NOD = SearchLCD(fraction.numerator, fraction.denominator);
    while (NOD != 1)
    {
        fraction.numerator /= NOD;
        fraction.denominator /= NOD;
        NOD = SearchLCD(fraction.numerator, fraction.denominator);
    }
    if (denominator != fraction.denominator)
    {
        temp.numerator = numerator * fraction.denominator + fraction.numerator * denominator;
        temp.denominator = denominator * fraction.denominator;
    }

    else
    {
        temp.numerator = numerator + fraction.numerator;
        temp.denominator = denominator;
    }

    return temp;
}

Fraction& operator + (const int& i, const Fraction& fraction)
{
    Fraction temp;
    Fraction fractionInt(i);
    int NOD = SearchLCD(fraction.numerator, fraction.denominator);
    while (NOD != 1)
    {
        fractionInt.numerator /= NOD;
        fractionInt.denominator /= NOD;
        NOD = SearchLCD(fractionInt.numerator, fractionInt.denominator);
    }
    if (fractionInt.denominator != fraction.denominator)
    {
        temp.numerator = fractionInt.numerator * fraction.denominator + fraction.numerator * fractionInt.denominator;
        temp.denominator = fractionInt.denominator * fraction.denominator;
    }

    else
    {
        temp.numerator = fractionInt.numerator + fraction.numerator;
        temp.denominator = fractionInt.denominator;
    }

    return temp;
}

Fraction& operator + (const double& d, const Fraction& fraction)
{
    Fraction temp;
    Fraction fractionDouble(d);
    int NOD = SearchLCD(fraction.numerator, fraction.denominator);
    while (NOD != 1)
    {
        fractionDouble.numerator /= NOD;
        fractionDouble.denominator /= NOD;
        NOD = SearchLCD(fractionDouble.numerator, fractionDouble.denominator);
    }

    if (fractionDouble.denominator != fraction.denominator)
    {
        temp.numerator = fractionDouble.numerator * fraction.denominator + fraction.numerator * fractionDouble.denominator;
        temp.denominator = fractionDouble.denominator * fraction.denominator;
    }

    else
    {
        temp.numerator = fractionDouble.numerator + fraction.numerator;
        temp.denominator = fractionDouble.denominator;
    }

    return temp;
}

std::istream& operator >> (std::istream& fin, Fraction& fraction)
{
    char* list = new char[100];
    std::cin.getline(list, 100);
    bool nice = false;
    char* help = new char[strlen(list) + 1];
    help[0] = '\0';
    size_t i = 0, j = 0;
    for (; i < strlen(list); i++)
    {
        if (list[i] == ' ') break;
        if (list[i] == '/') {
            nice = true;
            break;
        }
        help[j++] = list[i];
    }
    help[j] = '\0';
    if (!nice) {
        int head, num_1, num_2, k = 1;
        if (strlen(help) == 0)
            head = 0;
        else
        {
            if (atoi(help) < 0)
                k = -1;
            else k = 1;
            head = abs(atoi(help));
        }


        j = 0;
        ++i;
        help[j] = '\0';
        for (; i < strlen(list); i++)
        {
            if (list[i] == '/') break;
            help[j++] = list[i];
        }
        help[j] = '\0';
        if (strlen(help) == 0)
            num_1 = 0;
        else
            num_1 = atoi(help);


        j = 0; ++i;
        help[j] = '\0';
        for (; i < strlen(list); i++)
            help[j++] = list[i];
        help[j] = '\0';
        if (strlen(help) == 0)
            num_2 = 1;
        else
            num_2 = atoi(help);

        fraction.numerator = k * (head * num_2 + num_1);
        fraction.denominator = num_2;
    }
    else {
        int head, num_1, num_2;
        head = 0;
        j = 0;

        if (strlen(help) == 0)
            num_1 = 0;
        else
            num_1 = atoi(help);


        j = 0; ++i;
        help[j] = '\0';
        for (; i < strlen(list); i++)
            help[j++] = list[i];
        help[j] = '\0';
        if (strlen(help) == 0)
            num_2 = 1;
        else
            num_2 = atoi(help);

        fraction.numerator = num_1;
        fraction.denominator = num_2;
    }
    return fin;
}

std::ostream& operator << (std::ostream& fin, const Fraction& fraction)
{
    int head, k = 1;
    Fraction New;
    New.numerator = abs(fraction.numerator);
    New.denominator = abs(fraction.denominator);

    if (New.denominator < New.numerator) {
        head = abs(fraction.numerator / fraction.denominator);
        if (fraction.numerator < 0)
            k = -1;
        else k = 1;
        New.numerator -= head * New.denominator;
    }
    else if (abs(New.denominator) == abs(New.numerator)) {
        if (fraction.numerator < 0)
            k = -1;
        else k = 1;
        head = k * 1;
        fin << head;
        return fin;
    }
    else {
        head = 0;
        if (fraction.numerator < 0)
            k = -1;
        else k = 1;
    }

    int NOD = SearchLCD(New.numerator, New.denominator);
    while (NOD != 1)
    {
        New.numerator /= NOD;
        New.denominator /= NOD;
        NOD = SearchLCD(New.numerator, New.denominator);
    }

    if (New.denominator == 1)
    {
        head = New.denominator * head + New.numerator;
        New.numerator = 0;
        New.denominator = 1;
    }

    if (New.numerator == 0 && New.denominator == 1)
        fin << k * head;
    else if (head == 0 && New.numerator < 0)
        fin << k * New.numerator << '/' << New.denominator;
    else if (head == 0 && New.numerator != 0)
        fin << k * New.numerator << '/' << New.denominator;
    else
        fin << k * head << ' ' << std::abs(New.numerator) << '/' << New.denominator;
    return fin;
}

Fraction& Fraction::operator += (const Fraction& fraction)
{
    *this = *this + fraction;
    return *this;
}

Fraction& Fraction::operator += (const double& fractionDouble)
{
    Fraction fraction(fractionDouble);
    *this = *this + fraction;
    return *this;
}

Fraction& Fraction::operator += (const int& fractionInt)
{
    Fraction fraction(fractionInt);
    *this = *this + fraction;
    return *this;
}

Fraction& Fraction::operator = (const double& fractionDouble)
{
    Fraction fraction(fractionDouble);

    if (this != &fraction)
    {
        numerator = fraction.numerator;
        denominator = fraction.denominator;
    }

    else
        std::cout << "Самокопирование\n";
    return *this;
}

Fraction& Fraction::operator = (const Fraction& fraction)
{
    if (this != &fraction)
    {
        numerator = fraction.numerator;
        denominator = fraction.denominator;
    }

    else
        std::cout << "Самокопирование\n";
    return *this;
}
