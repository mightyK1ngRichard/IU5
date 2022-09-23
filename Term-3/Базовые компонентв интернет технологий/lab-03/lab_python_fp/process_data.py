# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
from lab_python_fp.print_result import print_result
from lab_python_fp.cm_timer import cm_timer_1
from lab_python_fp.get_random import get_random
import json
import sys

try:
    path = sys.argv[1]
    print(path)
except:
    path = '../file.json'

with open(path) as f:
    data = json.load(f)


@print_result
def f1(arg) -> list:
    """
    Выводит отсортированный список профессий без повторений.
    Сортировка должна игнорировать регистр.
    :param arg: список
    :return: отсортированный список
    """
    return sorted(list(set([el['job-name'] for el in arg])), key=lambda x: x.lower())


@print_result
def f2(arg) -> list:
    """
    Фильтрует входной массив и возвращает только те элементы, которые начинаются со слова “программист”
    :param arg:
    :return:
    """
    return list(filter(lambda text: (text.split())[0].lower() == 'программист', arg))


@print_result
def f3(arg) -> list:
    """
    Функция f3 должна модифицировать каждый элемент массива, добавив строку “с опытом Python”
    :param arg:
    :return:
    """
    return list(map(lambda lst: lst + ' с опытом Python', arg))


@print_result
def f4(arg) -> list:
    """
    Функция f4 должна сгенерировать для каждой специальности зарплату
    от 100 000 до 200 000 рублей и присоединить её к названию специальности.
    Пример: Программист C# с опытом Python, зарплата 137287 руб.
    Используйте zip для обработки пары специальность — зарплата.
    :param arg:
    :return:
    """
    return list(zip(arg, ['зарплата ' + str(el) + ' руб.' for el in get_random(len(arg), 100000, 200000)]))


if __name__ == '__main__':
    with cm_timer_1():
        f4(f3(f2(f1(data))))
