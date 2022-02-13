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
};

#endif