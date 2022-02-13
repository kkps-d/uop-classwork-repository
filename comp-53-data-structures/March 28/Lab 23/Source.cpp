/*
Lab 23
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

void printCityVector(const vector<City>& cities) {
	for (auto elm : cities) {
		elm.printInfo();
	}
}

void mergeCityVector(vector<City>& cities, int lower, int div, int upper) {
	int mergedSize = upper - lower + 1;
	int mergePos = 0;
	int leftPos = 0;
	int rightPos = 0;
	vector<City> mergedCities;
	mergedCities.resize(mergedSize);

	leftPos = lower;
	rightPos = div + 1;

	while (leftPos <= div && rightPos <= upper)
	{
		if (cities.at(leftPos).getPopulation() <= cities.at(rightPos).getPopulation())
		{
			mergedCities.at(mergePos) = cities.at(leftPos);
			++leftPos;
		}
		else
		{           
			mergedCities.at(mergePos) = cities.at(rightPos);
			++rightPos;
		}
		++mergePos;
	}

	while (leftPos <= div) {
		mergedCities.at(mergePos) = cities.at(leftPos);
		++leftPos;
		++mergePos;
	}

	while (rightPos <= upper) {
		mergedCities.at(mergePos) = cities.at(rightPos);
		++rightPos;
		++mergePos;
	}

	for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
		cities.at(lower + mergePos) = mergedCities.at(mergePos);
	}
}

void cityMergeSort(vector<City>& cities, int lower, int upper) {
	int mid = 0;
	if (lower < upper)
	{
		mid = (lower + upper) / 2;
		cityMergeSort(cities, lower, mid);
		cityMergeSort(cities, mid + 1, upper);
		mergeCityVector(cities, lower, mid, upper);
	}
}

int main() {
	cout << "Initializing cityVector with cityArray[]:" << endl;
	initVector(cityVector, cityArray, 11);
	printCityVector(cityVector);
	cout << endl;

	cout << "Merge sort on cityVector:" << endl;
	cityMergeSort(cityVector, 0, 10);
	printCityVector(cityVector);
}