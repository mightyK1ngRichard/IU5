# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

from operator import itemgetter


def task_01(one_to_many) -> list:
    """ ЗАДАНИЕ №1.
    Вывести имя IDE, которое начинается с буквы 'V' и количество пользователей и отсортированный список языков,
    которые поддерживается данным IDE.
    :param one_to_many: Список один ко многим.
    :return: Отфильтрованный список по первой букве, с отсортированным внутренним списком.
    """
    # Пояснение. Сначала отфильтровал список one_to_many по принципу: первая буква равна 'v', потом
    # создал новый список res, сортируя список класса. Новая переменная, так как tuple нельзя изменять.
    return [(name, count, sorted(lst)) for name, count, lst in
            list(filter(lambda el: el[0][0].lower() == 'v', one_to_many))]


def task_02(one_to_many) -> list:
    """ Задание 2.
    Вывести список IDE, которое поддерживает меньше всего языков. Вывод совершить в порядке убывания.
    :param one_to_many:
    :return: Список кортежей, состоящий из имени IDE и кол-ва языков, которые поддерживает.
    """
    # Пояснение. Сначала создаю список, состоящий из кортежей. Первый элемент - имя IDE, второй - кол-во языков,
    # которое он поддерживает.
    # Потом сортирую список по второму элементу.
    return sorted([(el[0], len(el[2])) for el in one_to_many],
                  key=itemgetter(1),
                  reverse=True)


def task_03(many_to_many) -> list:
    """
    Выведите список всех связанных IDE и языков, отсортированный по IDE, сортировка по языкам
    произвольная.
    :param many_to_many: список созданный связями многие ко многим.
    :return: Список IDE и языков, отсортированные по IDE.
    """
    # Пояснение. Изначально сортирую many_to_many по IDE.name, после чего возвращаю список кортежей:
    # имя и список языков.
    return [(name, languages) for name, count, languages in sorted(many_to_many, key=itemgetter(0))]
