#pragma once
#include "City.h"
#include <vector>
class Cities
{
public:
	void readCities();
	void printCityList();
private:
	vector<City> cityList;
};

