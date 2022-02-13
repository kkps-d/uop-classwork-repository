#include <iostream>
using namespace std;

int main() {
	int num, cal, total{};
	char choice{};

	do
	{
		cout << "Enter a number between 1 and 100: ";
		cin >> num;
		if (num % 2 == 0)
		{
			cout << "That is even!" << endl;
		}
		else
		{
			cout << "That is odd!" << endl;
		}
	} while (num >=1 && num <= 100);

	/*Example 2
	do
	{
		total++;
		cout << "Can you do more pushups weakling!!!: ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
	cout << "You did " << total << " pushups.";
*/

	/*Example 1
	cout << "Welcome to InNOut. How many items?: ";
	cin >> num;

	while (num > 0) {
		cout << "How many calories?: ";
		cin >> cal;
		total = total + cal;
		num--;
	}
	cout << "Total = " << total << " calories.";*/
}