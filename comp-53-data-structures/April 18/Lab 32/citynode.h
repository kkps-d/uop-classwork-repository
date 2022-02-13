#ifndef CITYNODE_H
#define CITYNODE_H

#include <string>
#include "city.h"
using namespace std;

class CityNode {
public:
	City data;
	CityNode* left;
	CityNode* right;

	CityNode(City city) {
		data = city;
		left = nullptr;
		right = nullptr;
	}
};

#endif
