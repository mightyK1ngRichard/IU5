class Card:
    """
    Класс для представления банковской карты.

    Атрибуты:
        card_number (str): Номер карты
        card_type (str): Тип карты (дебетовая/кредитная)
    """

    def __init__(self, card_number: str, card_type: str = "дебетовая"):
        """
        Инициализация карты.

        Args:
            card_number (str): Номер карты
            card_type (str): Тип карты
        """
        self.card_number = card_number
        self.card_type = card_type

    def __str__(self) -> str:
        return f"{self.card_type} карта {self.card_number}"
