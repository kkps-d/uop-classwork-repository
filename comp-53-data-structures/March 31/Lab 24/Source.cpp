/*
Lab 24
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <vector>
#include <math.h>
#include "city.h"
using namespace std;

City cityArray[] = { City("Los Angeles", 4340174), City("San Diego", 1591688), City("San Francisco", 871421), City("Sacramento", 505628), City("Stockton", 323761), City("Redding", 90292), City("Las Vegas", 711926), City("Reno", 289485), City("Portland", 730428), City("Seattle", 752180), City("Eugene", 221452) };
vector<City> cityVector;
vector<unsigned int> popVector;

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

template <typename T>
void printVector(const vector<T>& vectorT) {
	for (auto elm : vectorT) {
		cout << elm << " ";
	}
}

void populationProject(vector<City> cities, vector<unsigned int>& pops) {
	for (auto elm : cities) {
		pops.push_back(elm.getPopulation());
	}
}

int radixGetLength(unsigned int num) {
	return to_string(num).length();
}

int radixGetMaxLength(const vector<unsigned int>& num) {
	int maxDigit = 0;
	for (auto elm : num) {
		if (radixGetLength(elm) > maxDigit)
		{
			maxDigit = radixGetLength(elm);
		}
	}
	return maxDigit;
}

void populationRadixSort(vector<unsigned int>& num) {
	vector<unsigned int> bucket[10];	
	int maxDigit = radixGetMaxLength(num);
	unsigned int pow10 = 1;
	int temp = 0;

	for (int digitIndex = 0; digitIndex < maxDigit; digitIndex++)
	{
		for (unsigned int i = 0; i < num.size(); i++)
		{
			temp = num.at(i) / pow10;
			bucket[abs(temp) % 10].push_back(num.at(i));
		}
		int numIndex = 0;

		for (int i = 0; i < 10; i++)
		{
			for (auto elm : bucket[i]) {
				num.at(numIndex) = elm;
				numIndex++;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			bucket[i].clear();
		}
		pow10 *= 10;
	}
}

int main() {
	cout << "Initializing cityVector with cityArray[]:" << endl;
	initVector(cityVector, cityArray, 11);
	printCityVector(cityVector);
	cout << endl;

	cout << "Initialize popVector according to cityVector:" << endl;
	populationProject(cityVector, popVector);
	printVector(popVector);
	cout << endl;

	cout << "Radix sort on popVector:" << endl;
	populationRadixSort(popVector);
	printVector(popVector);
	cout << endl;
}