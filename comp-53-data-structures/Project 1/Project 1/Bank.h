#pragma once
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

void colored(string input, WORD color);
int intChecker();
string strChecker();

class Bank;
class Account;
class SubAccount;
class Saving;
class Checking;

template <typename T>
int Partition(vector<T>& arr, int i, int k);
template <typename T>
void QuicksortDescByBal(vector<T>& arr, int i, int k);

class Bank {
public:
	Bank(string name, string address, string workingHrs);
	//string getName();
	//string getAddress();
	//string getWorkingHrs();
	void displayMenu();
	void createAccount();
	int findAccount(string& accNum);
	void manageAccount(string accNum);
	void showTotalAccounts();
	void showTotalSavings();
	void showTotalCheckings();
	void deleteAccount();
	void modifyAccount();
	void showDetailed();
	void showBrief();
	static int totalAccounts;
	static int nextAccount;
	static int totalSavings;
	static int nextSaving;
	static int totalCheckings;
	static int nextChecking;

private:
	string name;
	string address;
	string workingHrs;
	vector<Account> accounts;

};

class Account {
public:
	Account(string firstName, string lastName, string SSN);
	void displayMenu();
	string getAccNum();
	int getAccNumint();
	void createSaving();
	void createChecking();
	int getNumOfSavings();
	int getNumOfCheckings();
	int preFindSubAccount(string temp, string& clean, string& mode);
	template <typename T>
	int findSubAccount(int key, vector<T>& subAccs);
	void showSubAccounts();
	void modifySubAccount();
	void manageSubAccount(string accNum);
	void closeSubAccount();
	double totalBalance();
	void printDetail();
	void showDetailed();
	void showBrief();

private:
	int accNum;
	string firstName;
	string lastName;
	string SSN;
	bool firstSaving;
	vector<Saving> savings;
	vector<Checking> checkings;
};

class SubAccount {
public:
	SubAccount();
	int getAccNumint();
	double getBalance();
	void setBalance(double balance);
	void deposit();
	void withdraw();

	void init();

protected:
	int accNum;
	double balance;
private:
};

class Saving : public SubAccount {
public:
	Saving();
	string getAccNum();
	void init();
	void manage();
	void printDetail();
};

class Checking : public SubAccount {
public:
	Checking();
	string getAccNum();
	void init();
	void manage();
	void setMax();
	void toggleLock();
	void deposit();
	double getMaxAmt();
	string getLockedStatus();
	void printDetail();
	
private:
	double maxAmt;
	bool locked;
};