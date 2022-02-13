/*
Lab 6
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include "coastalcity.h"
#include "city.h"

#include <iostream>
using namespace std;

unsigned int CoastalCity::coastalCityCount = 0;

int main() {
	CoastalCity ccity1("San Diego", 1500000, "Pacific Ocean", 5);
	cout << "The address of ccity1: " << &ccity1 << endl;
	// BELONGS TO STACK MEMORY
	CoastalCity* ccityPtr1 = nullptr;
	cout << "The address stored in ccityPtr1: " << ccityPtr1 << endl;
	ccityPtr1 = &ccity1;
	cout << "The address stored in ccityPtr1: " << ccityPtr1 << endl << endl;

	cout << "ccityPtr1 used to call printInfo()" << endl;
	cout << "Using -> syntax: " << endl;
	ccityPtr1->printInfo();
	cout << endl;
	cout << "Using * syntax: " << endl;
	(*ccityPtr1).printInfo();
	cout << endl;

	CoastalCity* ccityPtr2 = new CoastalCity("Miami", 500000, "Atlantic Ocean", 8);

	cout << "The address stored in ccityPtr2: " << ccityPtr2 << endl << endl;
	// BELONGS TO HEAP MEMORY
	cout << "ccityPtr2 used to call printInfo()" << endl;
	cout << "Using -> syntax: " << endl;
	ccityPtr2->printInfo();
	cout << endl;
	cout << "Using * syntax: " << endl;
	(*ccityPtr2).printInfo();
	cout << endl;

	delete ccityPtr2;
	cout << "The address stored in ccityPtr2: " << ccityPtr2 << endl;

}