# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>


def print_result(func):
    def wrapper():
        result = func()
        print(func.__name__)
        if type(result) is dict:
            for key, el in result.items():
                print(f'{key} = {el}')

        elif type(result) is list:
            for el in result:
                print(el)

        else:
            print(result)

        return func()

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


if __name__ == '__main__':
    print('!!!!!!!!')
    test_1()
    test_2()
    test_3()
    test_4()
