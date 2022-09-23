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


# @print_result
def f1(arg) -> list:
    """
    Выводит отсортированный список профессий без повторений.
    Сортировка должна игнорировать регистр.
    :param arg: список
    :return: отсортированный список
    """
    return sorted(list(set([el['job-name'] for el in arg])), key=lambda x: x.lower())


def filter_first_name(text):
    return (text.split())[0].lower() == 'программист'


@print_result
def f2(arg) -> list:
    """
    Фильтрует входной массив и возвращает только те элементы, которые начинаются со слова “программист”
    :param arg:
    :return:
    """
    return list(filter(lambda text: (text.split())[0].lower() == 'программист', arg))


@print_result
def f3(arg):
    raise NotImplemented


@print_result
def f4(arg):
    raise NotImplemented


if __name__ == '__main__':
    with cm_timer_1():
        # f4(f3(f2(f1(data))))
        res = f1(data)
        f2(res)
