#include <conio.h>

#define SIZE 150

bool Check(int arr[SIZE], size_t size) {
    --size;
    if (size == 0) {
        if (arr[0] == 122)
            return true;
        else
            return false;
    }

    for (size_t i = size; i > 0; i--) {
        // если последняя буква z. Далее
        if (arr[size] == 122) {
            // если след.буква не сходится с алфавитом. выход
            if (arr[i] - 1 != arr[i - 1])
                return false;
        } else
            return false;
    }

    return true;
}

int main() {
    size_t ch = 0, i = 0;
    int arr[SIZE]{0};
    do {
        ch = _getch();
        // считываем только латинские буквы
        if (ch > 96 && ch <= 122) {
            _putch(ch);
            arr[i] = ch;
            ++i;
        }

        // считываем пробел
        if (ch == 32) {
            _putch(ch);
            arr[i] = ch;
            ++i;
        }

        // считываем точку
        if (ch == 46)
            _putch(ch);

        // создаем удаление
        if (ch == 8 && i != 0) {
            _putch(8);
            _putch(32);
            _putch(8);
            --i;
        }

    } while (ch != 46);

    arr[i] = 8;
    if (i == 0)
        return 0;

    _putch('\n');

    // ищем индекс последнего слова
    size_t j = i - 1;
    while (arr[j] == 32 && j > 0)
        --j;
    while (arr[j] != 32 && j > 0)
        --j;
    size_t lw = 0;
    if (j == 0)
        lw = j;
    else
        lw = j + 1;
    // кек


    // размер ласт слова
    size_t k = 0;
    for (size_t i2 = lw; i2 < i; i2++) {
        if (arr[i2] == 32)
            break;
        ++k;
    }
    // кек

    int arr2[SIZE]{0};
    bool lol = false;
    size_t n = 0;
    _putch('\n');
    for (size_t i2 = 0; i2 < i; i2++) {
        // длина проверяемого слова
        if (arr[i2] != 32 && arr[i2] != 8) {
            arr2[n] = arr[i2];
            ++n;
        } else {
            if (Check(arr2, n)) {
                // сравниваем с последним словом
                size_t newlw = lw;
                for (size_t i3 = 0; i3 < k; ++i3) {
                    // если буква схожа на букву ласт слова, проверяем дальше
                    if (arr2[i3] == arr[newlw]) {
                        lol = false;
                        ++newlw;
                    }

                        // если не совпала хотя бы 1 буква. стоп
                    else {
                        lol = true;
                        break;
                    }

                    // если длина слова равна длине ласт слова. стоп
                    if (k == n)
                        break;
                }

                // если слово != последнему. печатаем
                if (lol) {
                    for (size_t i3 = 0; i3 < n; i3++)
                        _putch(static_cast<char>(arr2[i3]));
                    _putch(' ');
                }
            }

            // очищаем массив
            for (size_t i3 = 0; i3 < n; i3++)
                arr2[i3] = 0;
            n = 0;
        }

    }
    _putch('\n');
    return 0;
}
