# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

import unittest
from equation import calculate


class TestEquation(unittest.TestCase):

    def test_calculate(self):
        self.assertEqual(calculate(1, -10, 9), (-3, -1, 1, 3))
        self.assertEqual(calculate(-4, 16, 0), (-2, 0, 2))
        self.assertEqual(calculate(431, -123, 665), ())

    def test_value(self):
        with self.assertRaises(ValueError) as e:
            calculate(0, 33, 9)

    def test_type(self):
        with (self.assertRaises(TypeError)) as e:
            calculate(12, "B", 4)


if __name__ == '__main__':
    unittest.main()
