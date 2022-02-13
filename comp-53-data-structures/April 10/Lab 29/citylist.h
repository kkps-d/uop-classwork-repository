#ifndef CITYLIST_H
#define CITYLIST_H

#include <string>
#include "citynode.h"
using namespace std;

class CityList {
public:
	CityList() {
		head = tail = new CityNode(City());;
	}
	void append(CityNode* newNode) {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	void prepend(CityNode* newNode) {
		CityNode* firstNode = head->next;
		
		newNode->next = head->next;
		newNode->prev = head;
		
		head->next = newNode;

		if (firstNode != nullptr)
		{
			firstNode->prev = newNode;
		}
	}
	void printCityList() {
		CityNode* temp;
		temp = head->next;

		while (temp != nullptr)
		{
			temp->data.printInfo();
			temp = temp->next;
		}
	}
	CityNode* search(string cityName) {
		CityNode* curNode = head->next;
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
	void insert(CityNode* curNode, CityNode* newNode) {
		CityNode* sucNode;
		if (curNode == tail)
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		else
		{
			sucNode = curNode->next;
			newNode->next = sucNode;
			newNode->prev = curNode;
			curNode->next = newNode;
			sucNode->prev = newNode;
		}
	}
	void remove(CityNode* curNode) {
		if (curNode == head)
		{
			return;
		}
		CityNode* sucNode = curNode->next;
		CityNode* predNode = curNode->prev;
		if (sucNode != nullptr)
		{
			sucNode->prev = predNode;
		}
		predNode->next = sucNode;
		if (curNode == tail)
		{
			tail = predNode;
		}
	}

private:
	CityNode* head;
	CityNode* tail;
};

#endif