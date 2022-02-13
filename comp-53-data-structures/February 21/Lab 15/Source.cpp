/*
Lab 15
Kaung Khant Pyae Sone
Kaung Min Sett
*/

#include <iostream>
#include <set>
#include <utility>
#include "city.h"
using namespace std;

int a[] = { 2,8,1,7,3 };
City cityArray1[] = { City("Los Angeles", 4000000), City("San Diego", 1500000), City("San Francisco", 900000), City("Sacramento", 500000), City("Stockton", 300000) };
City cityArray2[] = { City("Redding", 90000), City("Stockton", 300000), City("Las Vegas", 700000), City("Reno", 300000), City("Portland", 700000), City("Sacramento", 500000), City("Eugene", 200000) };

set<int> intSet;
set<City> citySet1;
set<City> citySet2;
set<City> citySet3;

set<string> cityNames;

template<typename T>
void initSet(set<T>& theSet, T theArray[], const int elmNum) {
	for (int i = 0; i < elmNum; i++)
	{
		theSet.insert(theArray[i]);
	}
}

template<typename T>
void printSet(const set<T>& theSet) {
	for (auto content : theSet) {
		cout << content << " ";
	}
	cout << endl;
}

void printCitySet(const set<City>& theSet) {
	for (auto cities : theSet) {
		cities.printInfo();
	}
}

void cityNamesSet(const set<City>& theSet, set<string>& theString) {
	for (auto cities : theSet) {
		theString.insert(cities.getName());
	}
}

template <typename T>
void setIntersection(const set<T>& set1, const set<T>& set2, set<T>& set3) {
	for (auto cities1 : set1) {
		for (auto cities2 : set2) {
			if (cities1.getName() == cities2.getName())
			{
				set3.insert(cities1);
			}
		}
	}
}

template <typename T>
void setUnion(const set<T>& set1, const set<T>& set2, set<T>& set3) {
	for (auto cities1 : set1) {
		set3.insert(cities1);
	}
	for (auto cities2 : set2) {
		set3.insert(cities2);
	}
}

template <typename T>
bool isSubset(const set<T>& set1, const set<T>& set2) {
	for (auto cities1 : set1)
	{
		if (set2.count(cities1) == 0)
		{
			return false;
		}
	}
	return true;
}

void removeFromCitySet(set<City>& citySet, string name) {
	City test("Sacramento", 500000);
	for (auto cities : citySet) {
		if (cities.getName() == name)
		{
			citySet.erase(test);
			return;
		}
	}
}

int main() {

	cout << "Initializing intSet with a[]:" << endl;
	initSet(intSet, a, 5);
	printSet(intSet);
	cout << endl;

	cout << "Initializing citySet1 with cityArray1[]:" << endl;
	initSet(citySet1, cityArray1, 5);
	printCitySet(citySet1);
	cout << endl;

	cout << "Initializing citySet2 with cityArray2[]:" << endl;
	initSet(citySet2, cityArray2, 7);
	printCitySet(citySet2);
	cout << endl;

	cout << "Populate cityNames according to the cities in citySet1:" << endl;
	cityNamesSet(citySet1, cityNames);
	printSet(cityNames);
	cout << endl;

	cout << "Intersect citySet1 and citySet2, and store the result in citySet3:" << endl;
	setIntersection(citySet1, citySet2, citySet3);
	printCitySet(citySet3);
	cout << endl;

	cout << "Union citySet1 and citySet2, and store the result in citySet3:" << endl;
	setUnion(citySet1, citySet2, citySet3);
	printCitySet(citySet3);
	cout << endl;

	cout << "citySet1 is a subset of citySet2? " << isSubset(citySet1, citySet2) << endl;
	cout << "citySet2 is a subset of citySet3? " << isSubset(citySet2, citySet3) << endl;
	cout << endl;

	cout << "Removing Sacramento from citySet1:" << endl;
	removeFromCitySet(citySet1, "Sacramento");
	printCitySet(citySet1);
	cout << endl;
}