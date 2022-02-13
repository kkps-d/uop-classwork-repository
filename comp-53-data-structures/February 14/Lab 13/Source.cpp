/*
Lab 13
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <list>

#include "city.h"

using namespace std;

int a[] = { 2,8,1,7,3 };
City cityArray[] = { City("Los Angeles", 4000000), City("San Diego", 1500000), City("San Francisco", 900000), City("Sacramento", 500000), City("Stockton", 500000) };

list<int> intList;
list<City> cityList;

template <typename T>
void initList(list<T>& lists, T arr[], int num) {
	for (int i = 0; i < num; i++)
	{
		lists.push_back(arr[i]);
	}
}

template <typename T>
void printList(const list<T> lists) {
	int size = lists.size();
	for (T a : lists) {
		cout << a;
		size--;
		if (size != 0)
		{
			cout << " ";
		}
	}
	cout << endl;
}

void printCityList(const list<City> lists) {
	for (City a : lists)
	{
		a.printInfo();
	}
}

template <typename T>
void rotateListRight(list<T>& lists, int n) {
	T temp;
	for (int i = 0; i < n; i++)
	{
		temp = lists.back();
		lists.pop_back();
		lists.push_front(temp);
	}
}

template <typename T>
void rotateListLeft(list<T>& lists, int n) {
	T temp;
	for (int i = 0; i < n; i++)
	{
		temp = lists.front();
		lists.pop_front();
		lists.push_back(temp);
	}
}

void removeFromCityList(list<City>& lists, string name) {
	list<City>::iterator itr;
	for ( itr = lists.begin(); itr != lists.end(); itr++)
	{
		if (itr->getName() == name)
		{
			lists.erase(itr);
			break;
		}
	}
}

void insertToCityList(list<City>& lists, City toPut, string name) {
	list<City>::iterator itr;
	for (itr = lists.begin(); itr != lists.end(); itr++)
	{
		if (itr->getName() == name)
		{
			lists.insert(itr, toPut);
			break;
		}
	}
}

int main() {
	cout << "Initializing intList with a[]:" << endl;
	initList(intList, a, 5);
	printList(intList);
	cout << endl;

	cout << "Initializing cityList with cityArray[]:" << endl;
	initList(cityList, cityArray, 5);
	printCityList(cityList);
	cout << endl;

	cout << "Rotating intList to right twice:" << endl;
	rotateListRight(intList, 2);
	printList(intList);
	cout << endl;

	cout << "Rotating cityList to right once:" << endl;
	rotateListRight(cityList, 1);
	printCityList(cityList);
	cout << endl;

	cout << "Rotating intList to left once:" << endl;
	rotateListLeft(intList, 1);
	printList(intList);
	cout << endl;

	cout << "Rotating cityList to left twice:" << endl;
	rotateListLeft(cityList, 2);
	printCityList(cityList);
	cout << endl;

	cout << "Removing Sacramento from cityList:" << endl;
	removeFromCityList(cityList, "Sacramento");
	printCityList(cityList);
	cout << endl;

	cout << "Inserting Redding to cityList before Stockton:" << endl;
	City Redding("Redding", 90000);
	insertToCityList(cityList, Redding, "Stockton");
	printCityList(cityList);
}