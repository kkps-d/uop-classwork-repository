#ifndef COASTALCITY_H
#define COASTALCITY_H

#include "city.h"
using namespace std;

class CoastalCity : public City {
public:
	CoastalCity();
	CoastalCity(string name, unsigned int population, string waterName, unsigned int beachNum);
	void setWaterName(string waterName) { this->waterName = waterName; }
	void setBeachNum(int beachNum) { this->beachNum = beachNum; }
	string getWaterName() const { return waterName; }
	int getBeachNum() const { return beachNum; }
	static int getCoastalCityCount() { return coastalCityCount; }
	void printInfo() const {
		City::printInfo();
		cout << "Water: " << getWaterName() << endl;
		cout << "No. of Beaches: " << getBeachNum() << endl;
	}
	CoastalCity operator*(int rhs) {
		CoastalCity temp;
		temp.setName(getName());
		temp.setWaterName(getWaterName());
		temp.setPopulation(getPopulation());
		temp.setBeachNum(getBeachNum() * rhs);
		return temp;
	}
	CoastalCity operator+(CoastalCity rhs) {
		CoastalCity tempCity;
		string temp;

		temp = getName();
		temp.append(rhs.getName());
		tempCity.setName(temp);

		tempCity.setPopulation(getPopulation() + rhs.getPopulation());

		temp = getWaterName();
		temp.append(rhs.getWaterName());
		tempCity.setWaterName(temp);

		tempCity.setBeachNum(getBeachNum() + rhs.getBeachNum());

		return tempCity;
	}
private:
	string waterName;
	int beachNum;
	static unsigned int coastalCityCount;
};

CoastalCity::CoastalCity() {
	name = "N/A";
	population = 0;
	waterName = "N/A";
	beachNum = 0;
	++coastalCityCount;
}

CoastalCity::CoastalCity(string name, unsigned int population, string waterName, unsigned int beachNum) {
	this->name = name;
	this->population = population;
	this->waterName = waterName;
	this->beachNum = beachNum;
	++coastalCityCount;
}
#endif