// Copyright 2022 Dmitriy <dimapermyakov55@gmail.com>

#pragma once
#include <iostream>
#include <string.h>
#include <iomanip>
class String {
public:
	~String();
	String();
	String(const String& rhs);
	String(const char* data);
	size_t Find(const String& substr) const;
	size_t Find(const char* substr) const;
	void Replace(char oldSymbol, char newSymbol);
	size_t Size() const;
	bool Empty() const;
	void RTrim(char symbol);
	void LTrim(char symbol);
	void swap(String& oth);
	String& operator=(const String& rhs);
	String& operator+=(const String& rhs);
	String& operator+=(const char* rhs);
	String& operator*=(unsigned int m);
	bool operator==(const String& rhs) const;
	bool operator==(const char* rhs) const;
	bool operator<(const String& rhs) const;
	char operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::ostream& operator<<(std::ostream&, const String&);
private:
	char* Data{};
};
String operator+(const String& a, const String& b);
String operator+(const String& a, const char* b);
String operator*(const String& a, unsigned int b);
bool operator!=(const String& a, const String& b);
bool operator!=(const String& a, const char* b);
bool operator>(const String& a, const String& b);
std::ostream& operator<<(std::ostream& out, const String& str);
bool operator==(const char* str1, const String& rhs);
//------------------------Vector----------------------------------
const int MAX_SIZE = 5;
template <class T>
class Vector
{
public:
	Vector();
	Vector(const Vector& v);
	~Vector();
	void Push_back(T el);
	void Remove(int i);
	void Sort();
	int Size();
	int Maxsize();
	size_t Find(T el);
	T operator[](size_t i);
	Vector& operator=(Vector& v);
	template <class T1>
	friend std::ostream& operator<<(std::ostream& out, Vector<T1>& v);
protected:
	int maxsize;
	int size;
	T* data;
	void resize();
private:
	//void resize();
};
template <class T>
void Vector<T>::resize() {
	maxsize = static_cast<int>(size * 1.5);
	T* help = new T[size];
	for (size_t i = 0; i < size; i++)
		help[i] = data[i];
	data = new T[maxsize];
	for (size_t i = 0; i < size; i++)
		data[i] = help[i];
	delete[] help;
}
template <class T>
Vector<T>::Vector() {
	maxsize = MAX_SIZE;
	size = 0;
	data = new T[MAX_SIZE];
}
template <class T>
Vector<T>::Vector(const Vector& v) {
	data = new T[v.size];
	for (size_t i = 0; i < v.size; i++) {
		data[i] = v.data[i];
		++size;
	}
	maxsize = size + MAX_SIZE;
}
template <class T>
Vector<T>::~Vector() {
	delete[] data;
}
template <class T>
void Vector<T>::Push_back(T el) {
	if (size >= maxsize)
		resize();
	data[unsigned(size)] = el;
	++size;
}
template <class T>
int Vector<T>::Size() {
	return size;
}
template <class T>
int Vector<T>::Maxsize() {
	return maxsize;
}
template <class T1>
std::ostream& operator<<(std::ostream& out, Vector<T1>& v) {

	for (size_t i = 0; i < v.size; i++)
		out << "| " << v.data[i] << '\n';

	out << "\nSize: " << v.size << std::endl << "MaxSize: " << v.maxsize;
	return out;
}
template <class T>
void Vector<T>::Remove(int i) {
	for (size_t index = i; index < size - 1; index++)
		data[index] = data[index + 1];
	--size;
	if (size < (maxsize / 2) && maxsize / 1, 5 > MAX_SIZE)
		resize();
}
template <class T>
void Vector<T>::Sort() {
	for (size_t i = 1; i < size; i++) {
		for (size_t j = 0; j < size - i; j++) {
			if (data[j] > data[j + 1])
				std::swap(data[j], data[j + 1]);
		}
	}
}
template <class T>
size_t Vector<T>::Find(T el) {
	for (size_t i = 0; i < size; i++) {
		if (data[i] == el)
			return i;
	}
	std::cout << " ! NOT FOUND !\n";
	return -1;
}
template <class T>
T Vector<T>::operator[](size_t i) {
	return data[i];
}
template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>& v) {
	if (&v != this) {
		delete[] data;
		data = new T[v.size];
		for (size_t i = 0; i < v.size; i++)
			data[i] = v.data[i];
	}
	return *this;
}
//-------------------------------SET-----------------------------------------
template <class T>
class Set : public Vector<T> {
public:
	Set() = default;
	Set(int size) : Vector<T>(size) {};
	Set(String el, int size = MAX_SIZE) : Vector<String>(el, size) {};
	template<class T1>
	friend std::ostream& operator<<(std::ostream& out, Set<T1>& s);
	template<class T1>
	friend Set<T1> operator+(Set<T1>& s1, Set<T1>& s2);
	template<class T1>
	friend Set<T1> operator-(Set<T1>& s1, Set<T1>& s2);
	template<class T1>
	friend Set<T1> operator*(Set<T1>& s1, Set<T1>& s2);
	bool operator==(Set& s);
	Set<T>& operator+=(Set& s);
	Set<T>& operator-=(Set& s);
	Set<T>& operator*=(Set& s);
	void Add(T el);
	void Delete(T el);
	bool is_element(T el);
	int Find_Set(const T& el);
};
template <class T>
bool Set<T>::is_element(T el) {
	return Find_Set(el) != -1;
}
template <class T>
Set<T>& Set<T>::operator-=(Set& s) {
	*this = *this - s;
	return *this;
}
template <class T1>
Set<T1> operator-(Set<T1>& s1, Set<T1>& s2) {
	Set<T1> Subtraction;
	for (size_t i = 0; i < s1.size; ++i) {
		bool element_is_here = false;
		for (size_t j = 0; j < s2.size; ++j) {
			if (s1.data[i] == s2.data[j]) {
				element_is_here = true;
				break;
			}
		}
		if (!element_is_here)
			Subtraction.Add(s1.data[i]);
	}
	return Subtraction;
}
template <class T>
void Set<T>::Add(T el) {
	if (Vector<T>::size >= Vector<T>::maxsize)
		Vector<T>::resize();

	Vector<T>::data[Vector<T>::size] = el;
	++Vector<T>::size;
	Vector<T>::Sort();
}
template <class T>
void Set<T>::Delete(T el) {
	int i = Find(el);
	for (size_t index = static_cast<size_t>(i); index < Vector<T>::size - 1; index++)
		Vector<T>::data[index] = Vector<T>::data[index + 1];
	--Vector<T>::size;
}
template<class T1>
std::ostream& operator<<(std::ostream& out, Set<T1>& s) {
	for (size_t i = 0; i < s.size; i++)
		out << "| " << s.data[i] << std::endl;
	return out;
}
template <class T>
Set<T>& Set<T>::operator+=(Set& s) {
	*this = *this + s;
	return *this;
}
template<class T1>
Set<T1> operator+(Set<T1>& s1, Set<T1>& s2) {
	Set<T1> SumSet;
	for (size_t i = 0; i < s1.size; ++i)
		SumSet.Add(s1.data[i]);

	for (size_t i = 0; i < s2.size; ++i) {
		bool element_is_here = false;
		for (size_t j = 0; j < SumSet.size; ++j) {
			if (s2.data[i] == SumSet.data[j]) {
				element_is_here = true;
				break;
			}
		}
		if (!element_is_here)
			SumSet.Add(s2.data[i]);
	}
	return SumSet;
}
template <class T>
Set<T>& Set<T>::operator*=(Set& s) {
	*this = *this * s;
	return *this;
}
template<class T1>
Set<T1> operator*(Set<T1>& s1, Set<T1>& s2) {
	Set<T1> MultiSet;
	for (size_t i = 0; i < s1.size; ++i) {
		for (size_t j = i; j < s2.size; ++j) {
			if (s1.data[i] == s2.data[j]) {
				MultiSet.Add(s1.data[i]);
				break;
			}
		}
	}
	return MultiSet;
}
template<class T>
int Set<T>::Find_Set(const T& el) {
	Vector<T>::Sort();
	bool flag = false;
	size_t l = 0;
	size_t r = Vector<T>::size;
	size_t middle;
	while (l <= r) {
		middle = (l + r) / 2;
		if (Vector<T>::data[middle] == el) {
			flag = true;
			break;
		}
		if (Vector<T>::data[middle] > el)
			r = middle - 1;
		else
			l = middle + 1;
	}
	if (flag) {
		return middle;
	}
	else {
		std::cout << "  ! NOT FOUND !\n";
		return -1;
	}
}
template<class T>
bool Set<T>::operator==(Set& s) {
	if (Vector<T>::size != s.size)
		return false;
	for (size_t i = 0; i < Vector<T>::size; ++i) {
		if (Vector<T>::data[i] == s.data[i])
			continue;
		else return false;
	}
	return true;
}