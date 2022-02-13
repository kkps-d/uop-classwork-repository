/*
Lab 3
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include "coastalcity.h"
using namespace std;

int main() {
	CoastalCity temp;
	temp.printInfo();
	temp.setName("San Francisco");
	temp.setPopulation(900000);
	temp.setWaterName("SF Bay");
	temp.setBeachNum(10);
	temp.printInfo();
	system("pause");
}