from lab_python_oop.rectangle import Rectangle
from lab_python_oop.circle import Circle
from lab_python_oop.square import Square
import pandas as pd


def main():
    print('\n ---- LAB-01 ----\n')
    r = Rectangle("синего", 11, 11)
    c = Circle("зеленого", 11)
    s = Square("красного", 11)
    print(r, c, s, sep='\n')

    # пример выполнения импортированной библеотеки.
    print('\n ---- Module Pandas ----\n')
    table = pd.DataFrame({'Dima': ['Boss', 2, 'BKIT'], 'Permyakov': [777, 'informathion', 777]}, )
    print(table)


if __name__ == "__main__":
    main()
