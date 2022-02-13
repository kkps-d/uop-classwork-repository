#ifndef CITYLIST_H
#define CITYLIST_H

#include <string>
#include "citynode.h"
using namespace std;

class CityList {
public:
	CityList() {
		head = tail = nullptr;
	}
	void append(CityNode* cityNode) {
		if (head == nullptr)
		{
			head = cityNode;
			tail = cityNode;
		}
		else if (head == tail)
		{
			head->next = cityNode;
			tail = cityNode;
		}
		else {
			tail->next = cityNode;
			tail = cityNode;
		}
	}
	void prepend(CityNode* cityNode) {
		if (head == nullptr)
		{
			head = cityNode;
			tail = cityNode;
		}
		else if (head == tail)
		{
			head = cityNode;
			head->next = tail;
		}
		else
		{
			cityNode->next = head;
			head = cityNode;
		}
	}
	void printCityList() {
		CityNode* temp;
		temp = head;

		while (temp != nullptr)
		{
			temp->data.printInfo();
			temp = temp->next;
		}
	}
	CityNode* search(string cityName) {
		CityNode* curNode = head;
		while (curNode != nullptr)
		{
			if (curNode->data.getName() == cityName)
			{
				return curNode;
			}
			curNode = curNode->next;
		}
		return nullptr;
	}
private:
	CityNode* head;
	CityNode* tail;
};

#endif