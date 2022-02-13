#include <iostream>
#include "Cities.h"

void Cities::readCities() {
	string city;
	unsigned int population;
	City temp;
	cout << "Enter city name ('X' to stop): ";
	cin >> city;
	while (city != "X")
	{
		cout << "Enter population: ";
		cin >> population;
		temp.setName(city);
		temp.setPopulation(population);
		cityList.push_back(temp);
		cout << "Enter city name ('X' to stop): ";
		cin >> city;
	}
}

void Cities::printCityList() {
	for (unsigned int i = 0; i < cityList.size(); i++)
	{
		cout << cityList.at(i).getName() << " - " << cityList.at(i).getPopulation() << endl;
	}
}