/*
Kaung Khant Pyae Sone
Project 5 - Journal Entry
COMP 051
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ChartOfAccounts
{
public:
	ChartOfAccounts();
	string getaccNum() {
		return accNum;
	}
	string getName() {
		return name;
	}
	string getType() {
		return type;
	}
	float getBalance() {
		return balance;
	}
	void wrtAccNum(string x) {
		accNum = x;
	}
	void wrtName(string x) {
		name = x;
	}
	void wrtType(string x) {
		type = x;
	}
	void wrtBalance(float x) {
		balance = x;
	}
private:
	string accNum;
	string name;
	string type;
	float balance;
};

ChartOfAccounts::ChartOfAccounts()
{
	balance = 0;
}


class TransactionLines
{
public:
	void wrtlineNum(int x) {
		lineNum = x;
	}
	void wrtDebit(float x) {
		debit = x;
	}
	void wrtCredit(float x) {
		credit = x;
	}
	void wrtaccNum(string x) {
		accNum = x;
	}
	int getlineNum() {
		return lineNum;
	}
	float getDebit() {
		return debit;
	}
	float getCredit() {
		return credit;
	}
	string getaccNum() {
		return accNum;
	}
private:
	int lineNum;
	float debit;
	float credit;
	string accNum;
};

class TransactionHeader
{
public:
	TransactionHeader() {
		debitSum = 0;
		creditSum = 0;
		lineCount = 0;
		currLine = 0;
	}
	string getTXN() {
		return txnID;
	}
	void create(string Idate, string Iid, string Imemo) {
		date = Idate;
		txnID = Iid;
		memo = Imemo;
	}
	void insLine(int lineNum, float debit, float credit, string accNum) {
		lines[lineCount].wrtaccNum(accNum);
		lines[lineCount].wrtCredit(credit);
		lines[lineCount].wrtDebit(debit);
		lines[lineCount].wrtlineNum(lineNum);
		debitSum += debit;
		creditSum += credit;
		accountNum = accNum;
		lineCount++;
	}
	void validateEntry(class ChartOfAccounts Accounts[]) {
		int i = 0;
		valid = true;


		/*for (int i = 0; i < 14; i++)
		{
			cout << lines[currLine].getaccNum() << " = " << Accounts[i].getaccNum() << endl;
			if (i != 14)
			{
				if (lines[currLine].getaccNum() == Accounts[i].getaccNum())
				{
					currAcc = i;
					valid = true;
					break;
				}
			}
			else
			{
				cout << "Invalid account number: " << lines[currLine].getaccNum() << endl;
				cout << txnID << " is invalid!" << endl;
				valid = false;
			}
		}

		if (valid == true)
		{
			if (lines[currLine].getCredit() < 0)
			{
				cout << "Credit is negative: " << lines[currLine].getCredit() << endl;
				cout << txnID << " is invalid!" << endl;
				valid = false;
			}
		}

		if (valid == true)
		{
			if (lines[currLine].getDebit() < 0)
			{
				cout << "Debit is negative: " << lines[currLine].getDebit() << endl;
				cout << txnID << " is invalid!" << endl;
				valid = false;
			}
		}

		if (valid == true)
		{
			if (lines[currLine].getCredit() != 0 && lines[currLine].getDebit() != 0)
			{
				cout << "Debit and credit cannot be on the same line!" << endl;
				cout << txnID << " is invalid!" << endl;
				valid = false;
			}
		}

		if (valid == true)
		{
			if (creditSum != debitSum)
			{
				cout << "Credit sum = " << creditSum << " and debit sum = " << debitSum << " are not equal!" << endl;
				cout << txnID << " is invalid!" << endl;
				valid = false;
			}
		}*/
	}

	bool isValid() {
		return valid;
	}

	void updateBalances(class ChartOfAccounts Accounts[]) {
		if (valid == true)
		{
			Accounts[currAcc].wrtBalance(Accounts[currAcc].getBalance() + debitSum - creditSum);
		}
		else
		{
			cout << "Invalid transaction. Balance not updated" << endl;
		}
	}

private:
	string date;
	string txnID;
	string memo;
	bool valid;
	TransactionLines lines[40];
	int lineCount;
	int currLine;
	int currAcc;
	float debitSum;
	float creditSum;
	string accountNum;
};


int main() {
	ChartOfAccounts Accounts[13];

	string accNum;
	string name;
	string type;
	float balance;

	int lineNum;
	string date;
	string memo;
	string txnID;
	float debit;
	float credit;

	TransactionHeader Transactions[20];
	int currTXN = 0;

	ifstream input;
	bool fileError = false;

	// Checks if file exists // 
	input.open("accounts.txt");
	if (input.fail())
	{
		cout << "accounts.txt missing." << endl;
		fileError = true;
	}
	input.close();
	input.clear();

	input.open("journals.txt");
	if (input.fail())
	{
		cout << "journals.txt missing." << endl;
		fileError = true;
	}
	input.close();
	input.clear();

	input.open("pickups.txt");
	if (input.fail())
	{
		cout << "pickups.txt missing." << endl;
		fileError = true;
	}
	input.close();
	input.clear();

	if (fileError == true)
	{
		cout << "Please make sure the above files aren't missing and restart the program" << endl;
		exit(0);
	}
	// --------------------- //

	// Loads chart of accounts into Account array //
	input.open("accounts.txt");
	for (int i = 0; i < 13; i++)
	{
		input >> accNum >> name >> type;
		Accounts[i].wrtAccNum(accNum);
		Accounts[i].wrtName(name);
		Accounts[i].wrtType(type);
	}
	// ------------------------------------------ //


	for (int i = 0; i < 13; i++)
	{
		cout << Accounts[i].getaccNum() << "  " << Accounts[i].getName() << "  " << Accounts[i].getType() << "  " << Accounts[i].getBalance() << endl;
	}
	input.close();
	cout << "opening journals" << endl;
	input.open("journals.txt");

	int loopCount = 0;
	
	while (input >> lineNum)
	{
		if (lineNum == 0 && loopCount != 0)
		{
			currTXN++;
		}
		if (lineNum == 0)
		{
			cout << "Current TXN: " << currTXN << endl;
			input >> date >> memo >> txnID;
			cout << lineNum << "	" << date << "	" << memo << "	" << txnID << endl;
			Transactions[currTXN].create(date, txnID, memo);
		}
		else
		{
			input >> debit >> credit >> accNum;
			cout << lineNum << "	" << debit << "	" << credit << "	" << accNum << endl;
			Transactions[currTXN].insLine(lineNum, debit, credit, accNum);
		}
		loopCount++;
	}
	for (int i = 0; i <= currTXN; i++)
	{
		cout << "Current Transaction: " << Transactions[i].getTXN() << endl;
		Transactions[i].validateEntry(Accounts);
	}
	system("pause");
}