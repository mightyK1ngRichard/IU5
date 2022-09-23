# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
from lab_python_fp.field import main1
from lab_python_fp.get_random import main2
from lab_python_fp.unique import main3
from lab_python_fp.sort import main4
from lab_python_fp.print_result import main5
from lab_python_fp.cm_timer import main6


def filter_first_name(text):
    return (text.split())[0].lower() == 'программист'


def main():
    # main1()
    # main2()
    # main3()
    # main4()
    # main5()
    # main6()
    print(filter_first_name('программист я крутой'))
    text = ['программист конечно', 'я программист', 'бывает']
    t = filter(filter_first_name, text)
    print(list(t))


if __name__ == '__main__':
    main()
