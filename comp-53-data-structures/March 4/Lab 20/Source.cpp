/*
Lab 20
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

void citySelectionSort(vector<City>& cities) {
	// 2 4 5 1 3 6
	unsigned int size = cities.size();
	unsigned int s;
	unsigned int temp;
	City ctyTmp("", 0);
	for (unsigned int i = 0; i < size; i++)
	{
		temp = cities.at(i).getPopulation();
		for (unsigned int j = i; j < size; j++)
		{
			if (cities.at(j).getPopulation() < temp)
			{
				temp = cities.at(j).getPopulation();
				s = j;
			}
		}
		ctyTmp = cities.at(i);
		cities.at(i) = cities.at(s);
		cities.at(s) = ctyTmp;
	}
}

void cityInsertionSort(vector<City>& cities) {
	unsigned int i, j;
	City ctyTmp("", 0);
	for (i = 0; i < cities.size(); ++i)
	{
		j = i;
		while (j > 0 && cities.at(j).getPopulation() < cities.at(j - 1).getPopulation())
		{
			ctyTmp = cities.at(j);
			cities.at(j) = cities.at(j - 1);
			cities.at(j - 1) = ctyTmp;
			j--;
		}
	}
}

int main() {
	cout << "Initializing cityVector with cityArray[]:" << endl;
	initVector(cityVector, cityArray, 11);
	printCityVector(cityVector);
	cout << endl;

	cout << "Selection sort on cityVector:" << endl;
	citySelectionSort(cityVector);
	printCityVector(cityVector);
	cout << endl;

	cout << "Re-initializing cityVector with cityArray[]:" << endl;
	initVector(cityVector, cityArray, 11);
	printCityVector(cityVector);
	cout << endl;

	cout << "Insertion sort on cityVector:" << endl;
	cityInsertionSort(cityVector);
	printCityVector(cityVector);
	cout << endl;
}