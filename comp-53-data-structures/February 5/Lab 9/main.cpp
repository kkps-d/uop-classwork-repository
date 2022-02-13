/*
Lab 9
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <vector>
using namespace std;

int a[] = { 5,7,-2,8,11,-9,4,6,12,-1 };
int b[] = { 4,16,9,-2,1,1,-2,9,16,4 };
vector<int> vec1, vec2, vec3;

void initVector(vector<int>& vect, int arr[], unsigned int elements) {
	for (unsigned int i = 0; i < elements; i++)
	{
		vect.push_back(arr[i]);
	}
}

void printVector(const vector<int>& vect) {
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		cout << vect.at(i);
		if (i < vect.size() - 1)
		{
			cout << ", ";
		}
	}
}

int minVector(const vector<int>& vect) {
	int least = vect.at(0);
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		if (vect.at(i) < least)
		{
			least = vect.at(i);
		}
	}
	return least;
}

int productVector(const vector<int>& vect) {
	int product = 1;
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		product *= vect.at(i);
	}
	return product;
}

void copyVector(const vector<int>& source, vector<int>& target) {
	target = source;
}

void greaterVector(const vector<int>& vectA, const vector<int>& vectB, vector<int>& target) {
	for (unsigned int i = 0; i < vectA.size(); i++)
	{
		if (vectA.at(i) > vectB.at(i))
		{
			target.at(i) = vectA.at(i);
		}
		else
		{
			target.at(i) = vectB.at(i);
		}
	}
}

bool isPalindrome(const vector<int>& vect) {
	bool isIt = false;
	for (unsigned int i = 0; i < vect.size() / 2; i++)
	{
		if (vect.at(i) == vect.at(vect.size() - i - 1))
		{
			isIt = true;
		}
		else
		{
			return false;
		}
	}
	return isIt;
}

void updateLast(vector<int>& vect, int forChange) {
	vect.pop_back();
	vect.push_back(forChange);
}

int main() {
	cout << "initial size of vec1: " << vec1.size() << endl;

	initVector(vec1, a, sizeof(a) / sizeof(a[0]));
	cout << "size of vec1 after initialization: " << vec1.size() << endl;

	cout << "vec1 content: ";
	printVector(vec1);
	cout << endl;

	initVector(vec2, b, sizeof(b) / sizeof(b[0]));

	cout << "vec2 content: ";
	printVector(vec2);
	cout << endl;

	cout << "minimum of vec1: " << minVector(vec1) << endl;

	cout << "product of vec1: " << productVector(vec1) << endl;

	copyVector(vec1, vec3);
	cout << "copy vec1 to vec3: ";
	printVector(vec3);
	cout << endl;

	greaterVector(vec1, vec2, vec3);
	cout << "collect larger elements from vec1 and vec2 to vec3: ";
	printVector(vec3);
	cout << endl;

	cout << "vec1 is ";
	if (!isPalindrome(vec1))
	{
		cout << "not ";
	}
	cout << "Palindrome" << endl;

	cout << "vec2 is ";
	if (!isPalindrome(vec2))
	{
		cout << "not ";
	}
	cout << "Palindrome" << endl;

	updateLast(vec3, 7);
	cout << "Updating the last element of vec3: ";
	printVector(vec3);
	cout << endl;
}