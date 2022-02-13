/*
Lab 28
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include "citylist.h"
using namespace std;

City cityArray[] = { City("Los Angeles", 4340174), City("San Diego", 1591688), City("San Francisco", 871421), City("Sacramento", 505628), City("Stockton", 323761), City("Redding", 90292), City("Las Vegas", 711926), City("Reno", 289485), City("Portland", 730428), City("Seattle", 752180), City("Eugene", 221452) };
CityList cityList;

void initCityListByAppend(CityList& list, const City arr[], int size) {
	for (int i = 0; i < size; i++)
	{
		CityNode* temp = new CityNode(arr[i]);
		list.append(temp);
	}
}

void initCityListByPrepend(CityList& list, const City arr[], int size) {
	for (int i = 0; i < size; i++)
	{
		CityNode* temp = new CityNode(arr[i]);
		list.prepend(temp);
	}
}

int main() {
	cout << "Initializing cityList with cityArray[] using appending:" << endl;
	initCityListByAppend(cityList, cityArray, 11);
	cityList.printCityList();
	cout << endl;

	cout << "Insertion sort of cityList by population:" << endl;
	cityList.insertionSortByPopulation();
	cityList.printCityList();
	cout << endl;
}