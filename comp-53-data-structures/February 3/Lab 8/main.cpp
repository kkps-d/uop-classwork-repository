/*
Lab 8
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
using namespace std;

const int SIZE = 10;

int a[] = { 5,7,-2,8,11,-9,4,6,12,-1 };
int b[] = { 4,16,9,-2,1,14,-4,8,10,0 };
int c[SIZE];

void printArray(int arr[], int size) {
	for (int i = 0; i < size; i++)
	{
		cout << arr[i];
		if (i < size - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

int minArray(int arr[], int size) {
	int min = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}

int maxArray(int arr[], int size) {
	int max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

int sumArray(int arr[], int size) {
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}
	return sum;
}

int productArray(int arr[], int size) {
	int pdt = arr[0];
	for (int i = 1; i < size; i++)
	{
		pdt *= arr[i];
	}
	return pdt;
}

void copyArray(int arrA[], int arrB[], int size) {
	for (int i = 0; i < size; i++)
	{
		arrB[i] = arrA[i];
	}
}

void greaterArray(int arrA[], int arrB[], int arrC[], int size) {
	for (int i = 0; i < size; i++)
	{
		if (arrA[i] > arrB[i])
		{
			arrC[i] = arrA[i];
		}
		else
		{
			arrC[i] = arrB[i];
		}
	}
}

int main() {
	cout << "minimum of a[]: " << minArray(a, SIZE) << endl;
	cout << "maximum of a[] " << maxArray(a, SIZE) << endl;
	cout << "sum of a[]: " << sumArray(a, SIZE) << endl;
	cout << "product of a[]: " << productArray(a, SIZE) << endl;
	copyArray(a, c, SIZE);
	cout << "copy a[] to c[]: ";
	printArray(c, SIZE);
	greaterArray(a, b, c, SIZE);
	cout << "collect larger elements from a[] and b[] to c[]: ";
	printArray(c, SIZE);
	
}