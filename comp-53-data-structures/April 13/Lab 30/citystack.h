#ifndef CITYSTACK_H
#define CITYSTACK_H

#include "citylist.h"
class CityStack {
public:
	CityStack(CityList& l) {
		lst = l;
	}
	void pushCityNode(CityNode* cityNode) {
		lst.prepend(cityNode);
	}
	CityNode* popCityNode() {
		CityNode* temp;
		temp = lst.head;
		lst.remove(lst.head);
		return temp;
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
};

#endif