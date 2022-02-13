/*
Lab 12
Kaung Khant Pyae Sone
Kaung Min Sett
*/

#include <iostream>
#include <vector>

using namespace std;

int a[] = { 5,7,-2,8,11,-9,4,6,12,-1 };
vector<int> vec1;

void initVector(vector<int> &first, int second[], int size) {
	for (int i = 0; i < size; i++)
	{
		first.push_back(second[i]);
	}
}

void printVector(const vector<int> input) {
	int size = input.size();
	for (int a : input)
	{
		cout << a;
		size--;
		if (size != 0)
		{
			cout << ", ";
		}
	}
}

int minVector(const vector<int> input) {
	int min = input.at(0);
	for (int a : input)
	{
		if (a < min)
		{
			min = a;
		}
	}
	return min;
}

int productVector(const vector<int> input) {
	int product = 1;
	for (int a : input) {
		product *= a;
	}
	return product;
}

void doubleVector(vector<int>& input) {
	for (int &a : input) {
		a *= 2;
	}
}

void aggregationVector(vector<int>& input) {
	int temp = 0;
	for (int& a : input) {
		temp += a;
		a = temp;
	}
}

int main() {
	initVector(vec1, a, 10);

	cout << "vec1 content: ";
	printVector(vec1);
	cout << endl;
	
	cout << "minimum of vec1: " << minVector(vec1) << endl;

	cout << "product of vec1: " << productVector(vec1) << endl;

	doubleVector(vec1);
	cout << "doubling each element of vec1: ";
	printVector(vec1);
	cout << endl;

	aggregationVector(vec1);
	cout << "aggregating element values in vec1: ";
	printVector(vec1);
}