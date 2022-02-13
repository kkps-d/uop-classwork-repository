/*
Lab 21
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <vector>
#include "city.h"
using namespace std;

City cityArray[] = { City("Los Angeles", 4000000), City("San Diego", 1500000), City("San Francisco", 900000), City("Sacramento", 500000), City("Stockton", 300000), City("Redding", 90000), City("Las Vegas", 700000), City("Reno", 300000), City("Portland", 700000), City("Seattle", 750000), City("Eugene", 200000) };
int gaps[] = { 4,2,1 };
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

//void cityInsertionSort(vector<City>& cities) {
//	unsigned int i, j;
//	City ctyTmp("", 0);
//	for (i = 0; i < cities.size(); ++i)
//	{
//		j = i;
//		while (j > 0 && cities.at(j).getPopulation() < cities.at(j - 1).getPopulation())
//		{
//			ctyTmp = cities.at(j);
//			cities.at(j) = cities.at(j - 1);
//			cities.at(j - 1) = ctyTmp;
//			j--;
//		}
//	}
//}

void cityInterleavedInsertionSort(vector<City>& cities, int start, int gap) {
	int i = 0;
	int j = 0;
	City temp("", 0);

	for (int i = start + gap; i < cities.size(); i += gap)
	{
		j = i;
		while (j - gap >= start && cities.at(j).getPopulation() < cities.at(j - gap).getPopulation() )
		{
			temp = cities.at(j);
			cities.at(j) = cities.at(j - gap);
			cities.at(j - gap) = temp;
			j = j - gap;
		}
	}
}

void cityShellSort(vector<City>& cities, int gaps[], int size) {
	for (int i = 0; i < size; i++)
	{
		cityInterleavedInsertionSort(cities, 0, gaps[i]);
	}
}

int main() {
	cout << "Initializing cityVector with cityArray[]:" << endl;
	initVector(cityVector, cityArray, 11);
	printCityVector(cityVector);
	cout << endl;

	cout << "Shell sort on cityVector:" << endl;
	cityShellSort(cityVector, gaps, 3);
	printCityVector(cityVector);
}