#include "Header.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // демонстрация оператора присваивания 
    /*Planet Me;
    char* name_Me = new char[5];
    strcpy_s(name_Me, 5, "лол");
    Me.SetName(name_Me);
    Me.SetDimeter(5);
    Me.SetLife(0);
    Me.SetSatellite(777);
    Planet Me2;
    Me2 = Me;
    return 27;*/

    Planet* planet = new Planet[SIZE];
    size_t size = Read(planet);
    if (size == 0) { std::cout << "\x1b[31mФайл пуст!\x1b[0m\n"; return 0; }
   
    while (true)
    {
        switch (Menu())
        {
        case 1: Add(planet, size); break;
        case 2: Edit(planet, size); break;
        case 3: Sort(planet, size); break;
        case 4: SaveToFile(planet, size); break;
        case 5: Print(planet, size); break;
        case 6: delete[] planet; return 0;
        case 7: system("cls"); break;
        case 8: Delete(planet, size); break;
        default: std::cout << "\x1b[31mВводите числа (1-5)\x1b[0m\n"; break;
        }
    }
}
