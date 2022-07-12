#include "Header.h"

void Add(d* words, size_t& size)
{
    char word[100];
    cout << "Enter an Eglish word: ";
    cout << "\x1b[35m";
    cin >> word;
    cout << "\x1b[0m";

    words[size].eng = new char[strlen(word) + 1];
    copy(word, word + strlen(word) + 1, words[size].eng);
    cout << "Enter a Russian word: ";
    cout << "\x1b[35m";
    cin >> word;
    cout << "\x1b[0m";

    words[size].rus = new char[strlen(word) + 1];
    copy(word, word + strlen(word) + 1, words[size].rus);
    ++size;
    cout << endl;
}

void Delete(d* words, size_t& size)
{
    dict_sort(words, size);
    bool flag = false;
    char word[30];
    cout << "Enter the english word for deletion: ";
    cout << "\x1b[35m";
    cin >> word;
    cout << "\x1b[0m";
    size_t l = 0;
    size_t r = size;
    size_t middle;
    while (l <= r)
    {
        middle = (l + r) / 2;
        if (strcmp(words[middle].eng, word) == 0)
        {
            flag = true;
            break;
        }
        if (strcmp(words[middle].eng, word) > 0)
            r = middle - 1;
        else
            l = middle + 1;
    }

    if (flag)
    {
        delete[] words[middle].eng;
        delete[] words[middle].rus;
        for (size_t i = middle; i < size - 1; i++)
        {
            words[i].eng = words[i + 1].eng;
            words[i].rus = words[i + 1].rus;
        }
        --size;
    }
    else
        cout << "\x1b[31mNot found\x1b[0m\n\n";

}

void TranslateToRus(d* words, size_t size)
{
    dict_sort(words, size);
    bool flag = false;
    char word[30];
    cout << "Enter the english word for the translation: ";
    cout << "\x1b[35m";
    cin >> word;
    cout << "\x1b[0m";
    size_t l = 0;
    size_t r = size;
    size_t middle;
    while (l <= r)
    {
        middle = (l + r) / 2;
        if (strcmp(words[middle].eng, word) == 0)
        {
            flag = true;
            break;
        }
        if (strcmp(words[middle].eng, word) > 0)
            r = middle - 1;
        else
            l = middle + 1;
    }

    if (flag)
        cout << "\x1b[36mTranslation: " << words[middle].rus << "\x1b[0m\n\n";
    else
        cout << "\x1b[31mNot found\x1b[0m\n\n";
}

void TranslateToEng(d* words, size_t size)
{
    char word[30];
    cout << "Enter the russian word for the translation: ";
    cout << "\x1b[35m";
    cin >> word;
    cout << "\x1b[0m";
    bool flag = false;
    for (size_t i = 0; i < size; i++)
    {
        if (strcmp(words[i].rus, word) == 0)
        {
            cout << "\x1b[36mTranslation: " << words[i].eng << "\x1b[0m\n\n";
            flag = true;
            break;
        }
    }
    if (!flag)
        cout << "\x1b[31mNot found\x1b[0m\n\n";

}

void Print(d* words, size_t size)
{
    dict_sort(words, size);
    cout << "OUR DICTIONARY: \x1b[36m\n\n";
    for (size_t i = 0; i < size; ++i)
        cout << "    " << words[i].eng << " - " << words[i].rus << endl;
    cout << "\x1b[0m\n";
}

void FillFile(d* words, size_t size)
{
    ofstream fin("dictionary.txt");
    dict_sort(words, size);
    for (size_t i = 0; i < size; ++i)
    {
        if (i != size - 1)
            fin << words[i].eng << " - " << words[i].rus << endl;
        else
            fin << words[i].eng << " - " << words[i].rus;
    }
}

size_t read(d* words)
{
    setlocale(0, "rus");
    ifstream f("dictionary.txt");
    size_t size = 0;
    while (!f.eof())
    {
        char* str = new char[100];
        f >> str;
        // создаем массив для англ слова 
        words[size].eng = new char[strlen(str) + 1];
        copy(str, str + strlen(str) + 1, words[size].eng);

        f >> str;
        f >> str;
        // создаем массив для англ слова 
        words[size].rus = new char[strlen(str) + 1];
        copy(str, str + strlen(str) + 1, words[size].rus);
        ++size;
    }
    return size;
}

size_t Menu()
{
    cout << "Меню:\n";
    cout << "1. добавление слов в словарь\n";
    cout << "2. удаление слов из словаря\n";
    cout << "3. перевод слов с английского на русский\n";
    cout << "4. перевод слов с русского на английский\n";
    cout << "5. просмотр словаря\n";
    cout << "6. вывод словаря в файл\n";
    cout << "7. выход\n";
    cout << "Введите пункт меню: ";
    size_t number_of_menu = GetDataInt();
    return number_of_menu;
}

size_t GetDataInt()
{
    // провенрка введённых данных
    while (true)
    {
        size_t a;
        cout << "\x1b[35m";
        cin >> a;
        cout << "\x1b[0m";
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\x1b[31mПроверьте введённые данные: \x1b[0m";
        }
        else
        {
            cin.ignore(32767, '\n');
            return a;
        }
    }
}

//void dict_sort(d* words, size_t size)
//{
//    sort(words, words + size, [](d first, d second) {return strcmp(first.eng, second.eng) < 0; });
//}


void dict_sort(d* words, size_t size)
{
    for (size_t i = 1; i < size; i++)
    {
        for (size_t i2 = 0; i2 < size - i; i2++)
        {
            if (strcmp(words[i2].eng, words[i2 + 1].eng) > 0)
            {
                swap(words[i2].eng, words[i2 + 1].eng);
                swap(words[i2].rus, words[i2 + 1].rus);
            }
        }
    }
}