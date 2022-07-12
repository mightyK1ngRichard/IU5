#include "Header.h"
// C:\Users\dimap\source\repos\pract_with_vector\x64\Debug\pract_with_vector.exe
int main(int argc, char* argv[])
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);
    vector<dis> data;
    string Go;
    Read(data);

    while (true)
    {
        switch (Menu())
        {
        case 1:
            Add(data);
            break;
        case 2:
            Delete(data);
            break;
        case 3:
            Edit(data);
            break;
        case 4:
            FillFile(data);
            break;
        case 5:
            Print(data);
            break;
        case 6:
            FindData(data);
            break;
        case 7:
            cout << "Хотите сохранить данные в файл? (Введите \"да\" или \"нет\"): ";
            Go = GetDataString();
            if (Go == "да" || Go == "Да")
            {
                FillFile(data);
                return 0;
            }
            else
                return 0;
        case 8:
            
                            system("cls");
            break;
        default:
            cout << "\x1b[31mВведите число от 1 до 7: \x1b[0m\n";
            break;
        }
    }
    
}

