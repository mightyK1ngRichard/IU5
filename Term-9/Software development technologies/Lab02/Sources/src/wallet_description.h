/**
 * @page WalletPage Работа с мобильным кошельком
 *
 * Данный модуль включает:
 * - класс @ref MobileWallet для работы с кошельком;
 * - методы пополнения и оплаты;
 * - пример использования в main.cpp.
 *
 * @ref MobileWallet позволяет легко управлять балансом пользователя.
 *
 * Пример:
 * @code
 * MobileWallet w("Иван", 1000.0);
 * w.deposit(500);
 * w.pay(300);
 * std::cout << w.getBalance();
 * @endcode
 */