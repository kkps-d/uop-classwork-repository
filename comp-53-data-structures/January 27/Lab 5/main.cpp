/*
Lab 5
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include "city.h"
#include "coastalcity.h"

#include <iostream>
using namespace std;

unsigned int CoastalCity::coastalCityCount = 0;

int main() {
	CoastalCity sanDiego;
	CoastalCity miami;
	CoastalCity temp;

	sanDiego.setName("San Diego");
	sanDiego.setPopulation(1500000);
	sanDiego.setWaterName("Pacific Ocean");
	sanDiego.setBeachNum(5);

	miami.setName("Miami");
	miami.setPopulation(500000);
	miami.setWaterName("Atlantic Ocean");
	miami.setBeachNum(8);

	sanDiego = sanDiego * 5;
	sanDiego.printInfo();

	cout << endl;

	temp = sanDiego + miami;
	temp.printInfo();

	cout << endl;

	cout << CoastalCity::getCoastalCityCount();
}