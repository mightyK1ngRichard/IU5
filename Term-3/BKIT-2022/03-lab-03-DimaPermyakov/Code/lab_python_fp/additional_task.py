# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
import numpy


def print_result(arr):
    for el in arr:
        print(el)
    print('---')


def main():
    lst = [3, 4, 5, 6, 7]

    res1 = zip(lst, map(lambda num: num ** 2, lst))
    res2 = [(el, el ** 2) for el in lst]
    res3 = zip(lst, numpy.array(lst) ** 2)

    print_result(res1)
    print_result(res2)
    print_result(res3)


if __name__ == '__main__':
    main()
