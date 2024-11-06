#pragma once
#include "Header.h"

class weapon {
public:
	weapon() = default;
	virtual ~weapon() = default;
	virtual void Shoot() = 0;
};
class gun : public weapon {
public:
	gun() = default;
	~gun() = default;
	void Shoot() override {
		std::cout << " BAM " << std::endl;
	}

};
class machinegun : public weapon {
public:
	machinegun() = default;
	~machinegun() = default;
	void Shoot() override {
		std::cout << " BAMBAMBAM" << std::endl;
	}

};
class player {
public:
	player() = default;
	~player() = default;

	void Shoot(weapon* attack) {
		attack->Shoot();
	}
};
