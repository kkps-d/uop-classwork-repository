#include <iostream>
using namespace std;

int main() {
	int num;
	int total{};
	for (int i = 0; i < 4; i++) {
		cout << "Enter a positive number: ";
		cin >> num;
		if (cin.fail()) {
			cout << "Bad number" << endl;
			cin.clear();
			cin.ignore(128, '\n');
		}
		if (num < 0) {
			cout << "Can't add negative numbers" << endl;
			continue;
		}
		total = total + num;
	}
	cout << "Total" << total << endl;
	
	/*for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < i; j++) {
			cout << i;
		}
		cout << endl;
	}*/
	
	system("pause");
}