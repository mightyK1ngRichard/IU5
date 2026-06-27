#include "Header.h"

void Read(vector<dis> &data) {
    // ���� ���� �� ������, ������ ���
    ifstream f("data.txt");
    if (!f) {
        ofstream("data.txt");
        return;
    }

    while (!f.eof()) {
        dis data2;
        // ��������� ��� ������ �� �����
        string help;
        getline(f, help);

        // ���� ���� ������, ����
        if (help.length() == 0)
            return;

        size_t i2 = 0;
        size_t n = 0;

        // ����� �� ��������� ������ � �������� ������ ����� �� "|"
        for (size_t i = 0; i < help.length(); i++) {
            // ���������� �������
            if (help[i] == ' ')
                continue;

            // ���� ��������� '|' ������ ��� ����� ������� � ������� � ���������
            if (help[i] != '|') {
                // ���� ���� ��� �����, ��������� �� �������� 
                ++n;
                if (i != 0 && n > 1) {
                    if (help[i - 1] == ' ')
                        data2.name += ' ';
                }
                // ������� � ���������
                data2.name += help[i];
            }

                // ���� ���-�� ����
            else {
                i2 = ++i;
                break;
            }
        }

        // ��������� ����� �� string � ��������� ��� �����
        string num = "";
        for (size_t i = i2; i < help.length(); i++) {
            if (help[i] != '|') {
                if (help[i] == ' ')
                    continue;
                else
                    num += help[i];
            } else {
                i2 = ++i;
                break;
            }
        }
        data2.hour = stoi(num);

        // ��������� ����� �� string � ��������� ��� ��������
        num = "";
        for (size_t i = i2; i < help.length(); i++) {
            if (help[i] != '|') {
                if (help[i] == ' ')
                    continue;
                else
                    num += help[i];
            } else {
                i2 = ++i;
                break;
            }
        }
        data2.sem = stoi(num);

        // ������� � ���������
        data.push_back(data2);
    }

}

void Add(vector<dis> &data) {
    string GO = "";
    do {

        string discipline;
        size_t hour;
        size_t sem;
        dis data2;
        cout << "\n������� �������� ����������: ";
        // ���� ������ ����� � ��������� 
        discipline = GetDataString();

        // ��������, ����� ����� ����� ��� ������ ��������
        int n = 0; // �������� ������� �� �������� ���� � ������
        for (size_t i = 0; i < discipline.length(); i++) {
            if (discipline[i] == ' ')
                continue;

            if (discipline[i] != '|') {
                ++n;
                if (i != 0 && n > 1) {
                    if (discipline[i - 1] == ' ')
                        data2.name += ' ';
                }
                data2.name += discipline[i];
            } else
                break;
        }

        // �������� �� ������� ����� � ���������
        bool creat = false;
        for (size_t i = 0; i < data.size(); i++) {
            if (data2.name == data[i].name)
                creat = true;
        }


        // ���� ����� ����������, ���������� ������������ �������� �� � ������ ������ ���� "��"
        if (creat) {
            cout << "\x1b[31m������ ���������� ��� ����������!\x1b[0m\n"
                 << "�� �������, ��� ������ �������� \"" << data2.name << "\"? �������� \" ��\" ��� \" ���\": ";
            string contin = GetDataString();
            if (contin == "��" || contin == "��") {
                cout << "������� ���-�� �����: ";
                hour = GetDataInt();
                cout << "������� ����� ��������: ";
                sem = GetDataInt();

                data2.hour = hour;
                data2.sem = sem;

                cout << "�� �����: ";
                cout << "\x1b[31m"
                     << data2.name << ' ' << data2.hour << ' ' << data2.sem
                     << "\x1b[0m";

                cout << "\n������� � ���� ������? (������� \"��\" ��� \"���\"): ";
                string question = GetDataString();

                if (question == "��" || question == "��")
                    data.push_back(data2);
                cout << endl << endl;
            }
        }

            // ���� �� ����������, ������ ������ ������ �� ������� � ������ ��������
        else {
            cout << "������� ���-�� �����: ";
            hour = GetDataInt();
            cout << "������� ����� ��������: ";
            sem = GetDataInt();

            data2.hour = hour;
            data2.sem = sem;

            cout << "�� �����: ";
            cout << "\x1b[31m"
                 << data2.name << ' ' << data2.hour << ' ' << data2.sem
                 << "\x1b[0m";

            cout << "\n������� � ���� ������? (������� \"��\" ��� \"���\"): ";
            string question = GetDataString();

            if (question == "��" || question == "��")
                data.push_back(data2);
            cout << endl << endl;
        }

        // ���������� ������������, ����� �� ���������
        cout << "������ ����������? ��������� \"���������\" ��� \"���\": ";
        GO = GetDataString();

    } while (GO == "����������" || GO == "����������");
    cout << endl;

}

void Sort(vector<dis> &data) {
    // ���������� �� ��������
    for (size_t i = 1; i < data.size(); i++) {
        for (size_t i2 = 0; i2 < data.size() - i; i2++) {
            if (data[i2].name > data[i2 + 1].name) {
                swap(data[i2].name, data[i2 + 1].name);
                swap(data[i2].hour, data[i2 + 1].hour);
                swap(data[i2].sem, data[i2 + 1].sem);
            }
        }
    }
}

void Delete(vector<dis> &data) {
    // ���� ���� ������, ����
    if (data.size() == 0) {
        cout << "���� ������!\n";
        return;
    }

    Sort(data);
    bool flag = false;
    string discipline;

    // ������ ���������� ��� ��������. �������� �� ����
    cout << "\n������� ���������� ��� ��������: ";
    discipline = GetDataString();


    // ������� ��������� �������� �������� �������������
    string dis_new = "";
    int n = 0;
    for (size_t i = 0; i < discipline.length(); i++) {
        if (discipline[i] == ' ')
            continue;

        ++n;
        if (i != 0 && n > 1) {
            if (discipline[i - 1] == ' ')
                dis_new += ' ';
        }
        dis_new += discipline[i];

    }

    // ������ ������ ��� �������� �������� ����, ������� ����� � �������� ��� ��������
    vector<size_t> data2;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].name == dis_new)
            data2.push_back(i);
    }


    // ������� ��� ������ ����� �� ��������� data �� ������� data2[i]. 
    cout << "\n\n\x1b[31m��������� ������ �� ������� \"" << dis_new << "\":\x1b[0m\n";
    cout << "\x1b[36m";
    for (size_t i = 0; i < data2.size(); i++)
        cout << setw(10) << data[data2[i]].name << ' ' << data[data2[i]].hour << ' ' << data[data2[i]].sem << endl;
    cout << "\x1b[0m\n";


    // ���� ����� ��� �������� ����. �������
    if (data2.size() == 1)
        data.erase(data.begin() + data2[0]);

        // ���� ��������� ����� ��� ����������
    else if (data2.size() == 0)
        cout << "\x1b[31mNot found\x1b[0m\n\n";

        // ���� �������� ��� � ����� �����. ����� ������� ������������
    else {
        // ������������ �������� �������� ���������� �� ����� � ��������
        // ���������� ������������, ���� �� �� ����� ������������ ������
        size_t hour, sem;
        int lol = 0;
        do {
            cout << "������� ���-�� ����� � ������� ���������� ��� ��������:\n"
                 << "������� ���-�� �����: ";
            hour = GetDataInt();
            cout << "������� ����� ��������: ";
            sem = GetDataInt();

            for (size_t i = 0; i < data2.size(); i++) {
                if (data[data2[i]].hour == hour && data[data2[i]].sem == sem) {
                    data.erase(data.begin() + data2[i]);
                    ++lol;
                }
            }
            if (lol == 0)
                cout << "\n\x1b[31m�� ����� �������������� ������. ��������� ��������!\x1b[0m\n\n";

        } while (lol == 0);
    }
    cout << endl;
}

void FillFile(vector<dis> &data) {
    // ������� ������ � ���� � ���� �������
    size_t NUM = FindMax(data);
    ofstream fin("data.txt");
    Sort(data);
    for (size_t i = 0; i < data.size(); ++i) {
        if (i != data.size() - 1)
            fin << data[i].name << setw(NUM - data[i].name.length()) << " | "
                << setw(10) << data[i].hour << setw(10) << " | " << setw(10) << data[i].sem << endl;
        else
            fin << data[i].name << setw(NUM - data[i].name.length()) << " | "
                << setw(10) << data[i].hour << setw(10) << " | " << setw(10) << data[i].sem;
    }
    cout << endl;
}

void Print(vector<dis> &data) {
    // ���� ���� ������, ����
    if (data.size() == 0) {
        cout << "\x1b[31m\n���� ������!\x1b[0m\n\n";
        return;
    }

    Sort(data);
    size_t NUM = FindMax(data);
    // �����
    cout << "\x1b[31m" << "     ����������" << setw(NUM - 16) << '|' << setw(10)
         << "   ���-�� �����" << setw(5) << '|' << setw(10) << "    ����� ��������\x1b[0m\n";
    cout << "\x1b[36m";

    // �������
    for (size_t i = 0; i < data.size(); i++) {
        if (i != data.size() - 1)
            cout << data[i].name << setw(NUM - data[i].name.length()) << " | " << setw(10)
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

size_t FindMax(vector<dis> &data) {
    // ��� ������� ���� ����� ������� ������ ��� �������� �������
    size_t max = data[0].name.length();
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].name.length() > max)
            max = data[i].name.length();
    }
    if (max + 5 > 15)
        return max + 5;
    else
        return 22;
}

size_t Menu() {
    size_t report;
    cout << "*-*-*-*-*-* ���� *-*-*-*-*-*\n";
    cout << "1. �������� ����������\n"
         << "2. ������� ����������\n"
         << "3. ������������� ������\n"
         << "4. �������� � ����\n"
         << "5. ������\n"
         << "6. ����� ����������\n"
         << "7. �����\n";
    cout << "�������� �����: ";
    report = GetDataInt();
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    if (report > 0 && report <= 8)
        return report;

}

size_t GetDataInt() {
    // ��������� �������� ������
    while (true) {
        size_t a;
        cout << "\x1b[35m";
        cin >> a;
        cout << "\x1b[0m";
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\x1b[31m��������� �������� ������: \x1b[0m";
        } else {
            cin.ignore(32767, '\n');
            return a;
        }
    }
}

string GetDataString() {
    // ��������� �������� ������
    string name = "";
    cout << "\x1b[35m";
    getline(cin, name);
    cout << "\x1b[0m";

    while (!ControlName(name)) {
        cout << "\x1b[31m������ �� ����� ���� ������, ��������� ����� ��� \"|\", ���������� ����� : \x1b[0m\n";
        cout << "�������: ";
        cout << "\x1b[35m";
        getline(cin, name);
        cout << "\x1b[0m";
    }
    return name;
}

string GetDataStrinhgForInt() {
    // ��������� �������� ������
    string name = "";

    cout << "\x1b[35m";
    getline(cin, name);
    cout << "\x1b[0m";

    while (!ControlStrinhgForInt(name)) {
        cout << "\x1b[31m����� ���������! ���������� �����: \x1b[0m\n";
        cout << "�������: ";
        cout << "\x1b[35m";
        getline(cin, name);
        cout << "\x1b[0m";
    }
    return name;
}

bool ControlStrinhgForInt(string name) {
    // ��������� �������� ������

    if (name == "�� ����" || name == "�� ����")
        return true;

    if (name.length() == 0)
        return false;

    for (size_t i = 0; i < name.length(); i++) {
        if (name[i] >= '0' && name[i] <= '9')
            continue;
        else
            return false;
    }
}

bool ControlName(string name) {
    // ��������� �������� ������
    if (name.length() == 0)
        return false;

    for (size_t i = 0; i < name.length(); i++)
        if (name[i] >= '0' && name[i] <= '9' || name[i] == '|')
            return false;

    return true;
}

void FindData(vector<dis> &data) {
    cout << "������� ���������� ��� ������: ";
    string discipline = GetDataString();
    // ������� ��������� �������� �������� �������������
    string dis_new = "";
    int n = 0;
    for (size_t i = 0; i < discipline.length(); i++) {
        if (discipline[i] == ' ')
            continue;

        ++n;
        if (i != 0 && n > 1) {
            if (discipline[i - 1] == ' ')
                dis_new += ' ';
        }
        dis_new += discipline[i];

    }

    // ���������� ������������ ��� ��������� ������ �� ��� �������
    size_t k = 0;
    cout << "\x1b[31m���������� ������ �� ������� \"" << dis_new << "\":\x1b[0m\n";
    cout << "\x1b[36m";
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].name == dis_new) {
            cout << setw(10) << data[i].name << ' ' << data[i].hour << ' ' << data[i].sem << ' ' << endl;
            ++k;
        }
    }
    cout << "\x1b[0m\n\n";

    // ���� ���� ����� ���, �����:
    if (k == 0)
        cout << "\x1b[31mNot found\x1b[0m\n\n";
}

void Edit(vector<dis> &data) {
    // ���� ���� ������, ����
    if (data.size() == 0) {
        cout << "���� ������!\n";
        return;
    }

    string GO = "";
    do {
        string dis_new = "";
        cout << "����� ���������� �� ������ ��������? ";
        dis_new = GetDataString();

        // ������� ��������� �������� �������� �������������
        string discipline = "";
        int n = 0;
        for (size_t i = 0; i < dis_new.length(); i++) {
            if (dis_new[i] == ' ')
                continue;

            ++n;
            if (i != 0 && n > 1) {
                if (dis_new[i - 1] == ' ')
                    discipline += ' ';
            }
            discipline += dis_new[i];

        }

        // ������� �������� ������ ���� � ������
        vector<size_t> data2;
        for (size_t i = 0; i < data.size(); i++) {
            if (data[i].name == dis_new)
                data2.push_back(i);
        }

        // ������� ��� ������ ����� �� ��������� data �� ������� data2[i]
        cout << "\n\n\x1b[31m��������� ������ �� ������� \"" << dis_new << "\":\x1b[0m\n";
        cout << "\x1b[36m";
        for (size_t i = 0; i < data2.size(); i++)
            cout << setw(10) << data[data2[i]].name << ' ' << data[data2[i]].hour << ' ' << data[data2[i]].sem << endl;
        cout << "\x1b[0m\n";

        // ���� ����� ��� ��������� ����. ���������� ������������ ����� ������ � �������:
        if (data2.size() == 1) {
            cout << "������� ����� �������� (��� �������� \"�� ����\"): ";
            discipline = GetDataString();
            if (discipline != "�� ����" && discipline != "�� ����")
                data[data2[0]].name = discipline;


            string newTime;
            cout << "������� ����� ����� (��� �������� \"�� ����\"): ";
            newTime = GetDataStrinhgForInt();
            if (newTime != "�� ����" && newTime != "�� ����")
                data[data2[0]].hour = stoi(newTime);


            string newSem;
            cout << "������� ����� ������� (��� �������� \"�� ����\"): ";
            newSem = GetDataStrinhgForInt();
            if (newSem != "�� ����" && newSem != "�� ����")
                data[data2[0]].sem = stoi(newSem);
        }

            // ���� ����� �� �������
        else if (data2.size() == 0)
            cout << "\x1b[31mNot found\x1b[0m\n\n";

            // ���� �� ��� � ������
        else {
            size_t hour, sem;
            int lol = 0;
            do {
                // ���� ����� � �������� ��� ���������� ������ ����������
                cout << "������� ���-�� ����� � ������� ���������� ������ ������������ � �������:\n"
                     << "������� ���-�� �����: ";
                hour = GetDataInt();
                cout << "������� ����� ��������: ";
                sem = GetDataInt();

                // ���� ����� ������
                for (size_t i = 0; i < data2.size(); i++) {
                    if (data[data2[i]].hour == hour && data[data2[i]].sem == sem) {
                        cout << "������� ����� �������� (��� �������� \"�� ����\"): ";
                        discipline = GetDataString();
                        if (discipline != "�� ����" && discipline != "�� ����")
                            data[data2[i]].name = discipline;


                        string newTime;
                        cout << "������� ����� ����� (��� �������� \"�� ����\"): ";
                        newTime = GetDataStrinhgForInt();
                        if (newTime != "�� ����" && newTime != "�� ����")
                            data[data2[i]].hour = stoi(newTime);


                        string newSem;
                        cout << "������� ����� ������� (��� �������� \"�� ����\"): ";
                        newSem = GetDataStrinhgForInt();
                        if (newSem != "�� ����" && newSem != "�� ����")
                            data[data2[i]].sem = stoi(newSem);
                        ++lol;
                    }

                }
                // ������������ ��� �������������� ���� � ������� ����������. ���������� ������
                if (lol == 0)
                    cout << "\n\x1b[31m�� ����� �������������� ������. ��������� ��������!\x1b[0m\n\n";

            } while (lol == 0);

        }
        cout << endl;
        // ���������� ������� ���������?
        cout << "������ ����������? ��������� \"���������\" ��� \"���\": ";
        GO = GetDataString();

        // ���� "����������", ����������, ����� ����
    } while (GO == "����������" || GO == "����������");
    cout << endl;
}