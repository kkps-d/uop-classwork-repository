/*
Lab 34
Kaung Khant Pyae Sone
Kaung Min Sett
*/

#include <iostream>
#include "cityheap.h"
using namespace std;

City cityArray[] = { City("Sacramento", 505628), City("Eugene", 221452), City("Stockton", 323761), City("Redding", 90292), City("San Diego", 1591688), City("Reno", 289485), City("Los Angeles", 4340174), City("Portland", 730428), City("Las Vegas", 711926), City("Seattle", 752180), City("San Francisco", 871421) };
CityMaxHeap cityHeap(cityArray, 11);

int main() {
	cout << "Initializing cityHeap with cityArray[]:" << endl;	
	cityHeap.printHeap();
	cout << endl;

	cout << "Inserting Denver with population 600150 into cityHeap:" << endl;
	cityHeap.insert(City("Denver", 600150));
	cityHeap.printHeap();
	cout << endl;

	cout << "Removing the root of cityHeap:" << endl;
	cityHeap.remove();
	cityHeap.printHeap();
	cout << endl;

	cout << "Heap sort of cityHeap:" << endl;
	cityHeap.heapSort();
	cityHeap.printHeap();
	cout << endl;
}