# Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
""" Task #1. """


def field(items, *args):
    assert len(args) > 0, 'The parameter "args" is empty!'
    # Uninteresting method.
    # if len(args) == 1:
    #     for item in items:
    #         for el in item:
    #             if el == args[0] and item[el] is not None:
    #                 print(item[el], end=' ')
    #     print()
    # else:
    #     for item in items:
    #         help_dict = dict()
    #         for el in item:
    #             for argument in args:
    #                 if el == argument and item[argument] is not None:
    #                     help_dict[el] = item[el]
    #         print(help_dict)

    # Interesting method.
    if len(args) == 1:
        print(*[item[el] for item in items for el in item if el == args[0] and item[el] is not None])
    else:
        print({el: item[el] for item in items for el in item for argument in args if
               el == argument and item[argument] is not None})


# TODO: Возможно стоит сделать return.
def main1():
    print('\n---#1---')

    goods = [
        {'title': 'Ковер', 'price': 2000, 'color': 'green'},
        {'title': 'Диван для отдыха', 'price': 5300, 'color': 'black'}
    ]
    # должен выдавать 'Ковер', 'Диван для отдыха'.
    field(goods, 'title')
    # должен выдавать {'title': 'Ковер', 'price': 2000}, {'title': 'Диван для отдыха', 'price': 5300}.
    field(goods, 'title', 'price')


if __name__ == '__main__':
    main1()
