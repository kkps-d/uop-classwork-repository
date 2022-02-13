/*
Lab 19
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include "city.h"
using namespace std;

City cityArray[] = { City("Los Angeles", 4000000), City("San Diego", 1500000), City("San Francisco", 900000), City("Sacramento", 500000), City("Stockton", 300000), City("Redding", 90000), City("Las Vegas", 700000), City("Reno", 300000), City("Portland", 700000), City("Seattle", 750000), City("Eugene", 200000) };
vector<City> cityVector;
int steps = 0;

void initVector(vector<City>& cities, City arr[], int size) {
	for (int i = 0; i < size; i++)
	{
		cities.push_back(arr[i]);
	}
}

void printCityVector(const vector<City>& cities) {
	for (auto elm : cities) {
		elm.printInfo();
	}
}

bool isSmaller(const City a, const City b) {
	return a < b;
}

unsigned int cityLinearSearch(const vector<City>& cities, const string name) {
	steps = 0;
	for (auto elm : cities) {
		steps++;
		if (elm.getName() == name)
		{
			return elm.getPopulation();
		}
	}
	return 0;
}

unsigned int cityBinarySearch(const vector<City>& cities, const string name) {
	steps = 0;
	int mid = 0;
	int low = 0;
	int high = cities.size() - 1;

	while (high >= low)
	{
		steps++;
		mid = (high + low) / 2;
		if (cities.at(mid).getName() < name)
		{
			low = mid + 1;
		}
		else if (cities.at(mid).getName() > name) {
			high = mid - 1;
		}
		else {
			return cities.at(mid).getPopulation();
		}
	}
	return 0;
}

int main() {
	cout << "Initializing cityVector with cityArray[]:" << endl;
	initVector(cityVector, cityArray, 11);
	printCityVector(cityVector);
	cout << endl; 

	cout << "Sorting cityVector based on names in ascending order:" << endl;
	sort(cityVector.begin(), cityVector.end(), isSmaller);
	printCityVector(cityVector);
	cout << endl;

	cout << "Linear search for the population of San Francisco: " << cityLinearSearch(cityVector, "San Francisco") << endl;
	cout << "Number of comparisons for this search: " << steps << endl;
	cout << endl;

	cout << "Linear search for the population of Boston: " << cityLinearSearch(cityVector, "Boston") << endl;
	cout << "Number of comparisons for this search: " << steps << endl;
	cout << endl;

	cout << "Binary search for the population of San Francisco: " << cityBinarySearch(cityVector, "San Francisco") << endl;
	cout << "Number of comparisons for this search: " << steps << endl;
	cout << endl;

	cout << "Binary search for the population of Boston: " << cityBinarySearch(cityVector, "Boston") << endl;
	cout << "Number of comparisons for this search: " << steps << endl;
	cout << endl;
}