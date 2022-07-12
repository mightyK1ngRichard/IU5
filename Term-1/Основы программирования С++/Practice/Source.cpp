#include "Header.h"

void Read(vector<dis>& data)
{
    // если файл не найден, создаём его
    ifstream f("data.txt");
    if (!f)
    {
        ofstream("data.txt");
        return;
    }
    
    while (!f.eof())
    {
        dis data2;
        // считываем всю строку из файла
        string help;
        getline(f, help);

        // если файл пустой, стоп
        if (help.length() == 0)
            return;

        size_t i2 = 0;
        size_t n = 0;     
      
        // бежим по считанной строке и отбираем только текст до "|"
        for (size_t i = 0; i < help.length(); i++)
        {
            // пропускаем пробелы
            if (help[i] == ' ')
                continue;

            // если встретили '|' значит все слова считаны и заносим в структуру
            if (help[i] != '|')
            {
                // если было два слова, разделяем их пробелом 
                ++n;
                if (i != 0 && n > 1)
                {
                    if (help[i - 1] == ' ')
                        data2.name += ' ';
                }
                // заносим в структуру
                data2.name += help[i];
            }

            // счёт кол-ва слов
            else
            {
                i2 = ++i;
                break;
            }
        }

        // переводим цифру из string в структуру для часов
        string num = "";
        for (size_t i = i2; i < help.length(); i++)
        {
            if (help[i] != '|')
            {
                if (help[i] == ' ')
                    continue;
                else
                    num += help[i];
            }

            else
            {
                i2 = ++i;
                break;
            }
        }
        data2.hour = stoi(num);

        // переводим цифру из string в структуру для семестра
        num = "";
        for (size_t i = i2; i < help.length(); i++)
        {
            if (help[i] != '|')
            {
                if (help[i] == ' ')
                    continue;
                else
                    num += help[i];
            }

            else
            {
                i2 = ++i;
                break;
            }
        }
        data2.sem = stoi(num);

        // заносим в структуру
        data.push_back(data2);
    }

}

void Add(vector<dis>& data)
{
    string GO = "";
    do
    {

        string discipline; size_t hour; size_t sem;
        dis data2;
        cout << "\nВведите название дисциплины: ";
        // ввод нового слова с проверкой 
        discipline = GetDataString();

        // проверка, чтобы ввели слово без лишних пробелов
        int n = 0; // помогает следить за наличием слов в начале
        for (size_t i = 0; i < discipline.length(); i++)
        {
            if (discipline[i] == ' ')
                continue;

            if (discipline[i] != '|')
            {
                ++n;
                if (i != 0 && n > 1)
                {
                    if (discipline[i - 1] == ' ')
                        data2.name += ' ';
                }
                data2.name += discipline[i];
            }
            else
                break;
        }

        // проверка на наличие слова в структуре
        bool creat = false;
        for (size_t i = 0; i < data.size(); i++)
        {
            if (data2.name == data[i].name)
                creat = true;
        }


        // если слово существует, спрашиваем пользователя заносить ли и просим данные если "да"
        if (creat)
        {
            cout << "\x1b[31mДанная дисциплина уже существует!\x1b[0m\n"
                << "Вы уверены, что хотите добавить \"" << data2.name << "\"? Ответьте \" да\" или \" нет\": ";
            string contin = GetDataString();
            if (contin == "Да" || contin == "да")
            {
                cout << "Введите кол-во часов: ";
                hour = GetDataInt();
                cout << "Введите номер семестра: ";
                sem = GetDataInt();

                data2.hour = hour;
                data2.sem = sem;

                cout << "Вы ввели: ";
                cout << "\x1b[31m"
                    << data2.name << ' ' << data2.hour << ' ' << data2.sem
                    << "\x1b[0m";

                cout << "\nЗанести в базу данных? (введите \"да\" или \"нет\"): ";
                string question = GetDataString();

                if (question == "Да" || question == "да")
                    data.push_back(data2);
                cout << endl << endl;
            }
        }

        // если не существует, просим ввести данные по времени и номеру семестра
        else
        {
            cout << "Введите кол-во часов: ";
            hour = GetDataInt();
            cout << "Введите номер семестра: ";
            sem = GetDataInt();

            data2.hour = hour;
            data2.sem = sem;

            cout << "Вы ввели: ";
            cout << "\x1b[31m"
                << data2.name << ' ' << data2.hour << ' ' << data2.sem
                << "\x1b[0m";

            cout << "\nЗанести в базу данных? (введите \"да\" или \"нет\"): ";
            string question = GetDataString();

            if (question == "Да" || question == "да")
                data.push_back(data2);
            cout << endl << endl;
        } 

        // спрашиваем пользователя, хочет ли повторить
        cout << "Хотите продолжить? Отвечайте \"Продожить\" или \"нет\": ";
        GO = GetDataString();

    } while (GO == "продолжить" || GO == "Продолжить");
    cout << endl;

}

void Sort(vector<dis>& data)
{
    // сортировка по алфавиту
    for (size_t i = 1; i < data.size(); i++)
    {
        for (size_t i2 = 0; i2 < data.size() - i; i2++)
        {
            if (data[i2].name > data[i2 + 1].name)
            {
                swap(data[i2].name, data[i2 + 1].name);
                swap(data[i2].hour, data[i2 + 1].hour);
                swap(data[i2].sem, data[i2 + 1].sem);
            }
        }
    }
}

void Delete(vector<dis>& data)
{
    // если файл пустой, стоп
    if (data.size() == 0)
    {
        cout << "Файл пустой!\n";
        return;
    }

    Sort(data);
    bool flag = false;
    string discipline;

    // вводим дисциплину для удаление. проверка на ввод
    cout << "\nВведите дисциплину для удаления: ";
    discipline = GetDataString();


    // избежим случайных пробелов введённые пользователем
    string dis_new = "";
    int n = 0;
    for (size_t i = 0; i < discipline.length(); i++)
    {
        if (discipline[i] == ' ')
            continue;

        ++n;
        if (i != 0 && n > 1)
        {
            if (discipline[i - 1] == ' ')
                dis_new += ' ';
        }
        dis_new += discipline[i];

    }

    // создаём список для хранения индексов слов, которые схожи с введённым для удаления
    vector<size_t> data2;
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].name == dis_new)
            data2.push_back(i);
    }
    

    // выводим все схожие слова из структуры data по индексу data2[i]. 
    cout << "\n\n\x1b[31mНайденные данные на просьбу \"" << dis_new << "\":\x1b[0m\n";
    cout << "\x1b[36m";
    for (size_t i = 0; i < data2.size(); i++)
        cout << setw(10) << data[data2[i]].name << ' ' << data[data2[i]].hour << ' ' << data[data2[i]].sem << endl;
    cout << "\x1b[0m\n";


    // если слово для удаления одно. удаляем
    if (data2.size() == 1)
        data.erase(data.begin() + data2[0]);

    // если введённого слова нге существует
    else if (data2.size() == 0)
        cout << "\x1b[31mNot found\x1b[0m\n\n";

    // если найденно два и более слова. Задаём вопросы пользователю
    else
    {
        // пользователь уточняет удаление дисциплины по часам и семестру
        // спрашиваем пользователя, пока он не введёт существующие данные
        size_t hour, sem;
        int lol = 0;
        do
        {
            cout << "Введите кол-во часов и семестр дисциплины для удаления:\n"
                << "Введите кол-во часов: ";
            hour = GetDataInt();
            cout << "Введите номер семестра: ";
            sem = GetDataInt();

            for (size_t i = 0; i < data2.size(); i++)
            {
                if (data[data2[i]].hour == hour && data[data2[i]].sem == sem)
                {
                    data.erase(data.begin() + data2[i]);
                    ++lol;
                }
            }
            if (lol == 0)
                cout << "\n\x1b[31mВы ввели несуществующие данные. Повторите операцию!\x1b[0m\n\n";

        } while (lol == 0);
    }
    cout << endl;
}

void FillFile(vector<dis>& data)
{
    // заносим данные в файл в виде таблицы
    size_t NUM = FindMax(data);
    ofstream fin("data.txt");
    Sort(data); 
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (i != data.size() - 1)
            fin << data[i].name << setw(NUM - data[i].name.length()) << " | "
            << setw(10) << data[i].hour << setw(10) << " | " << setw(10) << data[i].sem << endl;
        else
            fin << data[i].name << setw(NUM - data[i].name.length()) << " | "
            << setw(10) << data[i].hour << setw(10) << " | " << setw(10) << data[i].sem;
    }
    cout << endl;
}

void Print(vector<dis>& data)
{
    // если файл пустой, стоп
    if (data.size() == 0)
    {
        cout << "\x1b[31m\nФайл пустой!\x1b[0m\n\n";
        return;
    }

    Sort(data);
    size_t NUM = FindMax(data);
    // шапка
    cout << "\x1b[31m" << "     Дисциплина" << setw(NUM - 16) << '|' << setw(10)
        << "   кол-во часов" << setw(5) << '|' << setw(10) << "    Номер семестра\x1b[0m\n";
    cout << "\x1b[36m";

    // таблица
    for (size_t i = 0; i < data.size(); i++)
    {
        if (i != data.size() - 1)
            cout << data[i].name << setw(NUM - data[i].name.length()) << " | "<< setw(10) 
            << data[i].hour << setw(10) << " | " << setw(10) << data[i].sem << endl;
        else
            cout << data[i].name << setw(NUM - data[i].name.length()) << " | "
            << setw(10) << data[i].hour << setw(10) << " | " << setw(10) << data[i].sem;
    }
    cout << endl;
    for (size_t i = 0; i < NUM + 35; i++)
        cout << '_';
    cout << "\x1b[0m";
    cout << endl << endl;
}

size_t FindMax(vector<dis>& data)
{
    // эта функция ищет самую длинную строку для красивой таблицы
    size_t max = data[0].name.length();
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].name.length() > max)
            max = data[i].name.length();
    }
    if (max + 5 > 15)
        return max + 5;
    else
        return 22;
}

size_t Menu()
{
    size_t report;
    cout << "*-*-*-*-*-* МЕНЮ *-*-*-*-*-*\n";
    cout << "1. Добавить дисциплину\n"
        << "2. Удалить дисциплину\n"
        << "3. Редактировать данные\n"
        << "4. Добавить в файл\n"
        << "5. Печать\n"
        << "6. Поиск дисциплины\n"
        << "7. Выход\n";
    cout << "Выберете пункт: ";
    report = GetDataInt();
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    if (report > 0 && report <= 8)
        return  report;

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

string GetDataString()
{
    // провенрка введённых данных
    string name = "";
    cout << "\x1b[35m";
    getline(cin, name);
    cout << "\x1b[0m";
    
    while (!ControlName(name))
    {
        cout << "\x1b[31mСтрока не может быть пустой, содержать числа или \"|\", попробуйте снова : \x1b[0m\n";
        cout << "Вводите: ";
        cout << "\x1b[35m";
        getline(cin, name);
        cout << "\x1b[0m";
    }
    return name;
}

string GetDataStrinhgForInt()
{
    // провенрка введённых данных
    string name = "";

    cout << "\x1b[35m";
    getline(cin, name);
    cout << "\x1b[0m";

    while (!ControlStrinhgForInt(name))
    {
        cout << "\x1b[31mБуквы запрещены! Попробуйте снова: \x1b[0m\n";
        cout << "Вводите: ";
        cout << "\x1b[35m";
        getline(cin, name);
        cout << "\x1b[0m";
    }
    return name;
}

bool ControlStrinhgForInt(string name)
{
    // провенрка введённых данных

    if (name == "Не хочу"  || name == "не хочу")
        return true;
    
    if (name.length() == 0)
        return false;

    for (size_t i = 0; i < name.length(); i++)
    {
        if (name[i] >= '0' && name[i] <= '9')
            continue;
        else
            return false;
    }
}

bool ControlName(string name)
{
    // провенрка введённых данных
    if (name.length() == 0)
        return false; 

    for (size_t i = 0; i < name.length(); i++)
        if (name[i] >= '0' && name[i] <= '9' || name[i] == '|')
            return false; 

    return true; 
}

void FindData(vector<dis>& data)
{
    cout << "Введите дисциплину для поиска: ";
    string discipline = GetDataString();
    // избежим случайных пробелов введённые пользователем
    string dis_new = "";
    int n = 0;
    for (size_t i = 0; i < discipline.length(); i++)
    {
        if (discipline[i] == ' ')
            continue;

        ++n;
        if (i != 0 && n > 1)
        {
            if (discipline[i - 1] == ' ')
                dis_new += ' ';
        }
        dis_new += discipline[i];

    }
    
    // показываем пользователю все найденные данные по его запросу
    size_t k = 0;
    cout << "\x1b[31mРезультаты поиска по запросу \"" << dis_new << "\":\x1b[0m\n";
    cout << "\x1b[36m";
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].name == dis_new)
        {
            cout << setw(10) << data[i].name << ' ' << data[i].hour << ' ' << data[i].sem << ' ' << endl;
            ++k;
        }
    }
    cout << "\x1b[0m\n\n";

    // если слов таких нет, пишем:
    if (k == 0)
        cout << "\x1b[31mNot found\x1b[0m\n\n";
}

void Edit(vector<dis>& data)
{
    // если файл пустой, стоп
    if (data.size() == 0)
    {
        cout << "Файл пустой!\n";
        return;
    }

    string GO = "";
    do
    {
        string dis_new = "";
        cout << "Какую дисциплину вы хотите изменить? ";
        dis_new = GetDataString();

        // избежим случайных пробелов введённые пользователем
        string discipline = "";
        int n = 0;
        for (size_t i = 0; i < dis_new.length(); i++)
        {
            if (dis_new[i] == ' ')
                continue;

            ++n;
            if (i != 0 && n > 1)
            {
                if (dis_new[i - 1] == ' ')
                    discipline += ' ';
            }
            discipline += dis_new[i];

        }

        // заносим инедексы схожих слов в список
        vector<size_t> data2;
        for (size_t i = 0; i < data.size(); i++)
        {
            if (data[i].name == dis_new)
                data2.push_back(i);
        }

        // выводим все схожие слова из структуры data по индексу data2[i]
        cout << "\n\n\x1b[31mНайденные данные на просьбу \"" << dis_new << "\":\x1b[0m\n";
        cout << "\x1b[36m";
        for (size_t i = 0; i < data2.size(); i++)
            cout << setw(10) << data[data2[i]].name << ' ' << data[data2[i]].hour << ' ' << data[data2[i]].sem << endl;
        cout << "\x1b[0m\n";

        // если слово для изменения одно. Спрашиваем пользователя новые данные и заносим:
        if (data2.size() == 1)
        {
            cout << "Введите новое название (или напишите \"не хочу\"): ";
            discipline = GetDataString();
            if (discipline != "не хочу" && discipline != "Не хочу")
                data[data2[0]].name = discipline;


            string newTime;
            cout << "Введите новое время (или напишите \"не хочу\"): ";
            newTime = GetDataStrinhgForInt();
            if (newTime != "не хочу" && newTime != "Не хочу")
                data[data2[0]].hour = stoi(newTime);


            string newSem;
            cout << "Введите новый семестр (или напишите \"не хочу\"): ";
            newSem = GetDataStrinhgForInt();
            if (newSem != "не хочу" && newSem != "Не хочу")
                data[data2[0]].sem = stoi(newSem);
        }

        // если слово не найдено
        else if (data2.size() == 0)
            cout << "\x1b[31mNot found\x1b[0m\n\n";

        // если их два и больше
        else
        {
            size_t hour, sem;
            int lol = 0;
            do
            {
                // ввод часов и семестра для нахождения нужной дисциплины
                cout << "Введите кол-во часов и семестр дисциплины строго существующие в таблице:\n"
                    << "Введите кол-во часов: ";
                hour = GetDataInt();
                cout << "Введите номер семестра: ";
                sem = GetDataInt();

                // ввод новых данных
                for (size_t i = 0; i < data2.size(); i++)
                {
                    if (data[data2[i]].hour == hour && data[data2[i]].sem == sem)
                    {
                        cout << "Введите новое название (или напишите \"не хочу\"): ";
                        discipline = GetDataString();
                        if (discipline != "не хочу" && discipline != "Не хочу")
                            data[data2[i]].name = discipline;


                        string newTime;
                        cout << "Введите новое время (или напишите \"не хочу\"): ";
                        newTime = GetDataStrinhgForInt();
                        if (newTime != "не хочу" && newTime != "Не хочу")
                            data[data2[i]].hour = stoi(newTime);


                        string newSem;
                        cout << "Введите новый семестр (или напишите \"не хочу\"): ";
                        newSem = GetDataStrinhgForInt();
                        if (newSem != "не хочу" && newSem != "Не хочу")
                            data[data2[i]].sem = stoi(newSem);
                        ++lol;
                    }

                }
                // пользователь ввёл несуществующие часы и семестр дисциплины. Спрашиваем занова
                if (lol == 0)
                    cout << "\n\x1b[31mВы ввели несуществующие данные. Повторите операцию!\x1b[0m\n\n";

            } while (lol == 0);

        }
        cout << endl;
        // продолжить измения дисциплин?
        cout << "Хотите продолжить? Отвечайте \"Продожить\" или \"нет\": ";
        GO = GetDataString();

    // пока "продолжить", продолжаем, иначе стоп
    } while (GO == "продолжить" || GO == "Продолжить");
    cout << endl;
}