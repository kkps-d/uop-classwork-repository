/*
Lab 14
Kaung Khant Pyae Sone
Kaung Min Sett
*/

#include <iostream>
#include <map>
#include "city.h"
using namespace std;

City cityArray[] = { City("Los Angeles", 4000000), City("San Diego", 1500000), City("San Francisco", 900000), City("Sacramento", 500000), City("Stockton", 300000) };
map<string, unsigned int> cityMap;

void initMap(map<string, unsigned int>& maps, const City cities[], const int elmNum) {
	for (int i = 0; i < elmNum; i++)
	{
		maps.emplace(cities[i].getName(), cities[i].getPopulation());
	}
}

void printCityMap(const map<string, unsigned int>& maps) {
	for (auto name : maps)
	{
		cout << name.first << ": " << name.second << endl;
	}
}

unsigned int findPopulation(const map<string, unsigned int>& maps, const string name) {
	if (maps.count(name) != 0)
	{
		return maps.at(name);
	}
	else
	{
		return 0;
	}
	
}

void updatePopulation(map<string, unsigned int>& maps, const string name, const unsigned int population) {
	if (maps.count(name) != 0)
	{
		maps.at(name) = population;
	}
	else
	{
		maps.emplace(name, population);
	}
}

void removeFromCityMap(map<string, unsigned int>& maps, const string name) {
	maps.erase(name);
}


int main() {
	cout << "Initializing cityMap with cityArray[]:" << endl;
	initMap(cityMap, cityArray, 5);
	printCityMap(cityMap);
	cout << endl;

	cout << "Find population of Sacramento: " << findPopulation(cityMap, "Sacramento") << endl;
	cout << "Find population of Chicago: " << findPopulation(cityMap, "Chicago") << endl;
	cout << endl;

	updatePopulation(cityMap, "Stockton", 350000);
	cout << "Find population of Stockton after update: " << findPopulation(cityMap, "Stockton") << endl;
	updatePopulation(cityMap, "Portland", 700000);
	cout << "Find population of Portland after update: " << findPopulation(cityMap, "Portland") << endl;
	cout << endl;

	cout << "Removing San Francisco from cityMap:" << endl;
	removeFromCityMap(cityMap, "San Francisco");
	printCityMap(cityMap);

}