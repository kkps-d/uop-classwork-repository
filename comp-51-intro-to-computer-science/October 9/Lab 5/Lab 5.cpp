/*****************************************************************************
*  Filename: Lab 5 Soln.cpp
*  Author: M Canniff
*  Description: A program to allow the user to calculate various financial
*				projections such as the rate of inflation
*               on a number of items and the predicted price of items.
*               Shows using functions and parameters and return values.
****************************************************************************/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/* Function:    inflation
* Description: Prompts the user for the old and new prices of an item and
*              calculates the rate of inflation: (new - old) / old
* Parameters:  None
* Returns:     a double representing the rate of inflation
*/

//************* INSERT INFLATION CODE HERE! *******************
double inflation()
{
	double oldPrice;
	double newPrice;
	double priceInflation;

	cout << "Enter the old price of the item: $";
	cin >> oldPrice;
	cout << "Enter the new price of the item: $";
	cin >> newPrice;

	priceInflation = (newPrice - oldPrice) / oldPrice;
	return priceInflation;
}

/* Function:    projection
* Description: Calculates and displays the future price of an item:
*              future price = price * (pow( 1 + rate, years))
* Parameters:  current price, interest rate, and number of years
* Returns:     nothing
*/
void projection(double curPrice, double rate, int years)
{
	//************* INSERT PROJECTION CODE HERE! *******************
	double futurePrice = curPrice * (pow(1 + rate, years));
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "The future price of item will be $" << futurePrice << endl;
}

//************* INSERT PRESENT VALUE FUNCTION PLUS CODE HERE! *******************
void presentValue(double targetAmount, double rate, int years, double &PV) {
	PV = targetAmount / pow(1 + rate, years);
}


/* Function:    main
* Description: Displays a menu of options to the user and then calls functions
*              to do the appropriate calculations.  Repeats until the user quits.
*/
int main()
{
	int choice;  // variable to store the user's menu choice
	double rate = 0.0,		// interest rate to be used for future and present value
		currentPrice,		// current amount of money to invest
		targetValue = 0.0,	// target amount for present value
		PV;					// present value to be calculated.
	int years;
	// keep displaying the menu until the user elects to quit
	do
	{
		// display menu and get choice
		cout << "Please pick a menu option:\n"
			<< "1) Calculate Inflation\n"
			<< "2) Calculate Projected Price\n"
			<< "3) Calculate the Present Value\n"
			<< "4) Quit\n";
		cin >> choice;

		// handle the different menu options
		switch (choice)	{
		case 1:
			rate = inflation();
			cout.setf(ios::fixed);
			cout.precision(2);
			cout << "The rate of inflation is " << rate << " or " << (rate * 100) << "%\n\n";
			break;
		case 2:
			cout << "Enter the current price of the item: $";
			cin >> currentPrice;
			cout << "Enter the rate of inflation (in decimals): ";
			cin >> rate;
			cout << "Enter the number of years until you purchase the item: ";
			cin >> years;
			projection(currentPrice, rate, years);
			
			break;
		case 3:
			cout << "Enter the amount of money after investment: $";
			cin >> targetValue;
			cout << "Enter the interest rate (in decimals): ";
			cin >> rate;
			cout << "Enter the number of years for investment: ";
			cin >> years;
			presentValue(targetValue, rate, years, PV);
			cout << "The present value = $" << PV << endl;
			break;
		case 4:
			break;
		default:
			cout << "Invalid choice, please try again!\n\n";
		}

	} while (choice != 4);

	system("PAUSE");
}
