// Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>
#include "Header.h"
#define SIZE 150
String::String() {
    Data = new char[SIZE];
    Data[0] = '\0';
}
String::~String() { delete[] Data; }
String::String(const String& rhs) {
    Data = new char[strlen(rhs.Data) + 1];
    std::snprintf(Data, strlen(rhs.Data) + 1, "%s", rhs.Data);
}
String::String(const char* data) {
    Data = new char[strlen(data) + 1];
    std::snprintf(Data, strlen(data) + 1, "%s", data);
}
size_t String::Size() const { return strlen(Data); }
size_t String::Find(const String& substr) const {
    size_t i = 0, count = 0, index;
    do {
        for (index = 0; index < strlen(substr.Data); index++) {
            if (Data[i] == substr[index]) {
                ++i;
                ++count;
            }
            else {
                break;
            }
        }
        if (strlen(substr.Data) == count) {
            return i - strlen(substr.Data);
        }
        count = 0;
        ++i;
        i -= index;
    } while (i != strlen(Data));
    return -1;
}
size_t String::Find(const char* substr) const {
    size_t i = 0, count = 0, index;
    do {
        for (index = 0; index < strlen(substr); index++) {
            if (Data[i] == substr[index]) {
                ++i;
                ++count;
            }
            else {
                break;
            }
        }
        if (strlen(substr) == count) {
            return i - strlen(substr);
        }
        count = 0;
        ++i;
        i -= index;
    } while (i != strlen(Data));
    return -1;
}
bool String::Empty() const { return strlen(Data) == 0; }
void String::swap(String& oth) {
    char* Data_new = oth.Data;
    oth.Data = Data;
    Data = Data_new;
}
void String::RTrim(char symbol) {
    char* new_data = new char[strlen(Data) + 2];
    size_t index = strlen(Data) - 1, j = 0;
    while (index > 0) {
        if (Data[index] == symbol) {
            --index;
            continue;
        }
        else {
            break;
        }
    }
    for (size_t i = 0; i <= index; i++) new_data[j++] = Data[i];
    new_data[j] = '\0';
    std::snprintf(Data, strlen(new_data) + 1, "%s", new_data);
    delete[] new_data;
}
void String::LTrim(char symbol) {
    char* new_data = new char[strlen(Data) + 2];
    size_t index = 0, j = 0;
    while (index < strlen(Data)) {
        if (Data[index] == symbol) {
            ++index;
            continue;
        }
        else {
            break;
        }
    }
    for (size_t i = index; i < strlen(Data); i++) new_data[j++] = Data[i];
    new_data[j] = '\0';
    std::snprintf(Data, strlen(new_data) + 1, "%s", new_data);
    delete[] new_data;
}
void String::Replace(char oldSymbol, char newSymbol) {
    for (size_t i = 0; i < strlen(Data); i++) {
        if (Data[i] == oldSymbol) Data[i] = newSymbol;
    }
}
char String::operator[](size_t index) const { return Data[index]; }
char& String::operator[](size_t index) { return Data[index]; }
bool String::operator<(const String& rhs) const {
    return strcmp(Data, rhs.Data) < 0;
}
bool String::operator==(const String& rhs) const {
    return strcmp(Data, rhs.Data) == 0;
}
bool String::operator==(const char* rhs) const {
    return strcmp(Data, rhs) == 0;
}
bool operator==(const char* str1, const String& rhs) { return rhs == str1; }
bool operator!=(const String& a, const String& b) { return !(a == b); }
bool operator!=(const String& a, const char* b) { return !(b == a); }
bool operator!=(const char* str1, const String& rhs) { return !(str1 == rhs); }
bool operator>(const String& a, const String& b) { return !(a < b); }
String& String::operator=(const String& rhs) {
    if (&rhs != this) {
        delete[] Data;
        Data = new char[strlen(rhs.Data) + 1];
        std::snprintf(Data, strlen(rhs.Data) + 1, "%s", rhs.Data);
    }
    return *this;
}
String operator*(const String& a, unsigned int b) {
    String MultiStr;
    if (b == 0) {
        MultiStr[0] = '\0';
        return MultiStr;
    }
    size_t count = 0, index = 0;
    while (count != b) {
        for (size_t i = 0; i < a.Size(); i++) MultiStr[index++] = a[i];
        ++count;
    }
    MultiStr[index] = '\0';
    return MultiStr;
}
String operator+(const String& a, const String& b) {
    String sumStr;
    sumStr[0] = '\0';
    size_t i = 0;
    for (; i < a.Size(); i++) sumStr[i] = a[i];
    for (size_t j = 0; j < b.Size(); j++) sumStr[i++] = b[j];
    sumStr[i] = '\0';
    return sumStr;
}
String operator+(const String& a, const char* b) {
    String sumStr;
    sumStr[0] = '\0';
    size_t i = 0;
    for (; i < a.Size(); i++) sumStr[i] = a[i];
    for (size_t j = 0; j < strlen(b); j++) sumStr[i++] = b[j];
    sumStr[i] = '\0';
    return sumStr;
}
String& String::operator+=(const String& rhs) {
    *this = *this + rhs;
    return *this;
}
String& String::operator+=(const char* rhs) {
    *this = *this + rhs;
    return *this;
}
String& String::operator*=(unsigned int m) {
    *this = *this * (m + 1);
    return *this;
}
std::ostream& operator<<(std::ostream& out, const String& str) {
    out << str.Data;
    return out;
}
