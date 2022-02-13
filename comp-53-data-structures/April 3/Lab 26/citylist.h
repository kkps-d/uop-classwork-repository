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
	void insert(CityNode* currNode, CityNode* cityNode) {
		if (head == nullptr)
		{
			append(cityNode);
		}
		else if (head == tail)
		{
			append(cityNode);
		}
		else
		{
			cityNode->next = currNode->next;
			currNode->next = cityNode;
		}
	}
	void remove(CityNode* currNode) {
		if (currNode == nullptr && head != nullptr)
		{
			head = head->next;
			if (head->next == nullptr)
			{
				tail = nullptr;
			}
		}
		else if (currNode->next != nullptr)
		{
			currNode->next = currNode->next->next;
			if (currNode->next->next == nullptr)
			{
				tail = currNode;
			}
		}
	
	}
private:
	CityNode* head;
	CityNode* tail;
};

#endif