/*
Lab 31
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include "citylist.h"
#include "cityqueue.h"
#include "citydeque.h"
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

	CityQueue cityQueue(cityList);
	CityDeque cityDeque(cityList);

	cout << "Reading the front of cityQueue:" << endl;
	if (cityQueue.isEmpty())
	{
		cout << "null" << endl;
	}
	else
	{
		cityQueue.peekCityNode()->data.printInfo();
	}
	cityQueue.pushCityNode(new CityNode(City("Phoenix", 1660472)));
	cout << "Phoenix pushed to cityQueue." << endl;
	cityQueue.pushCityNode(new CityNode(City("Santa Fe", 84263)));
	cout << "Santa Fe pushed to cityQueue." << endl;
	cityQueue.popCityNode();
	cout << "Front of cityQueue is popped." << endl;
	cout << "Reading the front of cityQueue:" << endl;
	if (cityQueue.isEmpty())
	{
		cout << "null" << endl;
	}
	else
	{
		cityQueue.peekCityNode()->data.printInfo();
	}
	cout << "Check if cityQueue is empty: " << cityQueue.isEmpty() << endl;
	cout << endl;

	cout << "Reading the front of cityDeque:" << endl;
	if (cityDeque.isEmpty())
	{
		cout << "null" << endl;
	}
	else
	{
		cityDeque.peekFrontCityNode()->data.printInfo();
	}
	cout << "Reading the back of cityDeque:" << endl;
	if (cityDeque.isEmpty())
	{
		cout << "null" << endl;
	}
	else
	{
		cityDeque.peekBackCityNode()->data.printInfo();
	}
	cityDeque.pushFrontCityNode(new CityNode(City("Phoenix", 1660472)));
	cout << "Phoenix pushed to front of cityDeque." << endl;
	cityDeque.pushBackCityNode(new CityNode(City("Santa Fe", 84263)));
	cout << "Santa Fe pushed to back of cityDeque." << endl;
	cout << "Popping the front of cityDeque and printing it:" << endl;
	if (cityDeque.peekFrontCityNode() == nullptr)
	{
		cout << "null" << endl;
	}
	else
	{
		cityDeque.popFrontCityNode()->data.printInfo();
	}
	cout << "Popping the back of cityDeque and printing it:" << endl;
	if (cityDeque.peekFrontCityNode() == nullptr)
	{
		cout << "null" << endl;
	}
	else
	{
		cityDeque.popBackCityNode()->data.printInfo();
	}
}