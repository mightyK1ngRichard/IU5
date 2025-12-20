/**
 * @file MobileWallet.h
 * @brief Заголовочный файл для класса MobileWallet
 *
 * Содержит объявление класса MobileWallet,
 * который моделирует мобильный кошелёк пользователя.
 */

#ifndef MOBILE_WALLET_H
#define MOBILE_WALLET_H

#include <string>

/**
 * @brief Класс, реализующий мобильный кошелёк
 *
 * Позволяет пользователю хранить баланс,
 * пополнять кошелёк и оплачивать покупки через мобильное приложение.
 *
 * Подробнее см. @ref WalletPage
 */
class MobileWallet {
private:
    std::string owner;   ///< Имя владельца кошелька
    double balance;      ///< Баланс кошелька

public:
    /**
     * @brief Конструктор кошелька
     * @param name Имя владельца
     * @param initialBalance Начальный баланс
     */
    MobileWallet(const std::string& name, double initialBalance);

    /**
     * @brief Пополнение кошелька
     * @param amount Сумма пополнения
     * @return true если успешно, false если сумма некорректна
     */
    bool deposit(double amount);

    /**
     * @brief Оплата покупки
     * @param amount Стоимость покупки
     * @return true если оплата прошла успешно, false если недостаточно средств
     */
    bool pay(double amount);

    /**
     * @brief Получить текущий баланс
     * @return Баланс кошелька
     */
    double getBalance() const;

    /**
     * @brief Получить имя владельца
     * @return Имя владельца
     */
    std::string getOwner() const;
};

#endif // MOBILE_WALLET_H