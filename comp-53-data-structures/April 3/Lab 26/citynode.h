#ifndef CITYNODE_H
#define CITYNODE_H

#include <string>
#include "city.h"
using namespace std;

class CityNode {
public:
	CityNode(City city) {
		data = city;
		next = nullptr;
	}
	City data;
	CityNode* next;
};

#endif