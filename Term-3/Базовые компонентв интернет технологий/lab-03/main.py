# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
from lab_python_fp.get_random import get_random


def main():
    numbers = get_random(4, 0, 5)
    for el in numbers:
        print(el, end=' ')
    print()
    m = iter([2, 3, 4])
    print(m.__next__())

    ls = [1, 2, 1, 1, 1]
    ls = set(ls)
    ls = list(ls)
    print(type(ls))


if __name__ == '__main__':
    main()
