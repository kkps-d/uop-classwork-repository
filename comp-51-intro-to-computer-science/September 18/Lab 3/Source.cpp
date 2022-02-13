#include <iostream>
#include <ctime>

using namespace std;

int main() {
	char userChoice;
	float a;
	int randA;
	float b;
	int randB;
	float c;
	float result;
	int randResult;
	int numStars;
	int currentStars;
	bool exit = 0;
	srand((unsigned)time(0));
	do
	{
		cout << "Welcome to my calculator" << endl << endl;
		cout << "Please select an operation from the following list: " << endl;
		cout << "(A)dd" << endl;
		cout << "(S)ubtract" << endl;
		cout << "(M)ultiply" << endl;
		cout << "(D)ivide" << endl;
		cout << "(C)ompare" << endl;
		cout << "(R)andom" << endl;
		cout << "S(t)ars" << endl;
		cout << "(Q)uit" << endl;
		cout << ">";
		cin >> userChoice;
		switch (userChoice)
		{
		case 'A':
		case 'a':
			cout << "Enter two numbers" << endl << ">";
			cin >> a >> b;
			result = a + b;
			cout << "The result is " << result;
			break;
		case 'S':
		case 's':
			cout << "Enter two numbers" << endl << ">";
			cin >> a >> b;
			result = a - b;
			cout << "THe result is " << result;
			break;
		case 'M':
		case 'm':
			cout << "Enter two numbers" << endl << ">";
			cin >> a >> b;
			result = a * b;
			cout << "The result is " << result;
			break;
		case 'D':
		case 'd':
			do
			{
				cout << "Enter two numbers" << endl << ">";
				cin >> a >> b;
				if (b == 0) {
					cout << "Cannot be divided by zero!" << endl;
				}
			} while (b == 0);
			result = a / b;
			cout << "The result is " << result;
			break;
		case 'C':
		case 'c':
			cout << "Enter two numbers" << endl << ">";
			cin >> a >> b;
			if (a > b)
			{
				cout << a << " is larger than " << b;
				break;
			}
			if (a < b)
			{
				cout << a << " is less than " << b;
				break;
			}
			else
			{
				cout << a << " is equal to " << b;
				break;
			}
			break;
		case 'R':
		case 'r':
			cout << "Enter range of numbers (min then max)" << endl << ">";
			cin >> randA >> randB;
			cout << "The five random numbers are: " << endl;
			for ( c = 0; c <= 5; c++)
			{
				randResult = rand() % randB + randA;
				cout << randResult << endl;
			}
			break;
		case 'T':
		case 't':
			b = 0;
			cout << "Enter the number of stars to display: ";
			do
			{
				cin >> a;
				if (a < 0)
				{
					cout << "Cannot display a negative number of stars!" << endl;
					cout << "Please enter a new number: ";
				}
			} while (a < 0);
			do
			{
				cout << "*";
				b++;
			} while (b < a);
			break;
		case 'Q':
		case 'q':
			exit = 1;
			break;
		default:
			cout << "Invalid option. Please try again";
			break;
		}
		cout << endl;
		if (exit != 1)
		{
			system("pause");
			system("cls");
		}
	} while (exit == 0);
	cout << "Thank you for using calculator" << endl;
	return 0;
}