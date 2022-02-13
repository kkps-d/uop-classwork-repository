#ifndef CITYHEAP_H
#define CITYHEAP_H

#include <string>
#include "city.h"

const int maxArraySize = 100;

class CityMaxHeap {
public:
	CityMaxHeap() {
		arraySize = 0;
	}
	CityMaxHeap(City arr[], int size) {
		for (int i = 0; i < size; i++)
		{
			array[i] = arr[i];
		}
		arraySize = size;
		cityHeapify();
	}
	void printHeap() {
		for (int i = 0; i < arraySize; i++)
		{
			array[i].printInfo();
		}
	}
	void insert(City city) {
		array[arraySize] = city;
		percolateUp(arraySize);
		arraySize++;
	}
	void remove() {
		for (int i = 1; i < arraySize; i++)
		{
			array[i - 1] = array[i];
		}
		percolateDown(0, arraySize);
		arraySize--;
		/*array[0] = array[arraySize-1];
		percolateDown(0, arraySize);
		arraySize--;*/
	}
	void heapSort() {
		City temp;

		for (int i = arraySize / 2 - 1; i >= 0; i--)
		{
			percolateDown(i, arraySize);
		}
		for (int i = arraySize - 1; i > 0; i--)
		{
			temp = array[0];
			array[0] = array[i];
			array[i] = temp;
			percolateDown(0, i);
		}
	}

	City test[10] = {};

private:
	City array[maxArraySize];
	int arraySize;

	void percolateUp(int nodeInd) {
		int parentInd;
		City temp;

		while (nodeInd > 0) 
		{
			parentInd = (nodeInd - 1) / 2;
			if (array[nodeInd].getPopulation() <= array[parentInd].getPopulation())
			{
				return;
			}
			else
			{
				temp = array[parentInd];
				array[parentInd] = array[nodeInd];
				array[nodeInd] = temp;
				nodeInd = parentInd;
			}
		}
	}

	void percolateDown(int nodeInd, int size) {
		int childInd = 2 * nodeInd + 1;
		int value = array[nodeInd].getPopulation();
		unsigned int maxValue;
		int maxInd;
		City temp;

		while (childInd < size)
		{
			maxValue = value;
			maxInd = -1;
			for (int i = 0; i < 2 && i + childInd < size; i++)
			{
				if (array[i + childInd].getPopulation() > maxValue)
				{
					maxValue = array[i + childInd].getPopulation();
					maxInd = i + childInd;
				}
			}
			if (maxValue == value)
			{
				return;
			}
			else
			{
				temp = array[maxInd];
				array[maxInd] = array[nodeInd];
				array[nodeInd] = temp;
				nodeInd = maxInd;
				childInd = 2 * nodeInd + 1;
			}
		}
	}

	void cityHeapify() {
		/*for (int i = 0; i < arraySize; i++)
		{
			percolateDown(i, arraySize);
		}*/
		for (int i = arraySize / 2 - 1; i >= 0; i--)
		{
			percolateDown(i, arraySize);
		}
	}
};

#endif
