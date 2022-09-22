# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
"""
Task #2.
"""
from random import randint


def get_random(num_count, begin, end):
    """
    Рандомные числа
    :param num_count: число случайных чисел
    :param begin: с какого числа
    :param end: по какое
    :return: картеж чисел
    """
    return (randint(begin, end) for _ in range(num_count))

#
# def main():
#     get_random(5, 1, 3)
#
#
# if __name__ == '__main__':
#     main()
