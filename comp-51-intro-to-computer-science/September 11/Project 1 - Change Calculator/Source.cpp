/*
Kaung Khant Pyae Sone
Project 1
COMP 051 - 01
*/

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <Windows.h>

using namespace std;

void setcolor(int value) { //Function for changing text color, i don't get this either
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}
int main() {
	srand((unsigned)time(0)); //Initialize RNG

	string firstName; //First name
	string itemDesc; //Item description
	float itemPrice = rand()%2000 + 1; //Item price randomized
	float amtTendered; //Amount tendered
	float dollarPrice; //Item price in dollars with two decimals
	float dollarTendered; //Amount tendered in dollars with two decimals
	int pluralCheck; //Variable used for plural form
	int amtLeft; //Change remaining
	//Constants to be used for division
	const int moneyDollar = 100;
	const int moneyQuarter = 25;
	const int moneyDime = 10;
	const int moneyNickel = 5;

	cout << "Change calculator by Kaung Khant Pyae Sone" << endl << endl;
	//First name
	cout << "What is the customer's first name?: ";
	setcolor(4);
	cin >> firstName;
	setcolor(7);
	//Item description
	cout << "Enter an item description: ";
	setcolor(4);
	cin >> itemDesc;
	setcolor(7);
	//Item price
	cout << "The price of ";
	setcolor(4);
	cout << itemDesc;
	setcolor(7);
	cout << " (in cents): " << itemPrice << endl;
	//Amount tendered
	do { //Prompt user to enter tender again if tendered amount is less than item's price
		cout << "Enter the amount tendered in cents: ";
		setcolor(4);
		cin >> amtTendered;
		setcolor(7);
		if (amtTendered < itemPrice) {
			cout << "Tendered amount needs to be more than the item's price" << endl;
		}
	} while (amtTendered < itemPrice);
	//Price conversion to be displayed only
	dollarPrice = itemPrice / 100;
	dollarTendered = amtTendered / 100;
	//Confirmation
	cout << firstName << " bought ";
	setcolor(4);
	cout << itemDesc;
	setcolor(7);
	cout << " for ";
	setcolor(19);
	cout << "$" << setprecision(2) << fixed << dollarPrice;
	setcolor(7);
	cout << " and tendered $" << setprecision(2) << fixed << dollarTendered << endl;

	//Check if there is change
	if (amtTendered == itemPrice)
	{
		cout << firstName << " has no change" << endl;
	}
	else
	{
		//Calculating change
		amtLeft = amtTendered - itemPrice;
		cout << firstName << "'s change is: " << endl;

		//Dollar bill calculation
		pluralCheck = amtLeft / moneyDollar; //Calculate how many dollar bills
		if (pluralCheck < 1) {}//Hides the dollar option the change consists of no dollar bills
		else
		{
			setcolor(2);
			cout << setw(6) << pluralCheck; //Print how many one-dollar bills
			setcolor(7);
			if (pluralCheck > 1) //Checking if singular for plural noun is needed
			{
				cout << " one-dollar bills";
			}
			else {
				cout << " one-dollar bill";
			}
			cout << endl;
		}
		amtLeft = amtLeft % moneyDollar; //Calculate remaining cents, put back into variable for another calculation
		//Quarter calculation
		pluralCheck = amtLeft / moneyQuarter;
		if (pluralCheck < 1) {}
		else
		{
			setcolor(2);
			cout << setw(6) << pluralCheck;
			setcolor(7);
			if (pluralCheck > 1)
			{
				cout << " quarters";
			}
			else {
				cout << " quarter";
			}
			cout << endl;
		}
		amtLeft = amtLeft % moneyQuarter;
		//Dime calculation
		pluralCheck = amtLeft / moneyDime;
		if (pluralCheck < 1) {}
		else
		{
			setcolor(2);
			cout << setw(6) << pluralCheck;
			setcolor(7);
			if (pluralCheck > 1)
			{
				cout << " dimes";
			}
			else {
				cout << " dime";
			}
			cout << endl;
		}
		amtLeft = amtLeft % moneyDime;
		//Nickel calculation
		pluralCheck = amtLeft / moneyNickel;
		if (pluralCheck < 1) {}
		else
		{
			setcolor(2);
			cout << setw(6) << pluralCheck;
			setcolor(7);
			if (pluralCheck > 1)
			{
				cout << " nickels";
			}
			else {
				cout << " nickel";
			}
			cout << endl;
		}
		amtLeft = amtLeft % moneyNickel;
		//Penny calculation
		if (amtLeft < 1) {}
		else
		{
			setcolor(2);
			cout << setw(6) << amtLeft;
			setcolor(7);
			if (amtLeft > 1)
			{
				cout << " pennies";
			}
			else
			{
				cout << " penny";
			}
			cout << endl;
		}
	}
	system("pause");
	return 0;
}