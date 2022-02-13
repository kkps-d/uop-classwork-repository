#ifndef CITY_H
#define CITY_H

#include <string>
#include <iostream>
using namespace std;

class City {
public:
	City();
	City(string name, unsigned int population);
	void setName(string name) { this->name = name; }
	void setPopulation(unsigned int population) {
		this->population = population;
	}
	string getName() const { return this->name; }
	unsigned int getPopulation() const { return this->population; }
	virtual void printInfo() const {	// void printInfo() const {
		cout << "Name: " << getName() << endl;
		cout << "Population: " << getPopulation() << endl;
	}
protected:
	string name;
	unsigned int population = 0;
};

City::City() {
	name = "N/A";
	population = 0;
}

City::City(string name, unsigned int population) {
	this->name = name;
	this->population = population;
}
#endif