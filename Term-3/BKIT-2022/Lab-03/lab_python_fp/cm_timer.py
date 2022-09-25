# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
""" Task #6 """
from time import sleep, time
from contextlib import contextmanager


class cm_timer_1:
    def __int__(self):
        self.__start = 0
        self.__finish = 0

    def __enter__(self):
        self.__start = time()
        # return self.__start

    def __exit__(self, exp_type, exp_value, traceback):
        self.__finish = time()
        print(f'Time of work: {self.__finish - self.__start}')


@contextmanager
def cm_timer_2():
    st = time()
    yield None
    en = time()
    print(f'Time of work: {en - st}')


def main6():
    with cm_timer_1():
        sleep(2.5)

    with cm_timer_2():
        sleep(2.5)


if __name__ == '__main__':
    main6()
