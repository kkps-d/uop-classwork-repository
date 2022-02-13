#include <iostream>

using namespace std;

void find(char letters[], int size, char c) {
	bool found = false;
	for (int i = 0; i < size; i++)
	{
		if (letters[i] == c)
		{
			cout << "Letter found at position #" << i << endl;
			found = true;
			break;
		}
	}
	if (found == false)
	{
		cout << "Letter does not exist" << endl;
	}
}

int main() {
	char characters[8];
	char findChar;

	for (int i = 0; i < 8; i++)
	{
		cout << "Enter letter #" << i << ": ";
		cin >> characters[i];
	}
	cout << "The word is: ";
	for (int i = 0; i < 8; i++)
	{
		cout << characters[i];
	}
	cout << endl << "The word backwards is: ";
	for (int i = 7; i >= 0; i--)
	{
		cout << characters[i];
	}

	cout << endl << "Enter letter to search: ";
	cin >> findChar;

	find(characters, 8, findChar);
}