# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
from lab_python_fp.print_result import print_result
from lab_python_fp.cm_timer import cm_timer_1
from lab_python_fp.unique import Unique
import json
import sys

# Необходимо в переменную path сохранить путь к файлу, который был передан при запуске сценария
# try:
#     path = sys.argv[0]
# except:
#     # TODO: узнать, как открыть
#     path = '../file.json'

path = '../file.json'
with open(path) as f:
    data = json.load(f)


# Далее необходимо реализовать все функции по заданию, заменив `raise NotImplemented`
# Предполагается, что функции f1, f2, f3 будут реализованы в одну строку
# В реализации функции f4 может быть до 3 строк

@print_result
def f1(arg) -> list:
    """
    Выводит отсортированный список профессий без повторений (строки в разном регистре считать равными).
    Сортировка должна игнорировать регистр.
    :param arg: список
    :return: отсортированный список
    """
    just_copy = arg
    return list()

# @print_result
# def f2(arg):
#     raise NotImplemented
#
#
# @print_result
# def f3(arg):
#     raise NotImplemented
#
#
# @print_result
# def f4(arg):
#     raise NotImplemented


if __name__ == '__main__':
    with cm_timer_1():
        # f4(f3(f2(f1(data))))
        f1(data)
