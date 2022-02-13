#ifndef CITY_H 
#define CITY_H

#include <string>
#include <iostream>

using namespace std;

class City {
public:
	City() {
		name = "";
		population = 0;
	}

	City(string nm, unsigned int pop) 
	{ name = nm; population = pop; } 

	void setName(string name) 
	{ this->name = name; } 
	
	void setPopulation(unsigned int population) 
	{ this->population = population; } 

	string getName() const { return this->name; } 
	
	unsigned int getPopulation() const { return this->population; } 
	
	virtual void printInfo() const { cout << getName() << ": " << getPopulation() << endl; } 

	protected: 
		string name; 
		unsigned int population;
};

#endif