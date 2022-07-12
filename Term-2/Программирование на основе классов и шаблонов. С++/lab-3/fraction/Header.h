#pragma once
#include <iostream>
#include <string.h>
class Fraction
{
    int numerator{};
    int denominator{ 1 };

public:
    Fraction() {};
    Fraction(int numerator) {
        this->numerator = numerator;
    };
    Fraction(double numerator) {
        this->numerator = numerator * 10000;
        this->denominator = 10000;
    };
    Fraction(int numerator, int denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
    };
    Fraction(const Fraction& fraction) {
        numerator = fraction.numerator;
        denominator = fraction.denominator;
    }
    Fraction(const char list[]) {
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

            ++i;
            j = 0;
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

            numerator = k * (head * num_2 + num_1);
            denominator = num_2;
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

            numerator = num_1;
            denominator = num_2;
        }
    }
    void SetNumerator(int numerator) {
        this->numerator = numerator;
    }
    void SetDenomirator(int numerator) {
        this->denominator = denominator;
    }
    int GetNumerator() {
        return numerator;
    }
    int GetDenomirator() {
        return denominator;
    }

    friend std::istream& operator >> (std::istream& fin, Fraction& fraction);
    friend std::ostream& operator << (std::ostream& fin, const Fraction& fraction);
    friend Fraction& operator + (const int& i, const Fraction& fraction);
    friend Fraction& operator + (const double& d, const Fraction& fraction);
    Fraction& operator + (const double& fractionDouble);
    Fraction& operator + (const int& fractionInt);
    Fraction& operator + (const Fraction& fraction);

    Fraction& operator += (const Fraction& fraction);
    Fraction& operator += (const double& fractionDouble);
    Fraction& operator += (const int& fractionInt);
    Fraction& operator = (const double& fractionDouble);
    Fraction& operator = (const Fraction& fraction);
};
int SearchLCD(int a, int b);
