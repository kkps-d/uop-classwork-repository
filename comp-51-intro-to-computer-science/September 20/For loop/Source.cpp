#include <iostream>
using namespace std;

int main() {
	int fact = 1;
	int num;
	/*for (int i = 12; i <= 23; i += 2)
	{
		if (i % 2 == 0)
		{
			cout << i << " is even" << endl;
		}
	}*/
	cout << "Enter factorial number: ";
	cin >> num;
	for (int i = num; i > 0; i--)
	{
		fact = fact * i;
	}
	cout << "Factorial: " << fact << endl;

	system("pause");
}