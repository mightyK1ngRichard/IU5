#include "Header.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // показ работы оператора присваивания и копирования
    /*Party one; Party two;
    char* name = new char[10];
    strcpy_s(name, 10, "ЛДПР");
    one.SetName(name);
    one.SetCountMemder(666);
    one.SetCapital(666);
    one.SetIQ(666);
    strcpy_s(name, 10, "КПРФ");
    two.SetName(name);
    two.SetCountMemder(777);
    two.SetCapital(777);
    two.SetIQ(777);
    std::cout << one << std::endl << two << std::endl;
    Party three = one;
    std::cout << "*-*-*-*-*-*- three -*-*-*-*-*-\n";
    std::cout << three;
    std::cout << "\n*-*-*-*-*-*- four -*-*-*-*-*-\n";
    Party four;
    four = two;
    std::cout << four << std::endl;
    return 27;*/
    //---------------------------------------------------

    Party* party = new Party[10];
    size_t size = Read(party);

    while (true)
    {
        switch (Menu())
        {
        case 1: Add(party, size); break;
        case 2: Edit(party, size); break;
        case 3: Sort(party, size); break;
        case 4: SaveToFile(party, size); break;
        case 5: Print(party, size); break;
        case 6: delete[] party; return 0;
        case 7: system("cls"); break;
        case 8: Delete(party, size); break;
        default: std::cout << "\x1b[31mВводите числа (1-5)\x1b[0m\n"; break;
        }
    }
}
