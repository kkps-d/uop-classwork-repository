// Lab 1

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string verb;
	string noun;
	string noun2;
	string adj;

	cout << "Welcome to Madlibs!" << endl;
	cout << "Enter a verb: ";
	cin >> verb;
	cout << "To " << verb << ", or not to " << verb << ", that is the question." << endl;

	cout << endl << "Enter a verb in past tense: ";
	cin >> verb;
	cout << "Enter a noun: ";
	cin >> noun;
	cout << "The Cow " << verb << " over the " << noun << endl;

	cout << endl << "Enter first noun: ";
	cin >> noun;
	cout << "Enter second noun: ";
	cin >> noun2;
	cout << "Enter an adjective: ";
	cin >> adj;
	cout << noun << " is more " << adj << " than the " << noun2 << endl << endl;

	system("pause");
	return 0;
}