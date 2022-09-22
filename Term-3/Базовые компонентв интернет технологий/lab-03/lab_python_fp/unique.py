# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>


# Итератор для удаления дубликатов
class Unique(object):
    def __init__(self, items, ignore_case=False, **kwargs):
        items = {items}  # Убираем повторы засчёт set.
        self._items = items
        self._dict = kwargs
        self._ignore_case = ignore_case
        self.__counter = 0
        # В качестве ключевого аргумента, конструктор должен принимать bool-параметр ignore_case,
        # в зависимости от значения которого будут считаться одинаковыми строки в разном регистре
        # Например: ignore_case = True, Aбв и АБВ - разные строки
        #           ignore_case = False, Aбв и АБВ - одинаковые строки, одна из которых удалится
        # По-умолчанию ignore_case = False

    def __next__(self):
        # if self.__counter + 1 < len(self._items):
        #     self.__counter += 1
        #     return self._items[self.__counter-1]
        pass

    def __iter__(self):
        return self


def main():
    pass


if __name__ == '__main__':
    main()
