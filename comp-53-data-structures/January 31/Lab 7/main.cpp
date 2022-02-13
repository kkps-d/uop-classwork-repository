/*
Lab 7
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include "city.h"
#include "coastalcity.h"

#include <iostream>
using namespace std;

unsigned int CoastalCity::coastalCityCount = 0;

int main() {
	CoastalCity* ccityPtr = new CoastalCity("Miami", 500000, "Atlantic Ocean", 8, "Coral Gables", 50000);
	cout << "address of coastal city = " << ccityPtr << endl;
	cout << "address of adjacent city = " << ccityPtr->getAdjCity() << endl;
	ccityPtr->printInfo();
}