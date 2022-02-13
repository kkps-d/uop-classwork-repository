/*
Kaung Khant Pyae Sone
Project 5 - Journal Entry
COMP 051
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Class for chart of accounts
class ChartOfAccounts
{
public:
	// Constructor
	ChartOfAccounts() {
		balance = 0;
		accNum = 0;
	}
	ChartOfAccounts(int accNum, string accName, string type);

	// Returns 4 digit account number
	int getAccNum() {
		return accNum;
	}
	// Returns name of account
	string getName() {
		return name;
	}
	// Returns type of account
	string getType() {
		return type;
	}
	// Returns balance of account
	float getBalance() {
		return balance;
	}
	// Sets 4 digit account number
	void setAccNum(int x) {
		accNum = x;
	}
	// Sets name of account
	void setName(string x) {
		name = x;
	}
	// Sets type of account
	void setType(string x) {
		type = x;
	}
	// Sets balance of account
	void setBalance(float x) {
		balance = x;
	}
private:
	int accNum;
	string name;
	string type;
	float balance;
};

ChartOfAccounts::ChartOfAccounts(int num, string accName, string accType)
{
	accNum = num;
	name = accName;
	type = accType;
	balance = 0;
}

class TransactionLines
{
public:
	// Gets line number
	int getLineNum() {
		return lineNum;
	}
	// Gets debit
	float getDebit() {
		return debit;
	}
	// Gets credit
	float getCredit() {
		return credit;
	}
	// Gets 4-digit account number
	int getAccNum() {
		return accNum;
	}
	// Sets line number
	void setLineNum(int x) {
		lineNum = x;
	}
	// Sets debit
	void setDebit(float x) {
		debit = x;
	}
	// Sets credit
	void setCredit(float x) {
		credit = x;
	}
	// Sets 4-digit account number
	void setAccNum(int x) {
		accNum = x;
	}
private:
	int lineNum;
	float debit;
	float credit;
	int accNum;
};

class TransactionHeader
{
public:
	TransactionHeader();

	// Returns JE transaction id
	string getTransactionID() {
		return transactionID;
	}

	// Code used while debugging
	//void getTransactionHeader(string &TXNDate, string &TXNID, string &TXNMemo) {
	//	TXNDate = transactionDate;
	//	TXNID = transactionID;
	//	TXNMemo = transactionMemo;
	//}
	//int getNumberOfLines() {
	//	return currentLine;
	//}
	//void getTransactionLines(int line, float &debit, float &credit, int &accNum) {
	//	debit = transactionLines[line].getDebit();
	//	credit = transactionLines[line].getCredit();
	//	accNum = transactionLines[line].getAccNum();
	//}

	// Returns sum of debits in an entry
	float getDebitSum() {
		return debitSum;
	}
	// Returns sum of credits in an entry
	float getCreditSum() {
		return creditSum;
	}
	// Creates a transaction header, used when line is 0, includes date, memo and id
	void createTransaction(string TXNDate, string TXNID, string TXNMemo) {
		transactionDate = TXNDate;
		transactionID = TXNID;
		transactionMemo = TXNMemo;
		currentLine = 0;
	}
	// Creates a line under a header, used when line is non zero, includes debit, credit and account number
	void insertLine(int line, float debit, float credit, int accNum) {
		transactionLines[currentLine].setDebit(debit);
		transactionLines[currentLine].setCredit(credit);
		transactionLines[currentLine].setAccNum(accNum);
		debitSum += debit;
		creditSum += credit;
		currentLine++;
	}
	// Validates account number, negative debit and credit, debit and credit non zero on same line, sum of debit and credit inequal
	void validateTransaction(class ChartOfAccounts accounts[]) {

		// Invalid account number
		for (int i = 0; i < currentLine; i++)
		{
			for (int j = 0; j <= 13; j ++)
			{
				if (j < 13)
				{
					if (transactionLines[i].getAccNum() == accounts[j].getAccNum()) // If account number in entry matches with one in chart of accounts, break loop so entryValid remains true
					{
						break;
					}
				}
				else // account number is compared to 13 accounts in chart of entries. If none of them are the same, entryValid = false
				{
					cout << endl;
					cout << "Invalid account number: " << transactionLines[i].getAccNum() << endl;
					cout << transactionID << " is invalid!" << endl;
					entryValid = false;
					break;
				}
			}
		}

		// Negative values
		if (entryValid == true)
		{
			for (int i = 0; i < currentLine; i++)
			{
				if (transactionLines[i].getDebit() < 0) // Checks negative debit
				{
					cout << endl;
					cout << "Invalid debit: " << transactionLines[i].getDebit() << endl;
					cout << transactionID << " is invalid!" << endl;
					entryValid = false;
					break;
				}
				if (transactionLines[i].getCredit() < 0) // Checks negative credit
				{
					cout << endl;
					cout << "Invalid credit: " << transactionLines[i].getCredit() << endl;
					cout << transactionID << " is invalid!" << endl;
					entryValid = false;
					break;
				}
			}
		}

		// Non zero debit and credit on same line
		if (entryValid == true)
		{
			for (int i = 0; i < currentLine; i++)
			{
				if (transactionLines[i].getDebit() != 0 && transactionLines[i].getCredit() != 0)
				{
					cout << endl;
					cout << "Both debit and credit above zero. Debit: " << transactionLines[i].getDebit() << " Credit: " << transactionLines[i].getCredit() << endl;
					cout << transactionID << " is invalid!" << endl;
					entryValid = false;
					break;
				}
			}
		}

		// Unequal sum
		if (entryValid == true)
		{
			if (debitSum != creditSum)
			{
				cout << endl;
				cout << "Sums are not equal. Debit: " << debitSum << " Credit: " << creditSum << endl;
				cout << transactionID << " is invalid!" << endl;
				entryValid = false;
			}
		}
	}
	// Returns if entry is valid or not
	bool isValid() {
		return entryValid;
	}
	// Translates account numbers into array pointer value for chart of accounts array
	int pointerToAccount(int account) {
		switch (account)
		{
		case 1000:
			return 0;
		case 1010:
			return 1;
		case 1020:
			return 2;
		case 1030:
			return 3;
		case 1040:
			return 4;
		case 6000:
			return 5;
		case 6005:
			return 6;
		case 6010:
			return 7;
		case 6020:
			return 8;
		case 6050:
			return 9;
		case 6060:
			return 10;
		case 2000:
			return 11;
		case 4000:
			return 12;
		default:
			return 0;
		}
	}
	// Updates balance for each account
	void updateBalances(class ChartOfAccounts accounts[]) {
		if (entryValid == true)
		{
			for (int i = 0; i < currentLine; i++)
			{
				tempPointer = pointerToAccount(transactionLines[i].getAccNum());	// Gets account number for the line and translates to chart of accounts array pointer
				tempBalance = accounts[tempPointer].getBalance();	// Gets balance of the account number and stores in tempBalance
				tempBalance += transactionLines[i].getDebit();	// Gets debit of the line and adds it to tempBalance
				tempBalance -= transactionLines[i].getCredit();	// Gets credit of the line and subtracts it from tempBalance
				accounts[tempPointer].setBalance(tempBalance);	// Updates the account balance with value from tempBalance
			}
		}
	}

private:
	string transactionDate;	// Transaction Date
	string transactionMemo;	// Transaction Memo
	string transactionID;	// Transaction ID
	float debitSum;	// Sum of debit
	float creditSum;	// Sum of credit
	TransactionLines transactionLines[30];	// Transaction Lines to store debit, credit and account Number
	int currentLine;	// Tracks which line values from journal file is being inserted into, also serves to track number of lines in an entry
	bool entryValid;	// Is this entry valid?	
	int tempPointer;	// Stores pointer value for chart of accounts array
	float tempBalance;	// Stores balance to be updated
};

TransactionHeader::TransactionHeader()
{
	debitSum = 0;
	creditSum = 0;
	currentLine = 0;
	entryValid = true;
}

int main() {
	ChartOfAccounts accounts[13];	// Stores accounts, names, types and balance
	string journalsFile;	// Name of journal file

	TransactionHeader transactions[10];	// Stores transactions and transaction lines
	int currentTransaction = -1;

	ifstream input; // File input stream

	int lineNum;	// Line number in journal file
	string date;	// Date in journal file
	string memo;	// Memo in journal file
	string id;	// JE id in journal file
	float debit;	// Debit in journal file
	float credit;	// Credit in journal file
	int accNum;	// Account number in journal file

	float totalRevenue = 0;
	float totalExpense = 0;

	// Account entries hardcoded (hidden)
	accounts[0] = ChartOfAccounts(1000, "Sales", "Revenue");
	accounts[1] = ChartOfAccounts(1010, "Services", "Revenue");
	accounts[2] = ChartOfAccounts(1020, "Warranties", "Revenue");
	accounts[3] = ChartOfAccounts(1030, "Refunds", "Revenue");
	accounts[4] = ChartOfAccounts(1040, "Shipping", "Revenue");
	accounts[5] = ChartOfAccounts(6000, "Travel", "Expense");
	accounts[6] = ChartOfAccounts(6005, "Meals", "Expense");
	accounts[7] = ChartOfAccounts(6010, "Salaries", "Expense");
	accounts[8] = ChartOfAccounts(6020, "Supplies", "Expense");
	accounts[9] = ChartOfAccounts(6050, "Rent", "Expense");
	accounts[10] = ChartOfAccounts(6060, "Repairs", "Expense");
	accounts[11] = ChartOfAccounts(2000, "Accounts_Receivable", "Balance_Sheet");
	accounts[12] = ChartOfAccounts(4000, "Accounts_Payable", "Balance_Sheet");
	//

	cout << "Project 5 - Simple Journal Generator" << endl;
	cout << "Kaung Khant Pyae Sone" << endl << endl;
	system("dir /b *.txt"); // Displays text files in directory
	
	do // File open fail checker
	{
		cout << "Enter journals file name: ";
		cin >> journalsFile;
		input.open(journalsFile);
		if (input.fail())
		{
			cout << "Opening file failed. ";
		}
	} while (input.fail());

	system("cls");
	cout << "Opening " << journalsFile << endl;

	while (input >> lineNum) // Reads data from journals file
	{
		if (lineNum == 0)	// Creates header when line number is 0
		{
			currentTransaction++;
			input >> date >> memo >> id;
			transactions[currentTransaction].createTransaction(date, id, memo);
		}
		if (lineNum != 0)	// Inserts lines when line number is non zero
		{
			input >> debit >> credit >> accNum;
			transactions[currentTransaction].insertLine(lineNum, debit, credit, accNum);
			// Shows a warning because currentTransaction starts at -1 to offset currentTransaction++ for the first entry
			// when line number inside the journal file is 0
		}
	}

	// Validate
	cout << endl << "Validating Journals: ";
	for (int i = 0; i <= currentTransaction; i++)
	{
		transactions[i].validateTransaction(accounts);
	}

	// Update
	cout << endl << "Updating Balances..." << endl;
	for (int i = 0; i <= currentTransaction; i++)
	{
		transactions[i].updateBalances(accounts);
	}
	
	cout << "Simple Income Statement: " << endl;
	cout << "Acct#" << setw(12) << "Account" << setw(10) << "Balance" << endl;

	// Display Revenue
	for (int i = 0; i < 5; i++)
	{
		cout << accounts[i].getAccNum() << setw(13) << accounts[i].getName() << setw(10) << accounts[i].getBalance() << endl;
		totalRevenue += accounts[i].getBalance();
	}
	cout << "Total Revenue = " << totalRevenue << endl << endl;

	// Display Expenses
	cout << "Acct#" << setw(12) << "Account" << setw(10) << "Balance" << endl;
	for (int i = 5; i < 11; i++)
	{
		cout << accounts[i].getAccNum() << setw(13) << accounts[i].getName() << setw(10) << accounts[i].getBalance() << endl;
		totalExpense += accounts[i].getBalance();
	}
	cout << "Total Expense = " << totalExpense << endl;
	cout << "Net income = " << totalRevenue + totalExpense << endl;

	system("pause");
}