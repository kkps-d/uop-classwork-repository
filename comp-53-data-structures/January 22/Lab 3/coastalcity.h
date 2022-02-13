#ifndef COASTALCITY_H
#define COASTALCITY_H

#include "city.h"
using namespace std;

class CoastalCity : public City {
public:
	CoastalCity();
	void setWaterName(string waterName) { this->waterName = waterName; }
	void setBeachNum(int beachNum) { this->beachNum = beachNum; }
	string getWaterName() const { return waterName; }
	int getBeachNum() const { return beachNum; }
	void printInfo() const {
		City::printInfo();
		cout << "Water: " << getWaterName() << endl;
		cout << "No. of Beaches: " << getBeachNum() << endl;
	}
private:
	string waterName;
	int beachNum;
};

CoastalCity::CoastalCity() {
	name = "N/A";
	population = 0;
	waterName = "N/A";
	beachNum = 0;
}
#endif