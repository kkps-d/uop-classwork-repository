#include <iostream>
#include <ctime>
using namespace std;

int sumX(int x) {
	if (x < 0)
	{
		return (x + sumX(x + 1));
	}
	else if (x > 0)
	{
		return (x + sumX(x - 1));
	}
	else
	{
		return 0;
	}
}

int sumXY(int x, int y) {
	if (y > x)
	{
		return (x + sumXY(x + 1, y));
	}
	else if (y < x)
	{
		return (x + sumXY(x - 1, y));
	}
	else
	{
		return x;
	}
}

void fillArray(int arr[], int size) {
	if (size > 1)
	{
		arr[size - 1] = rand() % 11;
		fillArray(arr, size - 1);
	}
	else {
		arr[size - 1] = rand() % 11;
	}
}

int main() {
	srand(unsigned(time(0)));
	int arr[5];
	int size = 5;

	cout << "sumX(5) = " << sumX(5) << endl;
	cout << "sumX(-5) = " << sumX(-5) << endl;
	cout << "sumX(0, 5) = " << sumXY(0, 5) << endl;
	cout << "sumX(5, 0) = " << sumXY(5, 0) << endl;
	fillArray(arr, size);
	cout << "fillArray(arr, 5) = ";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}