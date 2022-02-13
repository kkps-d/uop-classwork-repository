/*
Lab 35
Kaung Khant Pyae Sone
Kaung Min Sett
*/

#include <iostream>
#include "citypriorityqueue.h"
using namespace std;

City cityArray[] = { City("Sacramento", 505628), City("Eugene", 221452), City("Stockton", 323761), City("Redding", 90292), City("San Diego", 1591688), City("Reno", 289485), City("Los Angeles", 4340174), City("Portland", 730428), City("Las Vegas", 711926), City("Seattle", 752180), City("San Francisco", 871421) };
CityMaxHeap cityHeap(cityArray, 11);

int main() {
	cout << "Initializing cityHeap with cityArray[]:" << endl;	
	cityHeap.printHeap();
	cout << endl;

	CityPriorityQueue cityPQueue(cityHeap);
	cout << "Is cityPQueue empty? " << cityPQueue.isEmpty() << endl;
	cout << "Length of cityPQueue: " << cityPQueue.getLength() << endl;
	cout << endl;

	cout << "Reading the front of cityPQueue: ";
	cityPQueue.peekCity()->printInfo();
	cout << endl;

	cout << "Removing the item at the front of cityPQueue." << endl;
	cityPQueue.popCity();
	cout << "Reading the front of cityPQueue: ";
	cityPQueue.peekCity()->printInfo();
	cout << endl;

	cout << "Inserting Phoenix with population 1660472 into CityPQueue." << endl;
	cityPQueue.pushCity(City("Phoenix", 1660472));

	cout << "Inserting Santa Fe with population 84263 into CityPQueue." << endl;
	cityPQueue.pushCity(City("Santa Fe", 84263));
	cout << "Reading the front of cityPQueue: ";
	cityPQueue.peekCity()->printInfo();
	cout << endl;

	cout << "Length of cityPQueue: " << cityPQueue.getLength() << endl;
}