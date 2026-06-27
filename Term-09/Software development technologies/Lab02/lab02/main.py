from account import Account
from card import Card


# Демонстрация работы класса Account
if __name__ == "__main__":
    # Создание счета
    account = Account("Иван Иванов", 1000.0)
    print("Создан новый счет:")
    print(account.get_info())
    print()

    # Пополнение счета
    print("Пополнение счета на 500 руб.:")
    account.deposit(500)
    print(account.get_info())
    print()

    # Оплата (снятие средств)
    print("Оплата 200 руб.:")
    account.withdraw(200)
    print(account.get_info())
    print()

    # Проверка баланса
    print(f"Текущий баланс: {account.get_balance()} руб.")
    print()

    # Попытка снять больше, чем есть на счете
    try:
        print("Попытка снять 2000 руб.:")
        account.withdraw(2000)
    except ValueError as e:
        print(f"Ошибка: {e}")
    print(account.get_info())
    print()

    # Работа с карточками
    print("Добавление карт к счету:")
    card1 = Card("1234-5678-9012-3456", "дебетовая")
    card2 = Card("9876-5432-1098-7654", "кредитная")

    account.add_card(card1)
    account.add_card(card2)

    print("Карточки счета:")
    for card in account.get_user_cards():
        print(f"  - {card}")
