# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

class ProgrammingLanguage:
    def __init__(self, ID_language, name_language):
        self.__ID_language = ID_language
        self.__name = name_language

    @property
    def ID(self) -> int:
        return self.__ID_language

    @ID.setter
    def ID(self, ID_language):
        self.__ID_language = ID_language

    @property
    def name(self) -> str:
        return self.__name

    @name.setter
    def name(self, name_language):
        self.__name = name_language
