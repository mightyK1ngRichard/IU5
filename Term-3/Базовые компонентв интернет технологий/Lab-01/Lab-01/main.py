import sys
import math


def get_coef(index, prompt) -> float:
    '''
    Читаем коэффициент из командной строки или вводим с клавиатуры

    Args:
        index (int): Номер параметра в командной строке
        prompt (str): Приглашение для ввода коэффицента

    Returns:
        float: Коэффициент квадратного уравнения
    '''
    try:
        # Пробуем прочитать коэффициент из командной строки
        coef_str = sys.argv[index]
    except:
        # Вводим с клавиатуры
        while True:
            try:
                print(prompt)
                coef_str = input()
                coef = float(coef_str)
                return coef
            except ValueError:
                # Если неверный формат, повторяем ввод.
                pass
    return float(coef_str)


def get_roots(a, b, c) -> list:
    '''
    Вычисление корней квадратного уравнения

    Args:
        a (float): коэффициент А
        b (float): коэффициент B
        c (float): коэффициент C

    Returns:
        list[float]: Список корней
    '''
    result = []
    D = b * b - 4 * a * c
    if D == 0.0:
        root = -b / (2.0 * a)
        result.append(root)
    elif D > 0.0:
        sqD = math.sqrt(D)
        root1 = (-b + sqD) / (2.0 * a)
        root2 = (-b - sqD) / (2.0 * a)
        result.append(root1)
        result.append(root2)

    return result


def main():
    a = get_coef(1, 'Введите коэффициент А:')
    b = get_coef(2, 'Введите коэффициент B:')
    c = get_coef(3, 'Введите коэффициент C:')
    roots = get_roots(a, b, c)

    count = 0
    for el in roots:
        if el > 0:
            count += 1

    finally_roots = []
    for el in roots:
        if el > 0 or el == 1:
            finally_roots.append(math.sqrt(el))
            finally_roots.append(-1 * math.sqrt(el))
        elif el == 0:
            finally_roots.append(el)

    len_roots = len(finally_roots)
    if len_roots == 0:
        print('Корней нет')
    elif len_roots == 1:
        print(f'Один корень: {finally_roots[0]}')
    elif len_roots == 2:
        print('Два корня: {} и {}'.format(finally_roots[0], finally_roots[1]))
    elif len_roots == 3:
        print('Три корня: {} и {} и {}'.format(finally_roots[0], finally_roots[1], finally_roots[2]))
    else:
        print('Четыре корня: {} и {} и {} и {}'.format(finally_roots[0], finally_roots[1], finally_roots[2],
                                                       finally_roots[3]))


if __name__ == "__main__":
    print('\n============ LAB-01 ============\n')
    main()
    print('\n================================\n')
