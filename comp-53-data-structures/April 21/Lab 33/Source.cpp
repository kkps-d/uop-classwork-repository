/*
Lab 33
Kaung Khant Pyae Sone
Kaung Min Sett
*/

#include <iostream>
#include "citybst.h"
using namespace std;

City cityArray[] = { City("Sacramento", 505628), City("Eugene", 221452), City("Stockton", 323761), City("Redding", 90292), City("San Diego", 1591688), City("Reno", 289485), City("Los Angeles", 4340174), City("Portland", 730428), City("Las Vegas", 711926), City("Seattle", 752180), City("San Francisco", 871421) };
CityBST cityBST;

void initCityBSTByInsert(CityBST& bst, City array[], int length) {
	for (int i = 0; i < length; i++)
	{
		cityBST.insert(new CityNode(array[i]));
	}
}

int main() {
	cout << "Initializing cityBST with cityArray[] using appending:" << endl;
	initCityBSTByInsert(cityBST, cityArray, 11);
	cityBST.printCityBST();
	cout << endl;

	cout << "Height of cityBST: " << cityBST.getHeight() << endl << endl;

	CityNode* temp;
	cout << "Searching in cityBST for the city with population 289485: ";
	temp = cityBST.search(289485);
	if (temp != nullptr)
	{
		cout << temp->data.getName() << endl;
	}
	else
	{
		cout << "not found!" << endl;
	}

	cout << "Searching in cityBST for the city with population 782297: ";
	temp = cityBST.search(782297);
	if (temp != nullptr)
	{
		cout << temp->data.getName() << endl;
	}
	else
	{
		cout << "not found!" << endl;
	}
	cout << endl;

	cout << "Removing city with population 871421 (San Francisco):" << endl;
	cityBST.remove(871421);
	cityBST.printCityBST();
	cout << endl;

	cout << "Removing city with population 323761 (Stockton):" << endl;
	cityBST.remove(323761);
	cityBST.printCityBST();
	cout << endl;

	cout << "Removing city with population 505628 (Sacramento):" << endl;
	cityBST.remove(505628);
	cityBST.printCityBST();
	cout << endl;

	cout << "Height of cityBST: " << cityBST.getHeight() << endl << endl;

	cout << "cityBST inorder traversal and printing:" << endl;
	cityBST.printCityBST_InOrder();
}