#include <iostream>
using namespace std;

int fact(int num);

int main() {
	int result, number;

	cout << "Enter a number for factorial: ";
	cin >> number;
	result = fact(number);
	cout << "factorial = " << result << endl;

	system("pause");

}

int fact(int num) {
	int value = 1;
	while (num > 0)
	{
		value *= num;
		num--;
	}
	return value;
}

bool coinFlip(char choice) {
	int flip = rand() % 2;
	if (flip == 0) {
		if (choice == 'h')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (choice != 'h')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}