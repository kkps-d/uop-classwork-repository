#ifndef CITYQUEUE_H
#define CITYQUEUE_H

#include "citylist.h"

class CityQueue {
public:
	CityQueue(CityList& l) { lst = l; }
	void pushCityNode(CityNode* cityNode) {
		lst.append(cityNode);
	}
	CityNode* popCityNode() {
		if (lst.head == nullptr)
		{
			return nullptr;
		}
		else
		{
			temp = lst.head;
			lst.remove(lst.head);
			return temp;
		}
	}
	CityNode* peekCityNode() {
		return lst.head;
	}
	bool isEmpty() {
		if (lst.head == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	CityList lst;
	CityNode* temp;
};

#endif