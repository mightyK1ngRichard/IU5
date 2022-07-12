#pragma once
#include <iostream>
#include <Windows.h>
#include <list>
#include <string>

class Abstr {
public:
	Abstr() : data__(0) {}
	Abstr(const double& data) : data__(data) {}
	virtual ~Abstr() {
		std::cout << "хо-хо-хо\n";
	}
	virtual void Print() = 0;
private:
	double data__;
};
class Deriv1 : public Abstr {
public:
	Deriv1() : data__(0) {}
	Deriv1(const double& data) : data__(data) {}
	bool operator==(const Deriv1& der) const;
	~Deriv1() = default;
	void Print();
private:
	double data__;
};
bool Deriv1::operator==(const Deriv1& der) const{
	return data__ == der.data__;
}
void Deriv1::Print() {
	std::cout << "| Deriv1:  " << data__;
}
class Deriv2 : public Abstr {
public:
	Deriv2() : data__(0) {}
	Deriv2(const double& data) : data__(data) {}
	bool operator==(const Deriv2& der) const;
	~Deriv2() = default;
	void Print();
private:
	double data__;
};
bool Deriv2::operator==(const Deriv2& der) const {
	return data__ == der.data__;
}
void Deriv2::Print() {
	std::cout << "| Deriv2:  " << data__;
}
class Deriv3 : public Abstr {
public:
	Deriv3() : data__(0) {}
	Deriv3(const double& data) : data__(data) {}
	bool operator==(const Deriv3& der) const;
	~Deriv3() = default;
	void Print();
private:
	double data__;
};
bool Deriv3::operator==(const Deriv3& der) const {
	return data__ == der.data__;
}
void Deriv3::Print() {
	std::cout << "| Deriv3:  " << data__;
}
struct Together {
	bool operator == (const Together& object) const;
	Deriv1 a;
	Deriv2 b;
	Deriv3 c;
};
bool Together::operator==(const Together& object) const {
	return object.a == a && object.b == b && object.c == c;
}
