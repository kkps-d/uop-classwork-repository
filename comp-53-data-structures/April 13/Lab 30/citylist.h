#ifndef CITYLIST_H
#define CITYLIST_H

#include <string>
#include "citynode.h"
using namespace std;

class CityList {
public:
	CityNode* head;
	CityNode* tail;
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
			head->next->prev = head;
			tail = cityNode;
		}
		else {
			tail->next = cityNode;
			tail->next->prev = tail;
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
			tail->prev = head;
		}
		else
		{
			head->prev = cityNode;
			cityNode->next = head;
			head = cityNode;
		}
	}
	void printCityList() {
		printCityListRecursive(head);
	}
	CityNode* search(string cityName) {
		return searchRecursive(head, cityName);
	}
	void remove(CityNode* curNode) {
		CityNode* sucNode = curNode->next;
		CityNode* predNode = curNode->prev;

		if (sucNode != nullptr)
		{
			sucNode->prev = predNode;
		}
		if (predNode != nullptr)
		{
			predNode->next = sucNode;
		}
		if (curNode == head)
		{
			head = sucNode;
		}
		if (curNode == tail)
		{
			tail = predNode;
		}
	}

private:
	void printCityListRecursive(CityNode* cityNode) {
		if (cityNode != nullptr)
		{
			cityNode->data.printInfo();
			printCityListRecursive(cityNode->next);
		}
	}
	CityNode* searchRecursive(CityNode* cityNode, string cityName) {
		if (cityNode != nullptr)
		{
			if (cityNode->data.getName() == cityName)
			{
				return cityNode;
			}
			return searchRecursive(cityNode->next, cityName);
		}
		return nullptr;
	}
};

#endif