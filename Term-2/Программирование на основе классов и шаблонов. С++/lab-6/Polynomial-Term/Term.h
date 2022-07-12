#pragma once

template<class T>
class Polynomial;

template<class T>
class Term {
public:
	Term();
	Term(const int& coeff);
	Term(const int& coeff, const size_t& degree);
	~Term();
	Term<T>& operator=(const Term<T>& term);
	Term<T>& operator+=(const Term<T>& term);
	template<class T1>
	friend std::istream& operator>>(std::istream& out, Term<T1>& term);
	template<class T1>
	friend std::ostream& operator<<(std::ostream& out, const Term<T1>& term);
	void SetDegree(const size_t& degree);
	void SetCoeff(const int& coeff);
	size_t Degree() const;
	int Coeff() const;
	friend Polynomial<T>;

private:
	int coeff__;
	size_t degree__;
};
template<class T>
Term<T>::Term(const int& coeff, const size_t& degree) : coeff__(coeff), degree__(degree) {}
template<class T>
Term<T>::Term(const int& coeff) : coeff__(coeff), degree__(0) {}
template<class T>
Term<T>::~Term() = default;
template<class T>
Term<T>& Term<T>::operator = (const Term<T>&term) {
	if (this != &term) {
		coeff__ = term.coeff__;
		degree__ = term.degree__;
	}
	return *this;
}
template<class T>
Term<T>& Term<T>::operator+=(const Term<T>&term) {
	*this = *this + term;
	return *this;
}
template<class T>
Term<T>::Term() : coeff__(0), degree__(0) {}
template<class T>
inline void Term<T>::SetCoeff(const int& coeff) {
	coeff__ = coeff;
}
template<class T>
inline void Term<T>::SetDegree(const size_t & degree) {
	degree__ = degree;
}
template<class T>
inline size_t Term<T>::Degree() const {
	return degree__;
}
template<class T>
inline int Term<T>::Coeff() const {
	return coeff__;
}
template<class T>
Term<T> operator+(const Term<T>&term1, const Term<T>&term2) {
	if (term1.Degree() == term2.Degree()) {
		Term<T> SumTerm(term1.Coeff() + term2.Coeff(), term1.Degree());
		return SumTerm;
	}
	else if (term1.Coeff() == 0 || term2.Coeff() == 0) {
		if (term1.Degree() > term2.Degree()) {
			Term<T> SumTerm(term1.Coeff() + term2.Coeff(), term1.Degree());
			return SumTerm;
		}
		else {
			Term<T> SumTerm(term1.Coeff() + term2.Coeff(), term2.Degree());
			return SumTerm;
		}
	}
	else {
		Term<T> SumTerm;
		return SumTerm;
	}
}
template<class T>
Term<T> operator*(const Term<T>&term1, const Term<T>&term2) {
	Term<T> Multiply(term1.Coeff() * term2.Coeff(), term1.Degree() + term2.Degree());
	return Multiply;
}
template<class T1>
std::ostream& operator<<(std::ostream & out, const Term<T1>&term) {
	if (term.coeff__ == 1 && term.degree__ != 0 && term.degree__ != 1) {
		out << "x^" << term.degree__;
	}
	else if (term.coeff__ == -1 && term.degree__ != 0 && term.degree__ != 1) {
		out << "-x^" << term.degree__;
	}
	else if ((term.coeff__ != 1 || term.coeff__ != -1) && term.degree__ == 0) {
		out << term.coeff__;
	}
	else if (term.coeff__ == 1 && term.degree__ == 1) {
		out << "x";
	}
	else if (term.coeff__ == -1 && term.degree__ == 1) {
		out << "-x";
	}
	else if ((term.coeff__ != 1 || term.coeff__ != -1) && term.degree__ == 1) {
		out << term.coeff__ << "x";
	}
	else if (term.coeff__ == 0) {
		out << 0;
	}
	else {
		out << term.coeff__ << "x^" << term.degree__;
	}
	return out;
}
template<class T1>
std::istream& operator>>(std::istream & fin, Term<T1>&term) {
	char* data = new char[100];
	T1* polynom = new T1[100];
	std::cin.getline(data, 100);
	for (size_t i = 0; i < 100; ++i)
		polynom[i] = 0;
	size_t sizePolynom = 1;
	int coef = -1;
	// поиск макс степени
	char* pow = new char[10];
	size_t powIndex = 0;
	for (size_t i = 0; i < strlen(data); ++i) {
		if (data[i] == '^') {
			++i;
			while (data[i] == ' ')
				++i;

			while (data[i] >= '1' && data[i] <= '9') {
				pow[powIndex] = data[i];
				++powIndex;
				++i;
			}
			pow[powIndex] = '\0';
			if (std::atoi(pow) + 1 > sizePolynom)
				sizePolynom = std::atoi(pow) + 1;
			powIndex = 0;
		}
	}
	if (sizePolynom == 1) {
		for (size_t i = 0; i < strlen(data); ++i) {
			if (data[i] == 'x') {
				sizePolynom = 2;
				break;
			}
		}
	}
	delete[] pow;
	for (size_t i = 0; i < strlen(data); ++i) {
		// скипает вайпспайс
		if (data[i] == ' ') {
			continue;
		}

		else if (data[i] == 'x') {
			size_t k = 0;
			char* help = new char[10];
			++i;
			// вычисл€ем степень при 'x'
			for (; i < strlen(data); ++i) {
				if (data[i] == ' ' || data[i] == '^') {
					if (k != 0) {
						break;
					}
					continue;
				}
				// если после '^' эти знаки, значит нету коэф => 1
				else if ((data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/') && k == 0) {
					help[k] = '1';
					++k;
					--i;
					break;
				}
				else if (data[i] >= '0' && data[i] <= '9') {
					help[k] = data[i];
					++k;
				}
				else {
					break;
				}
			}

			// пока сам не понимаю что создал
			if (data[i] == '\0' && coef == -1 && k == 0) {
				// если один х
				if (sizePolynom == 0) {
					int sign;
					size_t countMinus = 0;
					while (static_cast<char>(data[i]) != 45 && data[i] != '+' && i != 0) {
						--i;
						++countMinus;
					}
					if (data[i] == '-') {
						sign = -1;
						i += countMinus;
					}
					else {
						sign = 1;
						i += countMinus;
					}
					sizePolynom += 2;
					polynom[0] = sign;
					delete[] help;
					break;
				}
				int sign;
				size_t countMinus = 0;
				while (static_cast<char>(data[i]) != 45 && data[i] != '+' && i != 0) {
					--i;
					++countMinus;
				}

				if (data[i] == '-') {
					sign = -1;
					i += countMinus;
				}
				else {
					sign = 1;
					i += countMinus;
				}
				coef = sign;
				polynom[sizePolynom - 2] += coef;
				coef = -1;
				delete[] help;
				break;
			}
			help[k] = '\0';
			// проверка знака при коэф = 1
			if (coef == -1) {
				int sign;
				size_t countMinus = 0;
				while (static_cast<char>(data[i]) != 45 && data[i] != '+' && i != 0) {
					--i;
					++countMinus;
				}

				if (data[i] == '-') {
					sign = -1;
					i += countMinus;
				}
				else {
					sign = 1;
					i += countMinus;
				}
				coef = sign;
			}
			size_t length = 0;
			if (strlen(help) == 0)
				length = sizePolynom - 1;
			else
				length = std::atoi(help);
			// если степень нулева€ то число 1 или -1
			if (help[0] == '0') {
				polynom[0] += coef / std::abs(coef);
				sizePolynom = 1;
				coef = -1;
				delete[] help;
			}
			else {
				size_t index = sizePolynom - length - 1;
				polynom[index] += coef;
				coef = -1;
				delete[] help;
			}
		}

		// если число
		else if (data[i] >= '0' && data[i] <= '9') {
			int sign; // знак коэф
			size_t countMinus = 0;
			// пока мы не нашли знак или не вернулись в начало, идЄм назад
			// и считаем, на сколько назад ушли. »щем знак коэф
			while (static_cast<char>(data[i]) != 45 && data[i] != '+' && i != 0) {
				--i;
				++countMinus;
			}

			if (data[i] == '-') {
				sign = -1;
				i += countMinus;
			}
			else {
				sign = 1;
				i += countMinus;
			}

			char* help = new char[10];
			size_t k = 0;
			while (data[i] >= '0' && data[i] <= '9') {
				help[k] = data[i];
				++k;
				++i;
			}
			--i;
			help[k] = '\0';
			coef = std::atoi(help) * sign;
			if (i == strlen(data) - 1) {
				polynom[sizePolynom - 1] += coef;
				delete[] help;
				break;
			}
			// новинка ќѕј—Ќќ
			if (i != strlen(data) - 1) {
				size_t helpindex = i + 1;
				while (data[helpindex] == ' ' && helpindex != strlen(data) - 1) {
					++helpindex;
				}
				if (data[helpindex] == 'x') continue;
				else {
					polynom[sizePolynom - 1] += coef;
					coef = -1;
				}
			}
			delete[] help;
		}

		else {
			continue;
		}
	}
	term.coeff__ = polynom[0];
	term.degree__ = sizePolynom - 1;

	delete[] data;
	delete[] polynom;
	return fin;
}
