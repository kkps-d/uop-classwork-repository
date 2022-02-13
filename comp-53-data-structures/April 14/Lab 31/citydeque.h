#ifndef CITYDEQUE_H
#define CITYDEQUE_H

#include "citylist.h"

class CityDeque {
public:
	CityDeque(CityList& l) { lst = l; };
	void pushFrontCityNode(CityNode* cityNode) {
		lst.prepend(cityNode);
	}
	void pushBackCityNode(CityNode* cityNode) {
		lst.append(cityNode);
	}
	CityNode* popFrontCityNode() {
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
	CityNode* popBackCityNode() {
		if (lst.head == nullptr)
		{
			return nullptr;
		}
		else
		{
			temp = lst.tail;
			lst.remove(lst.tail);
			return temp;
		}
	}
	CityNode* peekFrontCityNode() {
		return lst.head;
	}
	CityNode* peekBackCityNode() {
		return lst.tail;
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