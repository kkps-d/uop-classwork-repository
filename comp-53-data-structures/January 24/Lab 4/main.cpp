/*
Lab 4
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include "city.h"
#include "coastalcity.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
	City* myCity = new City;
	City* myCity2 = new City;
	CoastalCity* myCoastalCity = new CoastalCity;
	CoastalCity* myCoastalCity2 = new CoastalCity;
	vector<City*> cityPtr = {myCity, myCity2, myCoastalCity, myCoastalCity2};

	myCity->setName("Denver");
	myCity->setPopulation(750000);

	myCity2->setName("Reno");
	myCity2->setPopulation(250000);

	myCoastalCity->setName("San Diego");
	myCoastalCity->setPopulation(250000);
	myCoastalCity->setWaterName("Pacific Ocean");
	myCoastalCity->setBeachNum(5);

	myCoastalCity2->setName("Miami");
	myCoastalCity2->setPopulation(500000);
	myCoastalCity2->setWaterName("Atlantic Ocean");
	myCoastalCity2->setBeachNum(8);

	for (unsigned int i = 0; i < cityPtr.size(); i++)
	{
		cityPtr.at(i)->printInfo();
		cout << endl;
	}
}