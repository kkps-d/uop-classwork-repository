/*
Lab 18
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
using namespace std;

int a[] = { 2,8,1,7,3 };
int b[5];

void printArray(int a[], int size, int index) {
	if (index < size)
	{
		cout << a[index] << " ";
		printArray(a, size, ++index);
	}
}

void printReverseArray(int a[], int size, int index) {
	if (index < size)
	{
		cout << a[size - index - 1] << " "; // 4
		printReverseArray(a, size, ++index);
	}
}

void reverseArray(int a[], int start, int end) {
	int temp;
	if (start == end)
	{
		return;
	}
	else
	{
		temp = a[start];
		a[start] = a[end];
		a[end] = temp;
		reverseArray(a, ++start, --end);
	}
}

int sum = 0;
int sumArray(int a[], int size, int index) {
	// Misses the first number
	//if (index < size) {
	//	cout << a[index] << endl;
	//	return sumArray(a, size, ++index) + a[index];
	//}
	//else {
	//	return 0;
	//}
	if (index < size) {
		sum += a[index];
		sumArray(a, size, ++index);
	}
	return sum;
}

int product = 1;
int productArray(int a[], int size, int index) {
	if (index < size) {
		product *= a[index];
		productArray(a, size, ++index);
	}
	return product;
}

void copyArray(int a[], int b[], int size, int index) {
	if (index < size)
	{
		b[index] = a[index];
		copyArray(a, b, size, ++index);
	}
}

int min;
int minArray(int a[], int size, int index) {
	if (index == 0)
	{
		min = a[index];
	}
	if (index < size)
	{
		if (a[index] < min)
		{
			min = a[index];
		}
		minArray(a, size, ++index);
	}
	return min;
}

int max;
int maxArray(int a[], int size, int index) {
	if (index == 0)
	{
		max = a[index];
	}
	if (index < size)
	{
		if (a[index] > max)
		{
			max = a[index];
		}
		maxArray(a, size, ++index);
	}
	return max;
}

int main() {
	cout << "Array a[] content in order:" << endl;
	printArray(a, 5, 0);
	cout << endl << endl;

	cout << "Array a[] content in reverse:" << endl;
	printReverseArray(a, 5, 0);
	cout << endl << endl;

	cout << "Reverse a[]" << endl;
	reverseArray(a, 0, 4);
	printArray(a, 5, 0);
	cout << endl << endl;

	cout << "Summation of elements in a[]:" << endl;
	cout << sumArray(a, 5, 0);
	cout << endl << endl;

	cout << "Product of elements in a[]:" << endl;
	cout << productArray(a, 5, 0);
	cout << endl << endl;

	cout << "Copying a[] to b[]:" << endl;
	copyArray(a, b, 5, 0);
	printArray(b, 5, 0);
	cout << endl << endl;

	cout << "Minimum element in a[]:" << endl;
	cout << minArray(a, 5, 0);
	cout << endl << endl;

	cout << "Maximum element in a[]:" << endl;
	cout << maxArray(a, 5, 0);
	cout << endl << endl;

	// Recurrence runtime relation: O(N)
	
	// Runtime complexity: O(log N)
}