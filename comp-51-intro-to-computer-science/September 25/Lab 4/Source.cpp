#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	float initialBalance;
	float currentBalance;
	float interestRate;
	float interestMin;
	float interestMax;
	float buffer;
	int yearsOpen;

	// A
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "What's the starting balance of your bank account?: ";
	cin >> initialBalance;
	cout << "What's your current interest rate?: ";
	cin >> interestRate;
	cout << "How many years do you intend to keep your bank account open?: ";
	cin >> yearsOpen;
	currentBalance = initialBalance;
	for (int i = 0; i < yearsOpen; i++)
	{
		currentBalance = currentBalance * (1 + interestRate / 100.0);
	}
	cout << "Bank balance after " << yearsOpen << " years: $" << currentBalance << endl;

	// B
	cout << "This will calculate the amount of money you will have after one year with different interest rates" << endl;
	cout << "Enter the minimum amount of interest: ";
	cin >> interestMin;
	cout << "Enter the maximum amount of interest: ";
	cin >> interestMax;
	if (interestMax < interestMin)
	{
		buffer = interestMax;
		interestMax = interestMin;
		interestMin = buffer;
	}
	for ( interestMin; interestMin <= interestMax; interestMin+=0.5)
	{
		cout << setw(5) << interestMin << ": ";
		currentBalance = initialBalance * (1 + interestMin / 100.0);
		cout << "$" << currentBalance << endl;
	}
	system("pause");

}