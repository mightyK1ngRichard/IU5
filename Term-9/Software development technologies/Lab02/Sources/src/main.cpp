/**
 * @file main.cpp
 * @brief Тестовый пример работы с MobileWallet
 */

#include <iostream>
#include "MobileWallet.h"

// g++ main.cpp MobileWallet.cpp -o wallet_app
// ./wallet_app
int main() {
    MobileWallet wallet("Дмитрий", 1000.0);

    std::cout << "Владелец: " << wallet.getOwner() << std::endl;
    std::cout << "Начальный баланс: " << wallet.getBalance() << " руб." << std::endl;

    wallet.deposit(200.0);
    std::cout << "После пополнения: " << wallet.getBalance() << " руб." << std::endl;

    if (wallet.pay(300.0)) {
        std::cout << "Оплата прошла успешно!" << std::endl;
    } else {
        std::cout << "Недостаточно средств." << std::endl;
    }

    std::cout << "Текущий баланс: " << wallet.getBalance() << " руб." << std::endl;

    return 0;
}