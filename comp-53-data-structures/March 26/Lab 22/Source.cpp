/*
Lab 22
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <vector>
#include "city.h"
using namespace std;

City cityArray[] = { City("Los Angeles", 4000000), City("San Diego", 1500000), City("San Francisco", 900000), City("Sacramento", 500000), City("Stockton", 300000), City("Redding", 90000), City("Las Vegas", 700000), City("Reno", 300000), City("Portland", 700000), City("Seattle", 750000), City("Eugene", 200000) };
vector<City> cityVector;

void initVector(vector<City>& cities, City arr[], int size) {
	cities.clear();
	for (int i = 0; i < size; i++)
	{
		cities.push_back(arr[i]);
	}
}

void printCityVector (const vector<City>& cities) {
	for (auto elm : cities) {
		elm.printInfo();
	}
}

int cityPartition(vector<City>& cities, int lower, int upper) {
	int l = 0;
	int h = 0;
	int midPoint = 0;
	unsigned int pivot = 0;
	City temp("", 0);
	bool done = false;

	midPoint = lower + (upper - lower) / 2;
	pivot = cities.at(midPoint).getPopulation();

	l = lower;
	h = upper;

	while (!done) {
		while (cities.at(l).getPopulation() < pivot)
		{
			++l;
		}

		while (pivot < cities.at(h).getPopulation())
		{
			--h;
		}

		if (l >= h)
		{
			done = true;
		}
		else
		{
			temp = cities.at(l);
			cities.at(l) = cities.at(h);
			cities.at(h) = temp;
			++l;
			--h;
		}
	}

	return h;
}

void cityQuickSort(vector<City>& cities, int lower, int upper) {
	int j = 0;

	if (lower >= upper)
	{
		return;
	}

	j = cityPartition(cities, lower, upper);

	cityQuickSort(cities, lower, j);
	cityQuickSort(cities, j + 1, upper);
}

int main() {
	initVector(cityVector, cityArray, 11);

	cout << "Initializing cityVector with cityArray[]:" << endl;
	printCityVector(cityVector);
	cout << endl;

	cout << "Quick sort on cityVector:" << endl;
	cityQuickSort(cityVector, 0, 10);
	printCityVector(cityVector);
	cout << endl;
}