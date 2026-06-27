#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include "Term.h"

template<class T>
class Polynomial
{
public:
	Polynomial();
	Polynomial(const size_t& size_t);
	Polynomial(const Term<T>& term);
	Polynomial(const Term<T>* termArr, const size_t& size);
	Polynomial(const Polynomial<T>& polynomial);
	~Polynomial();
	Term<T> operator[](size_t index) const;
	Term<T>& operator[](size_t index);
	Polynomial<T>& operator=(const Polynomial<T>& polynomial);
	Polynomial<T>& operator+=(const Polynomial<T>& polynomial);
	Polynomial<T>& operator*=(const Polynomial<T>& polynomial);
	template<class T1>
	friend std::ostream& operator<<(std::ostream& fin, const Polynomial<T1>& polynomial);
	size_t Size() const;
	void Order();

private:
	Term<T>* data__;
	size_t size__;
	size_t degree__;
};
template <class T>
Polynomial<T> operator*(const Polynomial<T>& polynom1, const Polynomial<T>& polynom2) {
	Polynomial<T> MultiplyPol(polynom1.Size() + polynom2.Size() - 1);
	for (size_t i = 0; i < polynom1.Size(); ++i) {
		for (size_t j = 0; j < polynom2.Size(); ++j) {
			MultiplyPol[i + j] += polynom1[i] * polynom2[j];
			MultiplyPol[i + j].SetDegree(polynom1[i].Degree() + polynom2[j].Degree());
		}
	}
	return MultiplyPol;
}
template <class T>
Polynomial<T> operator+(const Polynomial<T>& a, const Polynomial<T>& b) {
	size_t max;
	size_t min;
	if (a.Size() > b.Size()) {
		max = a.Size();
		min = b.Size();
	}
	else {
		max = b.Size();
		min = a.Size();
	}
	Polynomial<T> SumPolinom(max);
	size_t i = 0;
	size_t index_a;
	size_t index_b;
	if (a.Size() > b.Size()) {
		for (; i < max - min; ++i)
			SumPolinom[i] = a[i];
		index_a = i;
		index_b = 0;
	}
	else {
		for (; i < max - min; ++i)
			SumPolinom[i] = b[i];
		index_a = 0;
		index_b = i;
	}
	for (size_t j = 0; j < min; ++j) {
		SumPolinom[i] = a[index_a] + b[index_b];
			++index_a;
		++index_b;
		++i;
	}
	return SumPolinom;
}
template<class T>
Polynomial<T>::Polynomial() = default;
template<class T>
Polynomial<T>::Polynomial(const Polynomial<T>&polynomial)
	: size__(polynomial.size__), degree__(polynomial.degree__) {
	data__ = new Term<T>[size__];
	for (size_t i = 0; i < size__; ++i) {
		data__[size__ - polynomial.data__[i].degree__ - 1].coeff__ += polynomial.data__[i].coeff__;
		data__[size__ - polynomial.data__[i].degree__ - 1].degree__ = polynomial.data__[i].degree__;
	}
}
template<class T>
Polynomial<T>::Polynomial(const Term<T>&term)
	: degree__(term.degree__), size__(term.degree__ + 1) {
	data__ = new Term<T>[size__];
	data__[0].coeff__ += term.coeff__;
	data__[0].degree__ += term.degree__;
}
template<class T>
Polynomial<T>::Polynomial(const Term<T>*termArr, const size_t & size) {
	size_t max = termArr[0].degree__;
	for (size_t i = 1; i < size; ++i) {
		if (termArr[i].degree__ > max)
			max = termArr[i].degree__;
	}
	size__ = max + 1;
	degree__ = max;
	data__ = new Term<T>[size__];
	for (size_t i = 0; i < size; ++i) {
		size_t index = size__ - termArr[i].degree__ - 1;
		data__[index].coeff__ += termArr[i].coeff__;
		data__[index].degree__ = termArr[i].degree__;
	}
}
template<class T>
Polynomial<T>::Polynomial(const size_t & size) : size__(size), degree__(size - 1) {
	data__ = new Term<T>[size__];
	for (size_t i = 0; i < size__; ++i) {
		data__[i].coeff__ = 0;
		data__[i].degree__ = 0;
	}
}
template<class T>
Polynomial<T>::~Polynomial() {
	delete[] data__;
}
template<class T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>&polynomial) {
	if (this != &polynomial) {
		delete[] data__;
		size__ = polynomial.size__;
		degree__ = polynomial.degree__;
		data__ = new Term<T>[size__];
		for (size_t i = 0; i < size__; ++i)
			data__[i] = polynomial.data__[i];
	}
	return *this;
}
template<class T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>&polynomial) {
	*this = *this + polynomial;
	return *this;
}
template<class T>
Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>&polynomial) {
	*this = *this * polynomial;
	return *this;
}
template<class T>
inline size_t Polynomial<T>::Size() const {
	return size__;
}
template <class T1>
std::ostream& operator<<(std::ostream & fin, const Polynomial<T1>&polynomial) {
	for (size_t i = 0; i < polynomial.size__; ++i) {
		if (i == 0) {
			if (polynomial[i].Coeff() != 0) {
				fin << polynomial[i];
			}
			else if (polynomial[i].Coeff() == 0 && i != polynomial.size__ - 1) {
				while (polynomial[i].Coeff() == 0 && i != polynomial.size__ - 1)
					++i;
				if (polynomial[i].Coeff() == 0)
					break;
				fin << polynomial[i];
			}
			else {
				fin << polynomial[i];
			}
		}
		else {
			if (polynomial[i].Coeff() > 0) {
				fin << " + " << polynomial[i];
			}
			else if (polynomial[i].Coeff() < 0) {
				fin << " + (" << polynomial[i] << ')';
				//fin << polynomial[i];
			}
		}

	}
	return fin;
}
template<class T>
inline Term<T> Polynomial<T>::operator[](size_t index) const {
	return data__[index];
}
template<class T>
inline Term<T>& Polynomial<T>::operator[](size_t index) {
	return data__[index];
}
template<class T>
void Polynomial<T>::Order() {
	size_t j = size__ - 1;
	for (size_t i = 0; i < size__ / 2; ++i) {
		std::swap(data__[i], data__[j]);
		--j;
	}
}
