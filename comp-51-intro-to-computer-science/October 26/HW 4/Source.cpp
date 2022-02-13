#include <iostream>
#include <string>
using namespace std;

string makeWord(int num[], int total)
{
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	string returnWord = "";
	for (int i = 0; i < total; i++) {
		returnWord = returnWord + alpha[num[i]];
	}

	return returnWord;
}

void fillArray(int numbers[], int set)
{
	if (set == 0)
	{
		numbers[0] = 19;
		numbers[1] = 17;
		numbers[2] = 8;
		numbers[3] = 2;
		numbers[4] = 10;
		numbers[5] = numbers[6] = 24;
	}
	else
	{
		numbers[2] = 4;
		numbers[3]--;
		numbers[3]--;
		numbers[4] = numbers[0];
	}
}

int getNum(int& numbers)
{
	int i = numbers * 100 - (10 % 3);
	numbers++;
	return i;
	numbers--;
}

int main()
{
	int numbers[7];
	for (int i = 0; i < 3; i++)
	{
		fillArray(numbers, i);
		cout << makeWord(numbers, 5);
		if (getNum(i) < 0)
			cout << " or ";
		else
			cout << "!\n";
	}
}
