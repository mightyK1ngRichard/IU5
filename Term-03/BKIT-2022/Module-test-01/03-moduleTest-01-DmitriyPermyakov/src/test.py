# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

import unittest
from main import *


class test_of_module_test(unittest.TestCase):

    def setUp(self):
        self.one_to_many = [
            (ide.name, ide.count_users,
             [language.name for el1 in ide.languageID for language in LANGUAGES if language.ID == el1])
            for ide in IDE
        ]
        self.many_to_many_temp = [
            (language.name, language.ID, ide_language.IDE_ID)
            for language in LANGUAGES
            for ide_language in IDE_LANGUAGES
            if language.ID == ide_language.language_ID
        ]
        self.many_to_many = [
            (ide_temp.name, ide_temp.count_users,
             [lang.name for el in ide_temp.languageID for lang in LANGUAGES if lang.ID == el])
            for name_language, languageID, ideID in self.many_to_many_temp
            for ide_temp in IDE
            if ide_temp.ID == ideID
        ]

    def test_task01(self):
        expected_result = [
            ('Visual Studio', 343304, ['C#', 'C++', 'HTML', 'Python', 'Rust']),
            ('VScode', 908311, ['C#', 'C++', 'CSS', 'HTML', 'JavaScript', 'Python', 'Rust'])
        ]
        result = task_01(self.one_to_many)
        self.assertEqual(result, expected_result)

    def test_task02(self):
        expected_result = [
            ('VScode', 7), ('Visual Studio', 5), ('PyCharm', 3), ('XCode', 3), ('Atom', 1), ('LITE', 1),
            ('IntelliJ IDEA', 1), ('Rider', 1)
        ]
        result = task_02(self.one_to_many)
        self.assertEqual(result, expected_result)

    def test_task03(self):
        expected_result = [
            ('Atom', ['CSS']), ('IntelliJ IDEA', ['JavaScript']), ('PyCharm', ['Python', 'HTML', 'CSS']),
            ('Rider', ['C#']), ('Visual Studio', ['C#', 'C++', 'Python', 'HTML', 'Rust']),
            ('XCode', ['Swift', 'HTML', 'CSS'])
        ]
        result = task_03(self.many_to_many)
        self.assertEqual(result, expected_result)


if __name__ == '__main__':
    unittest.main()
