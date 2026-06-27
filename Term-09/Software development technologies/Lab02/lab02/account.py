from card import Card


class Account:
    """
    Класс для управления пользовательским банковским счетом.

    Этот класс предоставляет базовые операции для работы с банковским счетом:
    - пополнение счета
    - снятие средств
    - проверка баланса

    Атрибуты:
        owner (str): Владелец счета
        balance (float): Текущий баланс счета (по умолчанию 0.0)
    """

    def __init__(self, owner: str, initial_balance: float = 0.0):
        """
        Инициализация счета.

        Args:
            owner (str): Имя владельца счета
            initial_balance (float, optional): Начальный баланс счета. По умолчанию 0.0
        """
        self.owner = owner
        self.balance = initial_balance
        self.user_cards: list[Card] = []

    def deposit(self, amount: float) -> bool:
        """
        Пополнение счета.

        Args:
            amount (float): Сумма для пополнения (должна быть положительной)

        Returns:
            bool: True если операция успешна, False если сумма отрицательная

        Raises:
            ValueError: Если сумма отрицательная
        """
        if amount <= 0:
            raise ValueError("Сумма пополнения должна быть положительной")
        self.balance += amount
        return True

    def withdraw(self, amount: float) -> bool:
        """
        Снятие средств со счета.

        Args:
            amount (float): Сумма для снятия

        Returns:
            bool: True если операция успешна, False если недостаточно средств

        Raises:
            ValueError: Если сумма отрицательная или недостаточно средств
        """
        if amount <= 0:
            raise ValueError("Сумма снятия должна быть положительной")

        if amount > self.balance:
            raise ValueError("Недостаточно средств на счете")

        self.balance -= amount
        return True

    def get_balance(self) -> float:
        """
        Получение текущего баланса счета.

        Returns:
            float: Текущий баланс счета
        """
        return self.balance

    def get_info(self) -> str:
        """
        Получение информации о счете.

        Returns:
            str: Информация о владельце и балансе счета
        """
        return f"Владелец: {self.owner}, Баланс: {self.balance:.2f} руб."

    def add_card(self, card: Card) -> None:
        """
        Добавление карты к счету.

        Args:
            card (Card): Карта для добавления
        """
        self.user_cards.append(card)

    # Пользовательские карточки этого счёта
    def get_user_cards(self) -> list[Card]:
        """
        Получение списка пользовательских карточек этого счета.

        Returns:
            list[Card]: Список пользовательских карточек этого счета
        """
        return self.user_cards
