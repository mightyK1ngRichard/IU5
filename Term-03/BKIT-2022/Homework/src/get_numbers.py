# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

import requests
import matplotlib.pyplot as plt


def make_url(main_url: str, count_numbers: int) -> str:
    base_url = main_url
    res_url = f"{base_url}/num/{count_numbers}"
    return res_url


def get_data(*, main_url: str, count_numbers: int) -> str:
    res_url = make_url(main_url, count_numbers)
    r = requests.get(res_url)
    return r.text


if __name__ == '__main__':
    url = 'http://127.0.0.1:5000'
    y_axis = get_data(main_url=url, count_numbers=int(input('Сколько чисел Фибанначу Вам необходимо? '))).split(', ')
    print(y_axis)
    print(len(y_axis))
    x_axis = list(range(1, len(y_axis) + 1))
    fig = plt.figure(figsize=(10, 5))
    plt.bar(x_axis, y_axis)
    plt.xlabel('Ось абсцисс')
    plt.ylabel('Ось ординат')
    plt.title('Первые {} чисел последовательности Фибоначчи'.format(len(y_axis)))
    plt.show()

    plt.plot(x_axis, y_axis)
    plt.show()
