#include "Header.h"
#include <ctime>
size_t CheckString(std::list<Together>& one, const size_t& size) {
    std::string index;
    size_t k = 0;
    while (true) {
        std::cout << "\n\n| Что вы хотите удалить? Введите индекс: ";
        try {
            std::cin >> index;
            // если буква, исключение
            for (size_t i = 0; i < index.length(); ++i) {
                if (!(index[i] >= '0' && index[i] <= '9'))
                    throw "\n\n| ERROR: Буква в индексе!";
            }
            // если введённый индекс больше существующего максимума
            if (std::stoi(index) > size)
                throw "\n\n| ERROR: Такого индекса не существует!";

            return std::stoi(index);
        }
        catch (const char* ex) {
            system("cls");
            k = 0;
            for (auto& i : one) {
                if (k == 0) {
                    std::cout << "----------------index [" << k << "]\n";
                }
                else {
                    std::cout << "\n----------------index [" << k << "]\n";
                }
                i.a.Print();
                std::cout << std::endl;
                i.b.Print();
                std::cout << std::endl;
                i.c.Print();
                ++k;
            }
            std::cout << ex << std::endl;
            std::cout << "| Повторите ввод!\n";
        }
    }
}

int main() {
    /*Deriv1 one1(11);
    one1.Print();
    std::cout << std::endl;
    Deriv2 one2(22);
    one2.Print();
    std::cout << std::endl;
    Deriv3 one3(33);
    one3.Print();
    std::cout << std::endl;*/    
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "------Pointer A-----\n";
    Abstr* pA;
    Deriv1 a(1);
    Deriv2 b(2);
    Deriv3 c(3);
    pA = &a;
    pA->Print();
    std::cout << std::endl;
    pA = &b;
    pA->Print();
    std::cout << std::endl;
    pA = &c;
    c.Print();
    std::cout << std::endl;
    std::cout << "--------------\n";

    std::list<Together> one;
    
    size_t k = 0;
    size_t size = 0;
    std::cout << "| Сколько чисел вы хотите внести в список? size = ";
    std::cin >> size;
    // заполнение list<Together> числами
    for (double i = 0; i < size; ++i) {
        Together all;
        all.a = rand() % 10;
        all.b = rand() % 10;
        all.c = rand() % 10;
        one.push_back(all);
    }
    --size;
    for (auto& i : one) {
        // избегаем пробел в начале для красоты
        if (k == 0) {
            std::cout << "----------------index [" << k << "]\n";
        }
        else {
            std::cout << "\n----------------index [" << k << "]\n";
        }
        i.a.Print();
        std::cout << std::endl;
        i.b.Print();
        std::cout << std::endl;
        i.c.Print();
        ++k;
    }
    // ввод индекса с проверкой на существование и отсутствие букв
    size_t index = CheckString(one, size);
    k = 0;
    // поиск элемента для удаления
    for (auto& i : one) {
        if (k == index) {
            one.remove(i);
            break;
        }
        ++k;
    }
    k = 0;
    for (auto& i : one) {
        std::cout << "\n---------[" << k << "]----------\n";
        i.a.Print();
        std::cout << std::endl;
        i.b.Print();
        std::cout << std::endl;
        i.c.Print();
        ++k;
    }

    std::cout << "\n\n//////////////////NEW_LIST/////////////////\n\n";
    std::list<Abstr*> new_list;
    for (size_t i = 0; i < 2; ++i) {
        Abstr* pd = new Deriv1(rand() % 10);
        new_list.push_back(pd);
        pd->Print();
        std::cout << std::endl;
    }
    for (size_t i = 0; i < 2; ++i) {
        Abstr* pd = new Deriv2(rand() % 10);
        new_list.push_back(pd);
        pd->Print();
        std::cout << std::endl;
    }
    for (size_t i = 0; i < 2; ++i) {
        Abstr* pd = new Deriv3(rand() % 10);
        new_list.push_back(pd);
        pd->Print();
        std::cout << std::endl;
    }
    k = 0;
    for (auto& i : new_list) {
        std::cout << "\n---------[" << k << "]----------\n";
        i->Print();
        ++k;
    }
    std::cout << std::endl;
    for (auto& i : new_list) {
        delete i;
    }

    return 0;
}
