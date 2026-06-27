# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

from libs.DevelopmentEnvironment import DevelopmentEnvironment
from libs.IdeLanguage import IdeLanguage
from libs.ProgrammingLanguage import ProgrammingLanguage
from tasks import task_01
from tasks import task_02
from tasks import task_03

LANGUAGES = [
    ProgrammingLanguage(0, 'C++'),
    ProgrammingLanguage(1, 'C#'),
    ProgrammingLanguage(2, 'Python'),
    ProgrammingLanguage(3, 'Swift'),
    ProgrammingLanguage(4, 'JavaScript'),
    ProgrammingLanguage(5, 'CSS'),
    ProgrammingLanguage(6, 'HTML'),
    ProgrammingLanguage(7, 'Rust'),
    ProgrammingLanguage(8, 'Go')
]
IDE = [
    DevelopmentEnvironment(0, 'PyCharm', 267209, 2, 6, 5),
    DevelopmentEnvironment(1, 'Atom', 171106, 5),
    DevelopmentEnvironment(2, 'LITE', 305374, 8),
    DevelopmentEnvironment(3, 'XCode', 253462, 3, 6, 5),
    DevelopmentEnvironment(4, 'Visual Studio', 343304, 1, 0, 2, 6, 7),
    DevelopmentEnvironment(5, 'IntelliJ IDEA', 426855, 4),
    DevelopmentEnvironment(6, 'Rider', 308911, 1),
    DevelopmentEnvironment(7, 'VScode', 908311, 0, 1, 2, 4, 5, 6, 7)
]
IDE_LANGUAGES = [
    IdeLanguage(0, 4),
    IdeLanguage(1, 6),
    IdeLanguage(2, 0),
    IdeLanguage(3, 3),
    IdeLanguage(4, 5),
    IdeLanguage(5, 1)
]


def main_code():
    # Пояснение: Так как у в одной среде разработки можно использовать несколько языков,
    # я создаю список в списке. Т.е список языков для определённого IDE.
    one_to_many = [
        (ide.name, ide.count_users,
         [language.name for el1 in ide.languageID for language in LANGUAGES if language.ID == el1])
        for ide in IDE
    ]
    many_to_many_temp = [
        (language.name, language.ID, ide_language.IDE_ID)
        for language in LANGUAGES
        for ide_language in IDE_LANGUAGES
        if language.ID == ide_language.language_ID
    ]
    many_to_many = [
        (ide_temp.name, ide_temp.count_users,
         [lang.name for el in ide_temp.languageID for lang in LANGUAGES if lang.ID == el])
        for name_language, languageID, ideID in many_to_many_temp
        for ide_temp in IDE
        if ide_temp.ID == ideID
    ]

    # Можно посмотреть содержимое списков.
    # print(*one_to_many, sep='\n', end=f'\n {"=" * 30}\n')
    # print(*many_to_many_temp, sep='\n', end=f'\n {"=" * 30}\n')
    # print(*many_to_many, sep='\n', end=f'\n {"=" * 30}\n')

    print(f'{"-" * 10} Задание №1. {"-" * 10}')
    print(*task_01(one_to_many), sep='\n', end='\n\n')
    print(f'{"-" * 10} Задание №2. {"-" * 10}')
    print(*task_02(one_to_many), sep='\n', end='\n\n')
    print(f'{"-" * 10} Задание №3. {"-" * 10}')
    print(*task_03(many_to_many), sep='\n', end='\n\n')


if __name__ == '__main__':
    main_code()
