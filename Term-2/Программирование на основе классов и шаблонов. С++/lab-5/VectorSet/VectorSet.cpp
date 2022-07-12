// Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>

#include "Header.h"
int main() {
    Vector<String> one;
    String word = "Agags";
    one.Push_back(word);
    one.Push_back("Bsdafsd");
    one.Push_back("Casdfd");
    one.Push_back("Ddfsd");
    one.Push_back("Dima");
    std::cout << one << std::endl;
    std::cout << "======= Remove =======\n";
    one.Remove(0);
    std::cout << one << std::endl;
    std::cout << "======= Find =======\n";
    std::cout << one[one.Find("Casdfd")] << std::endl;

    Vector<int> two;
    two.Push_back(1);
    two.Push_back(2);
    two.Push_back(3);
    two.Push_back(4);
    two.Push_back(5);
    std::cout << two << std::endl;
    std::cout << "======= Remove =======\n";
    two.Remove(0);
    std::cout << two << std::endl;
    std::cout << "======= Find =======\n";
    std::cout << std::setw(10) << two[two.Find(3)] << std::endl;

    Vector<char> three;
    three.Push_back('a');
    three.Push_back('b');
    three.Push_back('c');
    three.Push_back('d');
    three.Push_back('e');
    std::cout << three << std::endl;
    std::cout << "======= Remove =======\n";
    three.Remove(4);
    std::cout << three << std::endl;
    std::cout << "======= Find =======\n";
    std::cout << std::setw(10) << three[three.Find('c')] << std::endl;

    Set<int> set;
    set.Add(2);
    set.Add(4);
    set.Add(5);
    set.Add(6);
    std::cout << set << std::endl;
    Set<int> set2;
    set2.Add(1);
    set2.Add(2);
    set2.Add(4);
    set2.Add(3);
    std::cout << set2 << std::endl;
    Set<int> set3 = set + set2;
    std::cout << set3 << std::endl;
    std::cout << "-----_________-------\n";
    Set<int> set4 = set - set2;
    std::cout << set4 << std::endl;
    bool nice = set4.is_element(5);
    std::cout << nice << std::endl;
    return 0;
}
