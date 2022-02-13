/*
Lab 16
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include "city.h"
using namespace std;

City cityArray[] = { City("Los Angeles",4000000),City("San Diego",1500000),City("San Francisco",900000),City("Sacramento",500000),City("Stockton",300000) };
queue<City> cityQueue;
deque<City> cityStack;
vector<City> cityVector;

void initQueue(queue<City>& queues, City array[], int size) {
	for (int i = 0; i < size; i++)
	{
		queues.push(array[i]);
	}
}

void printCityQueue(queue<City>& queues) {
	City temp("", 0);
	int size = queues.size();
	for (int i = 0; i < size; i++)
	{
		temp = queues.front();
		temp.printInfo();
		queues.pop();
		queues.push(temp);
	}
}

void initStack(deque<City>& deques, City array[], int size) {
	for (int i = 0; i < size; i++)
	{
		deques.push_front(array[i]);
	}
}

void printCityStack(deque<City>& deques) {
	int size = deques.size();
	deque<City> second;
	for (int i = 0; i < size; i++)
	{
		second.push_front(deques.front());
		second.front().printInfo();
		deques.pop_front();
	}
	for (int i = 0; i < size; i++)
	{
		deques.push_front(second.front());
		second.pop_front();
	}
}

void initVector(vector<City>& vectors, City array[], int size) {
	for (int i = 0; i < size; i++)
	{
		vectors.push_back(array[i]);
	}
}

void printCityVector(const vector<City>& vectors) {
	for (auto elm : vectors) {
		elm.printInfo();
	}
}

bool largerName(City one, City two) {
	return !(one < two);
}

bool smallerPopu(City one, City two) {
	return one.getPopulation() < two.getPopulation();
}

int main() {
	cout << "Initializing cityQueue with cityArray[]:" << endl;
	initQueue(cityQueue, cityArray, 5);
	printCityQueue(cityQueue);
	cout << endl;

	cout << "Initializing cityStack with cityArray[]:" << endl;
	initStack(cityStack, cityArray, 5);
	printCityStack(cityStack);
	cout << endl;

	cout << "Initializing cityVector with cityArray[]:" << endl;
	initVector(cityVector, cityArray, 5);
	printCityVector(cityVector);
	cout << endl;

	cout << "Sorting cityVector based on names in descending order:" << endl;
	sort(cityVector.begin(), cityVector.end(), largerName);
	printCityVector(cityVector);
	cout << endl;

	cout << "Sorting cityVector based on populations in ascending order:" << endl;
	sort(cityVector.begin(), cityVector.end(), smallerPopu);
	printCityVector(cityVector);
	cout << endl;
}