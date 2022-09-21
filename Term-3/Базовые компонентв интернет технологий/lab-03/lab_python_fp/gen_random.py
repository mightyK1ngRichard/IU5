# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
"""
Task #2.
"""
from random import randint


def gen_random(num_count, begin, end):
    for _ in range(num_count):
        print(randint(begin, end), end=' ')


def main():
    gen_random(5, 1, 3)


if __name__ == '__main__':
    main()
