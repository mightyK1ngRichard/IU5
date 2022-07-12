#include "Header.h"

// C:\Users\dimap\source\repos\Laba_9\x64\Debug\Laba_9.exe
int main(int argc, char* argv[])
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    setlocale(0, "rus");
    d* words = new d[100];
    size_t size = read(words);

    while (true)
    {
        switch (Menu())
        {
        case 1:
            Add(words, size);
            break;

        case 2:
            Delete(words, size);
            break;

        case 3:
            TranslateToRus(words, size);
            break;

        case 4:
            TranslateToEng(words, size);
            break;

        case 5:
            Print(words, size);
            break;

        case 6:
            FillFile(words, size);
            break;

        case 7:
            delete[] words;
            return 0;

        case 8:
            system("cls");
            break;
        default:
            cout << "\x1b[31mНадо вводить число от 1 до 7.\x1b[0m\n";
            break;
        }

    }
}
