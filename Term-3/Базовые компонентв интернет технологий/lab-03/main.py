# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
from lab_python_fp.get_random import get_random


def main():
    numbers = get_random(4, 0, 5)
    for el in numbers:
        print(el)


if __name__ == '__main__':
    main()
