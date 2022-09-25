# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
""" Task #5 """


def print_result(func):
    def wrapper(lst=[], *args, **kwargs):
        print(func.__name__)

        if len(lst) == 0:
            result = func(*args, **kwargs)
        else:
            result = func(lst, *args, **kwargs)

        if type(result) is dict:
            for key, el in result.items():
                print(f'{key} = {el}')

        elif type(result) is list:
            print('\n'.join(map(str, result)))

        else:
            print(result)

        return result

    return wrapper


@print_result
def test_1():
    return 1


@print_result
def test_2():
    return 'iu5'


@print_result
def test_3():
    return {'a': 1, 'b': 2}


@print_result
def test_4():
    return [1, 2]


def main5():
    print('!!!!!!!!')
    test_1()
    test_2()
    test_3()
    test_4()


if __name__ == '__main__':
    main5()
