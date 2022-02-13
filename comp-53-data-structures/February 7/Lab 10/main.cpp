/*
Lab 10
Kaung Khant Pyae Sone
Kaung Min Sett
*/
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

char title1[30] = "Data Structures In C++";
char title2[30] = "Data   Structures		 In C++";
char password[4][30] = { "monkey", "MonnkeeY", "M8nnkeeY", "M8nnkeeY!" };

void splittedPrint(char chars[]) {
	for (int i = 0; chars[i] != '\0'; i++)
	{
		if (!isblank(chars[i]))
		{
			cout << chars[i];
		}
		else
		{
			while (isblank(chars[i]))
			{
				i++;
			}
			i--;
			cout << endl;
		}
	}
}

void stringFlipCase(char chars[]) {
	for (int i = 0; chars[i] != '\0'; i++)
	{
		if (isupper(chars[i]))
		{
			putchar(tolower(chars[i]));
		}
		else
		{
			putchar(toupper(chars[i]));
		}
	}
}

void stringTrimNonAlphanumeric(char chars[]) {
	for (int i = 0; chars[i] != '\0'; i++)
	{
		if (isalnum(chars[i]))
		{
			cout << chars[i];
		}
	}
}

bool isValidPassword(char chars[]) {
	bool isValid = true;
	int charsLen = strlen(chars);
	if (charsLen < 8)
	{
		cout << chars << " Not Accepted: Passwords must be at least 8 characters long." << endl;
		isValid = false;
	}
	
	for (int i = 0; i < charsLen && !isupper(chars[i]); i++)
	{
		if (i == charsLen - 1)
		{
			cout << chars << " Not Accepted: Passwords must at least include one uppercase alphabetic character." << endl;
			isValid = false;
		}
	}

	for (int i = 0; i < charsLen && !islower(chars[i]); i++)
	{
		if (i == charsLen - 1)
		{
			cout << chars << " Not Accepted: Passwords must at least include one lowercase alphabetic character." << endl;
			isValid = false;
		}
	}

	for (int i = 0; i < charsLen && !isdigit(chars[i]); i++)
	{
		if (i == charsLen - 1)
		{
			cout << chars << " Not Accepted: Passwords must at least include one digit." << endl;
			isValid = false;
		}
	}

	for (int i = 0; i < charsLen && !ispunct(chars[i]); i++)
	{
		if (i == charsLen - 1)
		{
			cout << chars << " Not Accepted: Passwords must at least include one special character: \n!\"#$%&'()*+,-./:;<=>?@[\\]^_\`{|}~" << endl;
			isValid = false;
		}
	}

	if (isValid == true)
	{
		cout << chars << " Accepted." << endl;
	}

	return isValid;
}

int main() {
	cout << "Splitting title1:" << endl;
	splittedPrint(title1);
	cout << endl << endl;

	cout << "Splitting title2:" << endl;
	splittedPrint(title2);
	cout << endl << endl;

	cout << "Flipping the case in title1: ";
	stringFlipCase(title1);
	cout << endl;

	cout << "Trimming non-alphanumeric characters in title1: ";
	stringTrimNonAlphanumeric(title1);
	cout << endl;

	cout << "Trimming non-alphanumeric characters in title2: ";
	stringTrimNonAlphanumeric(title2);
	cout << endl << endl;

	for (int i = 0; i < 4; i++)
	{
		isValidPassword(password[i]);
		cout << endl;
	}
}