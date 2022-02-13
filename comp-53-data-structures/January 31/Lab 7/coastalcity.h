#ifndef COASTALCITY_H
#define COASTALCITY_H

#include "city.h"
using namespace std;

class CoastalCity : public City {
public:
	CoastalCity();
	CoastalCity(string name, unsigned int population, string waterName, unsigned int beachNum, string adjName, unsigned int adjPopulation);
	~CoastalCity();
	void setWaterName(string waterName) { this->waterName = waterName; }
	void setBeachNum(int beachNum) { this->beachNum = beachNum; }
	string getWaterName() const { return waterName; }
	int getBeachNum() const { return beachNum; }
	static int getCoastalCityCount() { return coastalCityCount; }
	City* getAdjCity() { return adjCity; }
	void printInfo() const {
		City::printInfo();
		cout << "Water: " << getWaterName() << endl;
		cout << "No. of Beaches: " << getBeachNum() << endl;
		cout << "Adjacent City:" << endl;
		adjCity->printInfo();
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
	City* adjCity;
};

CoastalCity::CoastalCity() {
	name = "N/A";
	population = 0;
	waterName = "N/A";
	beachNum = 0;
	adjCity = new City();
	++coastalCityCount;
}

CoastalCity::CoastalCity(string name, unsigned int population, string waterName, unsigned int beachNum, string adjName, unsigned int adjPopulation) {
	this->name = name;
	this->population = population;
	this->waterName = waterName;
	this->beachNum = beachNum;
	adjCity = new City(adjName, adjPopulation);
	++coastalCityCount;
}
CoastalCity::~CoastalCity() {
	delete adjCity;
}
#endif