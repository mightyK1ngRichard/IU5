/**
 * @file MobileWallet.cpp
 * @brief Реализация методов класса MobileWallet
 */

#include "MobileWallet.h"

/**
 * @brief Конструктор
 */
MobileWallet::MobileWallet(const std::string& name, double initialBalance)
    : owner(name), balance(initialBalance) {}

/**
 * @brief Пополнение баланса
 */
bool MobileWallet::deposit(double amount) {
    if (amount <= 0) return false;
    balance += amount;
    return true;
}

/**
 * @brief Оплата покупки
 */
bool MobileWallet::pay(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    return true;
}

/**
 * @brief Получение текущего баланса
 */
double MobileWallet::getBalance() const {
    return balance;
}

/**
 * @brief Получение имени владельца
 */
std::string MobileWallet::getOwner() const {
    return owner;
}