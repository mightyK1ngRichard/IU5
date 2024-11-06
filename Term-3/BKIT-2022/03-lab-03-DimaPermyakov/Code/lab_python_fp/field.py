# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
""" Task #1. """


def field(items, *args):
    assert len(args) > 0, 'The parameter "args" is empty!'
    if len(args) == 1:
        return (item[el] for item in items for el in item if el == args[0] and item[el] is not None)
    else:
        return {el: item[el] for item in items for el in item for argument in args if
                el == argument and item[argument] is not None}


def main1():
    print('\n---#1---')

    goods = [
        {'title': 'Ковер', 'price': 2000, 'color': 'green'},
        {'title': 'Диван для отдыха', 'price': 5300, 'color': 'black'}
    ]
    # должен выдавать 'Ковер', 'Диван для отдыха'.
    res = (field(goods, 'title'))
    for el in res:
        print(el)
    # должен выдавать {'title': 'Ковер', 'price': 2000}, {'title': 'Диван для отдыха', 'price': 5300}.
    print(field(goods, 'title', 'price'))


if __name__ == '__main__':
    main1()
