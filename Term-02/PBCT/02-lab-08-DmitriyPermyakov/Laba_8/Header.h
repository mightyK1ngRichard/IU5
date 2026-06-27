#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <ctime>

void EditText(std::string& word);
void PrintVector(const std::vector<float>& vec);
void Printlist(const std::list<int>& list);
size_t CountPositive(const std::list<int>& list);

class Planet {
public:
	Planet() = default;
	~Planet() = default;
	size_t GetDataSatellite();
	std::string GetDataName();
	void SetDataSatellite(const size_t& count);
	void SetDataName(const std::string& name);
	friend std::ostream& operator<<(std::ostream& out, const Planet& planet);

private:
	std::string name__;
	size_t satellite__;
};
inline void Planet::SetDataSatellite(const size_t& count) {
	satellite__ = count;
}
inline size_t Planet::GetDataSatellite() {
	return satellite__;
}
inline void Planet::SetDataName(const std::string& name) {
	name__ = name;
}
inline std::string Planet::GetDataName() {
	return name__;
}
inline std::ostream& operator<<(std::ostream& out, const Planet& planet) {
	out << planet.name__ << ' ' << planet.satellite__ << std::endl;
	return out;
}
