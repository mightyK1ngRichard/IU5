# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>
import unittest
from src.functions import fibonacci


# python3 -m unittest -v libs/*
class TestFibonacci(unittest.TestCase):
    def test_numbers(self):
        self.assertEqual(len(list(fibonacci(10))), 10)
        self.assertEqual(list(fibonacci(10)), [0, 1, 1, 2, 3, 5, 8, 13, 21, 34])

    def test_iteration(self):
        res = fibonacci(2)
        self.assertEqual(next(res), 0)
        self.assertEqual(next(res), 1)

    def test_type_numbers(self):
        self.assertRaises(TypeError, fibonacci('5'))
