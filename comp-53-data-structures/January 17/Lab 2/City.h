#pragma once
#include <string>
using namespace std;

class City
{
public:
	City() :name("N/A"), population(0) {};
	City(string name, int population) {
		this->name = name;
		this->population = population;
	}
	void setName(string name) {
		this->name = name;
	}
	void setPopulation(unsigned int population) {
		this->population = population;
	}
	string getName() {
		return name;
	}
	unsigned int getPopulation() {
		return population;
	}
private:
	string name;
	unsigned int population;
};



