/*
Lab 30
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include "citylist.h"
#include "citystack.h"
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

int main() {
	cout << "Initializing cityList with cityArray[] using appending:" << endl;
	initCityListByAppend(cityList, cityArray, 11);
	cityList.printCityList();
	cout << endl;

	cout << "Searching for Stockton in cityList1, if found print its population:" << endl;
	cout << cityList.search("Stockton")->data.getPopulation() << endl;
	cout << endl;

	CityStack cityStack(cityList);
	cout << "Reading the top of cityStack:" << endl;
	cityStack.peekCityNode()->data.printInfo();
	cout << endl;

	cout << "Phoenix pushed." << endl;
	cityStack.pushCityNode(new CityNode(City("Phoenix", 1660472)));

	cout << "Santa Fe pushed." << endl;
	cityStack.pushCityNode(new CityNode(City("Santa Fe", 84263)));

	cout << "Top of stack is popped." << endl;
	cityStack.popCityNode();
	cout << "Reading the top of cityStack:" << endl;
	cityStack.peekCityNode()->data.printInfo();
}