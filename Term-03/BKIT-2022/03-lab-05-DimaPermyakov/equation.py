# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

import math
import sys


def calculate(A, B, C):
    if type(A) not in [int, float]:
        raise TypeError("Коэффициент A должен быть положительным вещественным числом!")
    if type(B) not in [int, float]:
        raise TypeError("Коэффициент B должен быть неотрицательным вещественным числом!")
    if type(C) not in [int, float]:
        raise TypeError("Коэффициент C должен быть неотрицательным вещественным числом!")

    if A == 0:
        raise ValueError("Коэффициент A должен быть положительным вещественным числом!")

    D = B * B - 4 * A * C

    if D > 0:
        t = (-B - math.sqrt(D)) / (2 * A)
        if t > 0:
            x1 = math.sqrt((-B + math.sqrt(D)) / (2 * A))
            x2 = -x1
            x3 = math.sqrt((-B - math.sqrt(D)) / (2 * A))
            x4 = -x3
            return tuple(sorted(set([x1, x2, x3, x4])))
    elif D == 0:
        x1 = math.sqrt(-B / 2 * A)
        x2 = -x1
        return tuple(sorted(set([x1, x2])))

    return ()


def main():
    A = 1
    B = 1
    C = 1
    try:
        A = float(sys.argv[1])
        B = float(sys.argv[2])
        C = float(sys.argv[3])
    except Exception as e:
        print("Не удалось прочитать коэффициенты!")
        while True:
            try:
                A = float(input("Введите коэффициент A\n> "))
                if A != 0:
                    break
                else:
                    print("Коэффициент A не может равняться нулю")
            except Exception as e:
                print("Коэффициент А введен некорректно!")
                pass
        while True:
            try:
                B = float(input("Введите коэффициент B\n> "))
                break
            except Exception as e:
                print("Коэффициент В введен некорректно!")
                pass
        while True:
            try:
                C = float(input("Введите коэффициент C\n> "))
                break
            except Exception as e:
                print("Коэффициент С введен некорректно!")
                pass

    roots = calculate(A, B, C)
    if (len(roots)) > 0:
        print("Корни:")
        for root in roots:
            print(root + ", ")
    else:
        print("Корней нет!")


if __name__ == "__main__":
    # main()
    pass
