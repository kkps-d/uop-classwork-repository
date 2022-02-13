#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <vector>
#include "Bank.h"

using namespace std;

// Used to track account numbers
int Bank::nextAccount = 10000;
int Bank::nextSaving = 1000;
int Bank::nextChecking = 6000;

// Changes color of text
void colored(string input, WORD color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << input;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// Rejects non-integer input
int intChecker() {
	int input;
	cin >> input;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			colored("Invalid character. Please enter again: ", 4);
			cin >> input;
		}
	} while (cin.fail());
	cin.ignore();
	return input;
}

// Rejects empty string
string strChecker() {
	string input;
	cin.clear();
	getline(cin, input);
	while (input.length() == 0)
	{
		colored("String cannot be empty! Please try again: ", 4);
		getline(cin, input);
	}
	return input;
}

// Rejects non-number input
double doubleChecker() {
	double input;
	cin >> input;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			colored("Invalid character. Please enter again: ", 4);
			cin >> input;
		}
	} while (cin.fail());
	cin.ignore();
	return input;
}

// Partitioning vector into low and high when quicksorting
template <typename T>
int Partition(vector<T>& arr, int i, int k) {
	int l = 0;
	int h = 0;
	int midpoint = 0;
	double pivot = 0;
	T temp;
	bool done = false;
	pivot = arr.at(i).getBalance();

	midpoint = i + (k - i) / 2;
	l = i;
	h = k;

	while (!done) {
		while (arr.at(l).getBalance() < pivot)
		{
			++l;
		}

		while (pivot > arr.at(h).getBalance()) {
			--h;
		}

		if (l >= h)
		{
			done = true;
		}
		else
		{
			temp = arr.at(l);
			arr.at(l) = arr.at(h);
			arr.at(h) = temp;
			++l;
			--h;
		}
	}
	return h;
}

// Sorts things by balance in desc. order
template <typename T>
void Quicksort(vector<T>& arr, int i, int k) {
	int j = 0;
	if (i >= k)
	{
		return;
	}

	j = Partition(arr, i, k);
	Quicksort(arr, i, j);
	Quicksort(arr, j + 1, k);
}

Bank::Bank(string name, string address, string workingHrs){
	this->name = name;
	this->address = address;
	this->workingHrs = workingHrs;
}

void Bank::displayMenu() {
	system("cls");
	cout << endl;
	colored("Eligible services for " + name + "\n\n", 3);
	cout << setw(5) << setfill(' ') << " " << "1. Show number of Bank Accounts" << endl;
	cout << setw(5) << setfill(' ') << " " << "2. Show number of Saving Sub-accounts" << endl;
	cout << setw(5) << setfill(' ') << " " << "3. Show number of Checking Sub-accounts" << endl;
	cout << setw(5) << setfill(' ') << " " << "4. Open Bank Account" << endl;
	cout << setw(5) << setfill(' ') << " " << "5. Close Bank Account" << endl;
	cout << setw(5) << setfill(' ') << " " << "6. Modify Bank Account" << endl;
	cout << setw(5) << setfill(' ') << " " << "7. Show detailed info on Bank Accounts" << endl;
	cout << setw(5) << setfill(' ') << " " << "8. Show brief of Bank Accounts in descending order of aggregated balance" << endl << endl;
}

// Creates an account
void Bank::createAccount() {
	int choice;
	bool validChoice, createChoice;
	string first, last, SSN;

	do
	{
		system("cls");
		cout << endl;
		colored("Create new account \n\n", 3);
		colored("Enter First Name: ", 6);
		first = strChecker();
		colored("Enter Last Name: ", 6);
		last = strChecker();
		colored("Enter SSN: ", 6);
		SSN = strChecker();

		system("cls");
		cout << endl;
		colored("Create new account \n\n", 3);
		cout << "Do you want to create an account with the following information?" << endl << endl;
		cout << setw(5) << setfill(' ') << "| " << first << endl << setw(5) << setfill(' ') << "| " << last << endl << setw(5) << setfill(' ') << "| " << SSN << endl << endl;
		colored("1. Yes", 2);
		cout << endl;
		colored("2. No", 4);
		cout << endl << endl;
		colored("Enter your choice: ", 6);
		choice = intChecker();
		do
		{
			switch (choice)
			{
				case 1:
					createChoice = true;
					validChoice = true;
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
	
	accounts.push_back(Account(first, last, SSN));

	system("cls");
	cout << endl;
	colored("Create new account \n\n", 3);
	colored("Account for " + first + " " + last + " has been created!\n\n", 2);
	system("pause");
	manageAccount("BNK" + to_string(nextAccount - 1));	// Manages newly created account
}

// Finds the specified account and returns index to account in account vector
int Bank::findAccount(string& accNum) {
	int mid = 0;
	int low = 0;
	int high = 0;
	int currAcc = 0;
	string clean;

	high = accounts.size() - 1;

	clean.clear();
	for (auto elm : accNum) {
		if (elm >= '0' && elm <= '9')
		{
			clean.push_back(elm);
		}
	}
	accNum = clean;

	int key;
	if (accNum.size() == 0)
	{
		accNum = "BNK" + accNum;	// Just so that the user can see what account is being deleted in format BNK10000, purely cosmetic
		return -1;
	}
	else
	{
		key = stoi(accNum);
	}	
	
	accNum = "BNK" + accNum;	// Just so that the user can see what account is being deleted in format BNK10000, purely cosmetic

	while (high >= low)
	{
		mid = (high + low) / 2;
		currAcc = accounts.at(mid).getAccNumint();
		if (currAcc < key)
		{
			low = mid + 1;
		}
		else if (currAcc > key)
		{
			high = mid - 1;
		}
		else
		{
			return mid;
		}
	}

	return -1;
}


void Bank::manageAccount(string accNum) {
	int choice;
	int index = findAccount(accNum);

	if (index != -1)
	{
		while (true)
		{
			accounts.at(index).displayMenu();
			colored("Enter your choice: ", 6);
			do
			{
				choice = intChecker();
				switch (choice)
				{
				case 1:
					accounts.at(index).createSaving();
					break;
				case 2:
					accounts.at(index).createChecking();
					break;
				case 3:
					accounts.at(index).modifySubAccount();
					break;
				case 4:
					accounts.at(index).closeSubAccount();
					break;
				case 5:
					accounts.at(index).showDetailed();
					break;
				case 6:
					accounts.at(index).showBrief();
					break;
				case 7:
					return;
					break;
				default:
					colored("Invalid choice. Please enter again: ", 4);
					break;
				}
			} while (!(choice >= 1 && choice <= 7));
		}
	}
	else {
		system("cls");
		cout << endl;
		colored("Eligible services for " + accounts.at(index).getAccNum() + "\n\n", 3);
		colored(accNum + " not found!\n\n", 4);
		system("pause");
	}
}

void Bank::showTotalAccounts() {
	system("cls");
	cout << endl;
	colored("Number of bank accounts\n\n", 3);
	cout << "There are currently " << accounts.size() << " bank accounts." << endl << endl;
	system("pause");
}

void Bank::showTotalSavings() {
	int total = 0;
	for (auto elm : accounts) {
		total += elm.getNumOfSavings();
	}
	system("cls");
	cout << endl;
	colored("Number of saving sub-accounts\n\n", 3);
	cout << "There are currently " << total << " saving sub-accounts" << endl << endl;
	system("pause");
}

void Bank::showTotalCheckings() {
	int total = 0;
	for (auto elm : accounts) {
		total += elm.getNumOfCheckings();
	}
	system("cls");
	cout << endl;
	colored("Number of checking sub-accounts\n\n", 3);
	cout << "There are currently " << total << " checking sub-accounts" << endl << endl;
	system("pause");
}

void Bank::deleteAccount() {
	string temp;
	int location;
	int choice;

	system("cls");
	cout << endl;
	colored("Close bank account\n\n", 3);

	if (accounts.size() == 0) {
		colored("There are no accounts!\n\n", 14);
		system("pause");
		return;
	}

	while (true)
	{
		system("cls");
		cout << endl;
		colored("Close bank account\n\n", 3);
		for (auto elm : accounts)
		{
			cout << setw(5) << setfill(' ') << "| " << elm.getAccNum() << endl;
		}
		cout << endl;
		colored("Enter the account you wish to delete, leave blank to cancel: ", 6);
		getline(cin, temp);
		cin.clear();
		if (temp.size() == 0)
		{
			return;
		}
		system("cls");
		cout << endl;
		colored("Close bank account\n\n", 3);
		location = findAccount(temp);
		if (location == -1)
		{
			system("cls");
			cout << endl;
			colored("Close bank account\n\n", 3);
			colored("That account does not exist!\n\n", 4);
			system("pause");
		}
		else
		{
			cout << "Are you sure you want to delete " << temp << " ?" << endl << endl;
			colored("1. Yes", 2);
			cout << endl;
			colored("2. No", 4);
			cout << endl << endl;
			colored("Enter your choice: ", 6);
			while (true) {
				choice = intChecker();
				switch (choice)
				{
				case 1:
					accounts.erase(accounts.begin() + location);
					system("cls");
					cout << endl;
					colored("Close bank account\n\n", 3);
					colored(temp + " has been deleted!\n\n", 2);
					system("pause");
					return;
				case 2:
					return;
				default:
					colored("Invalid choice. Please try again: ", 4);
					break;
				}
			}
		}
	}
	
}

void Bank::modifyAccount() {
	string temp;
	int location;

	system("cls");
	cout << endl;
	colored("Modify bank account\n\n", 3);

	if (accounts.size() == 0) {
		colored("There are no accounts!\n\n", 14);
		system("pause");
		return;
	}

	while (true)
	{
		system("cls");
		cout << endl;
		colored("Modify bank account\n\n", 3);
		for (auto elm : accounts)
		{
			cout << setw(5) << setfill(' ') << "| " << elm.getAccNum() << endl;
		}
		cout << endl;
		colored("Enter the account you wish to modify, leave blank to cancel: ", 6);
		getline(cin, temp);
		cin.clear();
		if (temp.size() == 0)
		{
			return;
		}
		location = findAccount(temp);
		if (location == -1)
		{
			system("cls");
			cout << endl;
			colored("Modify bank account\n\n", 3);
			colored("That account does not exist!\n\n", 4);
			system("pause");
		}
		else
		{
			manageAccount(temp);	// Displays the menu of the account selected
			break;
		}
	}
}

// Shows detailed info of bank and all accounts
void Bank::showDetailed() {
	system("cls");
	cout << endl;
	colored("Detailed info\n\n", 3);

	cout << name << endl;
	cout << address << endl;
	cout << workingHrs << endl;
	cout << accounts.size() << " bank ";
	if (accounts.size() == 1)
	{
		cout << "account";
	}
	else
	{
		cout << "accounts";
	}
	cout << endl << endl;
	for (auto elm : accounts) {
		elm.printDetail();
		cout << endl;
	}
	cout << endl;
	system("pause");
}

// Shows brief info with aggregated balance sorted in desc. order
void Bank::showBrief() {
	double bankTotal = 0;
	for (auto elm : accounts) {
		bankTotal += elm.totalBalance();
	}

	system("cls");
	cout << endl;
	colored("Brief info\n\n", 3);

	cout << name << endl;
	cout << address << endl;
	cout << workingHrs << endl << endl;
	cout << "Aggregated Balance: " << bankTotal << endl;
	cout << setprecision(2) << fixed << accounts.size() << " bank ";
	if (accounts.size() == 1)
	{
		cout << "account";
	}
	else
	{
		cout << "accounts";
	}
	cout << endl;
	for (auto elm : accounts) {
		cout << setw(5) << setfill(' ') << " " << "|- " << elm.getAccNum() << " - " << elm.getNumOfCheckings() + elm.getNumOfSavings() << " sub-accounts - Aggregated balance: " << elm.totalBalance() << endl;
	}
	cout << endl;
	system("pause");
}

Account::Account(string firstName, string lastName, string SSN) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->SSN = SSN;
	accNum = Bank::nextAccount;
	firstSaving = true;
	Bank::nextAccount++;
}

// Returns accNum with prefix BNK
string Account::getAccNum() {
	return "BNK" + to_string(accNum);
}

// Returns accNum without prefix BNK
int Account::getAccNumint() {
	return accNum;
}

void Account::displayMenu() {
	system("cls");
	cout << endl;
	colored("Eligible services for " + getAccNum() + "\n\n", 3);
	cout << setw(5) << setfill(' ') << " " << "1. Open Saving sub-account" << endl;
	cout << setw(5) << setfill(' ') << " " << "2. Open Checking sub-account" << endl;
	cout << setw(5) << setfill(' ') << " " << "3. Modify a sub-account" << endl;
	cout << setw(5) << setfill(' ') << " " << "4. Close a sub-account" << endl;
	cout << setw(5) << setfill(' ') << " " << "5. Show detailed account info with sub-accounts sorted in descending order" << endl;
	cout << setw(5) << setfill(' ') << " " << "6. Show brief account info" << endl;
	cout << setw(5) << setfill(' ') << " " << "7. Exit" << endl << endl;
}

void Account::createSaving() {
	Saving temp;
	temp.init();	// Initializes sub-account, different for saving and checking
	if (firstSaving == true)	// 100 Bonus for first saving account
	{
		temp.setBalance(temp.getBalance() + 100);
		firstSaving = false;
	}
	savings.push_back(temp);
}

void Account::createChecking() {
	Checking temp;
	temp.init();
	checkings.push_back(temp);
}

int Account::getNumOfSavings() {
	return savings.size();
}

int Account::getNumOfCheckings() {
	return checkings.size();
}

// cleans up accNum and selects whether it's finding in savings or checkings vector
// temp = temporary input, clean = ouput with only numbers, no prefixes, mode = CHK or SAV, selects which vector to search
int Account::preFindSubAccount(string temp, string& clean, string& mode) {
	int key;
	
	clean.clear();
	for (auto elm : temp) {
		if (elm >= '0' && elm <= '9')
		{
			clean.push_back(elm);
		}
	}
	key = stoi(clean);

	if (key >= 1000 && key <= 5999)	// Savings
	{
		mode = "SAV";
		return findSubAccount(key, savings);
	}
	else if (key >= 6000 && key <= 9999) // Checkings
	{
		mode = "CHK";
		return findSubAccount(key, checkings);
	}
	else
	{
		return -1;
	}
}

// finds sub-accounts according to accNum
template <typename T>
int Account::findSubAccount(int key, vector<T>& subAccs) {
	int mid = 0;
	int low = 0;
	int high = subAccs.size() - 1;
	int currAcc;

	while (high >= low) {
		mid = (high + low) / 2;
		currAcc = subAccs.at(mid).getAccNumint();
		if (currAcc < key)
		{
			low = mid + 1;
		}
		else if (currAcc > key)
		{
			high = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

// Displays sub-accounts
void Account::showSubAccounts() {
	cout << "Saving accounts" << endl;
	if (savings.size() != 0)
	{
		for (auto elm : savings) {
			cout << setw(5) << setfill(' ') << "| " << elm.getAccNum() << endl;
		}
	}
	else
	{
		cout << "There are no saving accounts." << endl;
	}
	cout << endl;
	cout << "Checking accounts" << endl;
	if (checkings.size() != 0)
	{
		for (auto elm : checkings) {
			cout << setw(5) << setfill(' ') << "| " << elm.getAccNum() << endl;
		}
	}
	else
	{
		cout << "There are no checking accounts." << endl;
	}
	cout << endl;
}

void Account::modifySubAccount() {
	string temp;
	string clean;
	string mode;
	int location;

	system("cls");
	cout << endl;
	colored("Modify sub-account\n\n", 3);

	if (savings.size() == 0 && checkings.size() == 0) {
		colored("There are no accounts!\n\n", 14);
		system("pause");
		return;
	}

	while (true)
	{
		system("cls");
		cout << endl;
		colored("Modify sub-account\n\n", 3);
		showSubAccounts();
		colored("Enter the account you wish to modify, leave blank to cancel: ", 6);
		getline(cin, temp);
		cin.clear();
		if (temp.size() == 0)
		{
			return;
		}
		
		// temp = temporary input, clean = ouput with only numbers, no prefixes, mode = CHK or SAV, selects which vector to search
		location = preFindSubAccount(temp, clean, mode);
		// location = index to sub-account in either vectors, -1 means not found

		if (location != -1)
		{
			if (mode == "SAV")
			{
				savings.at(location).manage();
			}
			else if (mode == "CHK")
			{
				checkings.at(location).manage();
			}
			return;
		}
		else {
			system("cls");
			cout << endl;
			colored("Modify sub-account\n\n", 3);
			colored("Account does not exist!\n\n", 4);
			system("pause");
		}
		
	}

}

void Account::closeSubAccount() {
	string temp;
	string clean;
	string mode;
	int location;

	system("cls");
	cout << endl;
	colored("Close sub-account\n\n", 3);

	if (savings.size() == 0 && checkings.size() == 0) {
		colored("There are no accounts!\n\n", 14);
		system("pause");
		return;
	}

	while (true)
	{
		system("cls");
		cout << endl;
		colored("Close sub-account\n\n", 3);
		showSubAccounts();
		colored("Enter the account you wish to close, leave blank to cancel: ", 6);
		getline(cin, temp);
		cin.clear();
		if (temp.size() == 0)
		{
			return;
		}

		location = preFindSubAccount(temp, clean, mode);

		if (location != -1)
		{
			if (mode == "SAV")
			{
				savings.erase(savings.begin() + location);
			}
			else if (mode == "CHK")
			{
				checkings.erase(checkings.begin() + location);
			}
			system("cls");
			cout << endl;
			colored("Close sub-account\n\n", 3);
			colored(mode + clean + " has been closed!\n\n", 2);
			system("pause");
			return;
		}
		else {
			system("cls");
			cout << endl;
			colored("Modify sub-account\n\n", 3);
			colored("Account does not exist!\n\n", 4);
			system("pause");
		}

	}
}

double Account::totalBalance() {
	double totalBal = 0;
	for (auto elm : savings) {
		totalBal += elm.getBalance();
	}
	for (auto elm : checkings) {
		totalBal += elm.getBalance();
	}
	return totalBal;
}

// Prints detailed info of the account to be displayed in Bank::showDetailed();
void Account::printDetail() {
	double totalBal = totalBalance();
	int totalSubs = savings.size() + checkings.size();
	
	cout << "Account BNK" + to_string(accNum) << endl;
	cout << setw(5) << setfill(' ') << " " << "|- Full Name: " << firstName << " " << lastName << endl;
	cout << setw(5) << setfill(' ') << " " << "|- SSN: " << SSN << endl;
	cout << setw(5) << setfill(' ') << " " << "|- Aggregated Balance: " << setprecision(2) << fixed << totalBal << endl;
	

	if (totalSubs != 0)
	{
		cout << setw(5) << setfill(' ') << " " << "|- " << totalSubs << " sub-accounts" << endl;
		if (savings.size() == 0)
		{
			cout << setw(7) << setfill(' ') << " " << "|- No saving accounts " << endl;
		}
		else
		{
			cout << setw(7) << setfill(' ') << " " << "|- Savings " << endl;
			for (auto elm : savings) {
				cout << setw(9) << setfill(' ') << " " << "|- " << elm.getAccNum() << " - " << setprecision(2) << fixed << elm.getBalance() << endl;
			}
		}
		if (checkings.size() == 0)
		{
			cout << setw(7) << setfill(' ') << " " << "|- No checking accounts " << endl;
		}
		else
		{
			cout << setw(7) << setfill(' ') << " " << "|- Checkings " << endl;
			for (auto elm : checkings) {
				cout << setw(9) << setfill(' ') << " " << "|- " << elm.getAccNum() << " - " << setprecision(2) << fixed << elm.getBalance() << " out of " << setprecision(2) << fixed << elm.getMaxAmt() << " - " << elm.getLockedStatus() << endl;
			}
		}
	}
	else
	{
		cout << setw(5) << setfill(' ') << " " << "|- No sub-accounts" << endl;
	}
}

// Prints detailed info of the sub-accounts sorted by aggregated balance of sub-account in desc. order
void Account::showDetailed() {
	vector<Saving> tempSav = savings;
	vector<Checking> tempChk = checkings;

	system("cls");
	cout << endl;
	colored("Show sub-account details in descending order\n\n", 3);
	if (savings.size() != 0)
	{
		cout << "Saving accounts" << endl;
		Quicksort(tempSav, 0, tempSav.size() - 1);
		for (auto elm : tempSav)
		{
			elm.printDetail();
		}
		cout << endl;
	}
	else
	{
		cout << "There are no saving accounts." << endl << endl;
	}
	if (checkings.size() != 0)
	{
		cout << "Checking accounts" << endl;
		Quicksort(tempChk, 0, tempChk.size() - 1);
		for (auto elm : tempChk)
		{
			elm.printDetail();
		}
		cout << endl;
	}
	else
	{
		cout << "There are no checking accounts." << endl << endl;
	}
	system("pause");
}

// Prints detailed info of the sub-accounts
void Account::showBrief() {
	double totalBal = 0;
	system("cls");
	cout << endl;
	colored("Show sub-account brief\n\n", 3);
	cout << "Bank account: BNK" + to_string(accNum) << endl;
	cout << setw(5) << setfill(' ') << "|- " << "Total sub-accounts: " << savings.size() + checkings.size() << endl;
	for (auto elm : savings) {
		totalBal += elm.getBalance();
	}
	for (auto elm : checkings) {
		totalBal += elm.getBalance();
	}
	cout << setw(5) << setfill(' ') << "|- " << "Aggregated balance: " << totalBal << endl << endl;
	system("pause");
}

SubAccount::SubAccount() {
	balance = 0;
}

int SubAccount::getAccNumint() {
	return accNum;
}

double SubAccount::getBalance() {
	return balance;
}

void SubAccount::setBalance(double balance) {
	this->balance = balance;
}

void SubAccount::deposit() {
	double bal;
	system("cls");
	cout << endl;
	colored("Deposit to sub-account \n\n", 3);
	colored("Current balance: " + to_string(balance) + "\n\n", 3);
	colored("Enter amount to deposit. Enter 0 to cancel: ", 6);
	bal = doubleChecker();
	if (bal == 0)
	{
		return;
	}
	else {
		system("cls");
		cout << endl;
		colored("Deposit to sub-account \n\n", 3);
		balance += bal;
		colored("Current balance: " + to_string(balance) + "\n\n", 3);
		colored(to_string(bal) + " has been successfully deposited into your sub-account!\n\n", 2);
		system("pause");
	}
	return;
}

void SubAccount::withdraw() {
	double bal;
	system("cls");
	cout << endl;
	colored("Withdraw from sub-account \n\n", 3);
	colored("Current balance: " + to_string(balance) + "\n\n", 3);
	colored("Enter amount to withdraw. Enter 0 to cancel: ", 6);
	do
	{
		bal = doubleChecker();
		if (bal == 0)
		{
			return;
		}
		else if (bal > balance)
		{
			colored("You cannot withdraw more than your balance! Please try again: ", 4);
		}
		else
		{
			balance -= bal;
			system("cls");
			cout << endl;
			colored("Withdraw from sub-account \n\n", 3);
			colored("Current balance: " + to_string(balance) + "\n\n", 3);
			colored(to_string(bal) + " has been successfully withdrawn from your account!\n\n", 2);
			system("pause");
			return;
		}
	} while (bal > balance);
}

// Initializes sub-account with balance etc, slightly different for checkings sub-account
void SubAccount::init() {
	colored("Enter the initial balance for this account: ", 6);
	balance = doubleChecker();
}

Saving::Saving() {
	accNum = Bank::nextSaving;
	Bank::nextSaving++;
}

string Saving::getAccNum() {
	return "SAV" + to_string(accNum);
}

// Displays services for sub-accounts, slightly different for checkings
void Saving::manage() {
	int choice;
	bool validChoice = false;
	while (true)
	{
		system("cls");
		cout << endl;
		colored("Managing SAV" + to_string(accNum) + "\n", 3);
		colored("Balance: " + to_string(balance) + "\n\n", 3);
		cout << setw(5) << setfill(' ') << "| " << "1. Deposit" << endl;
		cout << setw(5) << setfill(' ') << "| " << "2. Withdraw" << endl;
		cout << setw(5) << setfill(' ') << "| " << "3. Exit" << endl << endl;
		do
		{
			cout << "Enter your choice: ";
			choice = intChecker();

			switch (choice)
			{
			case 1:
				deposit();
				validChoice = true;
				break;
			case 2:
				withdraw();
				validChoice = true;
				break;
			case 3:
				return;
			default:
				colored("Invalid choice. Please enter again: ", 4);
				choice = intChecker();
				break;
			}
		} while (validChoice == false);
	}
}

// Prints detailed info of the sub-account to be displayed in Account::showDetailed();
void Saving::printDetail() {
	cout << setw(5) << setfill(' ') << "|- " << "SAV" + to_string(accNum) << endl;
	cout << setw(7) << setfill(' ') << "|- " << "Balance: " << balance << endl;
}

// Same function with sub-account, just added cosmetic stuff
void Saving::init() {
	system("cls");
	cout << endl;
	colored("Create Saving sub-account \n\n", 3);
	SubAccount::init();
	system("cls");
	cout << endl;
	colored("Create Saving sub-account \n\n", 3);
	colored("Saving account SAV" + to_string(accNum) + " has been created successfully\n\n", 2);
	system("pause");
}

Checking::Checking() {
	accNum = Bank::nextChecking;
	maxAmt = 0;
	locked = false;
	Bank::nextChecking++;
}

string Checking::getAccNum() {
	return "CHK" + to_string(accNum);
}

// Displays services for sub-accounts, more options added for checkings e.g. max balance, lock
void Checking::manage() {
	int choice;
	bool validChoice = false;

	while (true)
	{
		system("cls");
		cout << endl;
		colored("Managing CHK" + to_string(accNum) + "\n", 3);
		colored("Balance: " + to_string(balance) + "\n\n", 3);
		cout << setw(5) << setfill(' ') << "| " << "1. Deposit" << endl;
		cout << setw(5) << setfill(' ') << "| " << "2. Withdraw" << endl;
		cout << setw(5) << setfill(' ') << "| " << "3. Set maximum balance (Currently = " << maxAmt << ")" << endl;
		cout << setw(5) << setfill(' ') << "| " << "4. Lock/Unlock account (Currently = ";
		if (locked == true)
		{
			colored("Locked", 3);
		}
		else
		{
			colored("Unlocked", 14);
		}
		cout << ")" << endl;
		cout << setw(5) << setfill(' ') << "| " << "5. Exit" << endl << endl;
		do
		{
			colored("Enter your choice: ", 6);
			choice = intChecker();

			switch (choice)
			{
			case 1:
				if (locked == true)	// Blocks this action when account is locked
				{
					system("cls");
					cout << endl;
					colored("Managing CHK" + to_string(accNum) + "\n", 3);
					colored("Balance: " + to_string(balance) + "\n\n", 3);
					colored("Action not allowed! Sub-account is locked.\n\n", 4);
					system("pause");
				}
				else
				{
					deposit();
				}	
				validChoice = true;
				break;
			case 2:
				if (locked == true)	// Blocks this action when account is locked
				{
					system("cls");
					cout << endl;
					colored("Managing CHK" + to_string(accNum) + "\n", 3);
					colored("Balance: " + to_string(balance) + "\n\n", 3);
					colored("Action not allowed! Sub-account is locked.\n\n", 4);
					system("pause");
				}
				else
				{
					withdraw();
				}
				validChoice = true;
				break;
			case 3:
				if (locked == true)	// Blocks this action when account is locked
				{
					system("cls");
					cout << endl;
					colored("Managing CHK" + to_string(accNum) + "\n", 3);
					colored("Balance: " + to_string(balance) + "\n\n", 3);
					colored("Action not allowed! Sub-account is locked.\n\n", 4);
					system("pause");
				}
				else
				{
					setMax();
				}
				validChoice = true;
				break;
			case 4:
				toggleLock();
				validChoice = true;
				break;
			case 5:
				return;
			default:
				colored("Invalid choice. Please enter again: ", 4);
				choice = intChecker();
				break;
			}
		} while (validChoice == false);
	}
}

// Changes max amount for checking sub-account
void Checking::setMax() {
	double temp;
	system("cls");
	cout << endl;
	colored("Set maximum balance \n\n", 3);
	cout << "Current maximum balance: " << maxAmt << endl;
	colored("Enter new maximum balance. Enter 0 to cancel: ", 6);
	while (true)
	{
		temp = doubleChecker();
		if (temp == 0)
		{
			return;
		}
		else if (temp < balance)
		{
			colored("The maximum cannot be less than the balance! Please try again: ", 4);
		}
		else {
			maxAmt = temp;
			system("cls");
			cout << endl;
			colored("Set maximum balance \n\n", 3);
			colored("The maximum balance for this account has been updated to " + to_string(temp) + "!\n\n", 2);
			system("pause");
			return;
		}
	}
}

// Changes lock status for checking sub-account
void Checking::toggleLock() {
	if (locked == true)
	{
		locked = false;
	}
	else
	{
		locked = true;
	}
	return;
}

void Checking::deposit() {
	double bal;
	system("cls");
	cout << endl;
	colored("Deposit to sub-account \n\n", 3);
	colored("Current balance: " + to_string(balance) + "\n\n", 3);
	colored("Enter amount to deposit. Enter 0 to cancel: ", 6);
	while (true)
	{
		bal = doubleChecker();
		if (bal == 0)
		{
			return;
		}
		else if ((balance + bal) <= maxAmt) {
			system("cls");
			cout << endl;
			colored("Deposit to sub-account \n\n", 3);
			balance += bal;
			colored("Current balance: " + to_string(balance) + "\n\n", 3);
			colored(to_string(bal) + " has been successfully deposited into your sub-account!\n\n", 2);
			system("pause");
			return;
		}
		else
		{
			colored("Your updated balance will exceed the maximum! Please try again: ", 4);
		}
	}
	
}

double Checking::getMaxAmt() {
	return maxAmt;
}

string Checking::getLockedStatus() {
	switch (locked)
	{
	case true:
		return "Locked";
	case false:
		return "Unlocked";
	}
}

// Prints detailed info of the account to be displayed in Bank::showDetailed();
void Checking::printDetail() {
	cout << setw(5) << setfill(' ') << "|- " << "CHK" + to_string(accNum) << endl;
	cout << setw(7) << setfill(' ') << "|- " << "Balance: " << balance << endl;
	cout << setw(7) << setfill(' ') << "|- " << "Maximum Balance: " << maxAmt << endl;
	cout << setw(7) << setfill(' ') << "|- " << "Status - ";
	if (locked == true)
	{
		cout << "Locked" << endl;
	}
	else
	{
		cout << "Unlocked" << endl;
	}
}

// Slightly different function with sub-account, added lock status, max amt and cosmetic stuff
void Checking::init() {
	char temp;
	bool valid = false;
	system("cls");
	cout << endl;
	colored("Create Checking sub-account \n\n", 3);
	SubAccount::init();
	colored("Enter the maximum capacity of the account: ", 6);
	do
	{
		maxAmt = doubleChecker();
		if (maxAmt < balance)
		{
			colored("The maximum capacity cannot be higher than the balance! Please try again: ", 4);
		}
	} while (maxAmt < balance);

	colored("Do you want to lock the account?(Y/N): ", 6);
	while (!valid)
	{
		cin >> temp;
		cin.clear();
		switch (temp)
		{
		case 'y':
		case 'Y':
			locked = true;
			valid = true;
			break;
		case 'n':
		case 'N':
			locked = false;
			valid = true;
			break;
		default:
			cout << "Invalid choice. Please try again: ";
			break;
		}
	}
	system("cls");
	cout << endl;
	colored("Create Checking sub-account \n\n", 3);
	colored("Saving account CHK" + to_string(accNum) + " has been created successfully\n\n", 2);
	system("pause");
}