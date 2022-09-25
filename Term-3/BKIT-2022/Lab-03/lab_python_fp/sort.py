# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
""" Task #4 """


def main4():
    data = [4, -30, 100, -100, 123, 1, 0, -1, -4]
    result = sorted(data, key=abs, reverse=True)
    print(result)

    result_with_lambda = sorted(data, key=lambda a: abs(a), reverse=True)
    print(result_with_lambda)


if __name__ == '__main__':
    main4()
