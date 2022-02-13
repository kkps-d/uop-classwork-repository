/*
Project 1
Kaung Khant Pyae Sone
*/
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "Bank.h"

using namespace std;

int main() {
	int choice;
	bool validChoice, createChoice, quit = false;
	string name, address, workingHrs;
	
	do
	{
		system("cls");
		cout << endl;
		colored("Bank Setup \n\n", 3);
		colored("Enter the name of the bank: ", 6);
		name = strChecker();	// Rejects empty strings
		colored("Enter the address of the bank: ", 6);
		address = strChecker();
		colored("Enter the working hours: ", 6);
		workingHrs = strChecker();

		system("cls");
		cout << endl;
		colored("Bank Setup \n\n", 3);
		cout << "Do you want to create a bank with the following information?" << endl << endl;
		cout << setw(5) << setfill(' ') << "| " << name << endl << setw(5) << setfill(' ') << "| " << address << endl << setw(5) << setfill(' ') << "| " << workingHrs << endl;
		cout << endl;
		colored("1. Yes", 2);
		cout << endl;
		colored("2. No", 4);
		cout << endl << endl;
		colored("Enter your choice: ", 6);
		choice = intChecker();	// Rejects non number characters

		do
		{
			switch (choice)
			{
			case 1:
				createChoice = true;	// Used to loop bank setup when user chooses no
				validChoice = true;	// Used to loop bank yes no choice if invalid
				break;
			case 2:
				createChoice = false;
				validChoice = true;
				break;
			default:
				validChoice = false;
				colored("Invalid choice. Please enter again: ", 4);
				choice = intChecker();
				break;
			}
		} while (validChoice == false);
	} while (createChoice == false);

	Bank temp(name, address, workingHrs);

	//Bank temp("Student Bank Co.", "3601 Pacific Ave, Stockton CA 95211", "Mon - Fri 11:00am - 3:00pm");

	do
	{
		temp.displayMenu();	// Displays eligible services for a bank
		colored("Enter choice: ", 6);
		do
		{
			choice = intChecker();
			switch (choice)
			{
			case 1:
				temp.showTotalAccounts();	// Shows total accounts
				break;
			case 2:
				temp.showTotalSavings();	// Shows total saving sub-accounts
				break;
			case 3:
				temp.showTotalCheckings();	// Shows total checking sub-accounts
				break;
			case 4:
				temp.createAccount();	// Creates an account
				break;
			case 5:
				temp.deleteAccount();	// Deletes an account
				break;
			case 6:
				temp.modifyAccount();	// Modifies an account
				break;
			case 7:
				temp.showDetailed();	// Shows detailed info of bank and all accounts
				break;
			case 8:
				temp.showBrief();	// Shows brief info with aggregated balance sorted in desc. order
				break;
			default:
				colored("Invalid choice. Please enter again: ", 4);
				break;
			}
		} while (!(choice >= 1 && choice <= 8));
	} while (quit == false);
}