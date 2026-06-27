# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

class DevelopmentEnvironment:
    def __init__(self, ID_environment, name_environment, count_users, *args):
        """
        :param ID_environment: id языка программирования. Int.
        :param name_environment: Название языка программирования. Str.
        :param args: IDE для этих языков программирования. Tuple.
        """
        self.__ID = ID_environment
        self.__name = name_environment
        self.__languageID = args
        self.__count_users = count_users

    @property
    def ID(self) -> int:
        return self.__ID

    @ID.setter
    def ID(self, ID_environment):
        self.__ID = ID_environment

    @property
    def name(self) -> str:
        return self.__name

    @name.setter
    def name(self, name_env):
        self.__name = name_env

    @property
    def languageID(self):
        return self.__languageID

    @languageID.setter
    def languageID(self, id):
        self.__languageID = id

    @property
    def count_users(self) -> int:
        return self.__count_users

    @count_users.setter
    def count_users(self, count):
        if type(count) != int:
            raise TypeError('Format of count_users must be Int!')
        self.__count_users = count
