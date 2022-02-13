/*
Lab 11
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <vector>
using namespace std;

int a[] = { 6,10,-4,11,-2 };
char str[7] = "Hello.";
vector<int> vec1;
vector<char> vec2;

template <typename Arbitary>
void reverseArray(Arbitary a[], const int length) {
	Arbitary temp;
	for (int i = 0; i < length / 2; i++)
	{
		temp = a[i];
		a[i] = a[length - 1 - i];
		a[length - 1 - i] = temp;
	}
}

template <typename Arbitary>
void printArray(Arbitary a[], const int length) {
	for (int i = 0; i < length; i++)
	{
		cout << a[i];
		if (i < length - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

template <typename Arbitary>
void initVector(vector<Arbitary>& a, Arbitary b[], const int length) {
	for (int i = 0; i < length; i++)
	{
		a.push_back(b[i]);
	}
}

template <typename Arbitary>
void replaceLastThree(vector<Arbitary>& a, Arbitary one, Arbitary two, Arbitary three) {
	a.pop_back();
	a.pop_back();
	a.pop_back();

	a.push_back(one);
	a.push_back(two);
	a.push_back(three);
}

template <typename Arbitary>
void printVector(vector<Arbitary> a) {
	for (unsigned int i = 0; i < a.size(); i++)
	{
		cout << a.at(i);
		if (i < a.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

template <typename Arbitary>
class Comparable
{
public:
	Comparable(Arbitary item1, Arbitary item2);
	bool lt();
	bool gt();
	bool eq();
private:
	Arbitary item1;
	Arbitary item2;
};

template <typename Arbitary>
Comparable<Arbitary>::Comparable(Arbitary item1, Arbitary item2){
	this->item1 = item1;
	this->item2 = item2;
}

template <typename Arbitary>
bool Comparable<Arbitary>::lt() {
	if (item1 < item2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename Arbitary>
bool Comparable<Arbitary>::gt() {
	if (item1 > item2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename Arbitary>
bool Comparable<Arbitary>::eq() {
	if (item1 == item2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main() {
	cout << "Reverse a[]:" << endl;
	reverseArray(a, 5);
	printArray(a, 5);
	cout << endl;

	cout << "Reverse str[]:" << endl;
	reverseArray(str, 7);
	printArray(str, 7);
	cout << endl;

	cout << "Initialize vec1 according to a[]:" << endl;
	initVector(vec1, a, 5);
	printVector(vec1);
	cout << endl;

	cout << "Initialize vec2 according to a[]:" << endl;
	initVector(vec2, str, 7);
	printVector(vec2);
	cout << endl;

	cout << "Replace last three elements of vec1 with 9, 0 , and 2:" << endl;
	replaceLastThree(vec1, 9, 0, 2);
	printVector(vec1);
	cout << endl;

	cout << "Replace last three elements of vec2 with 'f', 'y' , and 'o':" << endl;
	replaceLastThree(vec2, 'f', 'y', 'o');
	printVector(vec2);
	cout << endl;

	Comparable<int> comp1(3, 5);
	Comparable<char> comp2('r', 'b');

	cout << "Is 1st component of comp1 less than 2nd component of it? " << comp1.lt() << endl;
	cout << "Is 1st component of comp2 equal to 2nd component of it? " << comp2.eq() << endl;
}