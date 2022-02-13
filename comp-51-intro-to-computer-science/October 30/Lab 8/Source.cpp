#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

void getData(string fileName, int appendSwitch) {
	string mOB;
	float examScore;
	ofstream outStream;
	ifstream inStream;
	int studentNum;
	bool fail = 0;

	if (appendSwitch == 1)
	{
		inStream.open(fileName);
		fail = inStream.fail();
	}

	if (fail == 0)
	{
		inStream.close();

		if (appendSwitch == 1)
		{
			outStream.open(fileName, ios::app | ios::_Nocreate);
			outStream << endl;
		}
		else
		{
			outStream.open(fileName);
		}

		cout << "Enter number of students: " << endl;
		cin >> studentNum;

		for (int i = 1; i <= studentNum; i++)
		{
			cout << "Enter student " << i << "'s month of birth (first three characters): ";
			cin >> mOB;
			outStream << mOB << endl;
			cout << endl;
			cout << "Enter the exam score: ";
			cin >> examScore;
			outStream << examScore << endl;
			cout << endl;
		}

		outStream.close();
	}
	else
	{
		cout << "File open failed!" << endl;
	}
}

void analyzeData(string fileName) {
	string mOB;
	int examScore;
	int studentNum;
	int isJuly = 0;
	float sumJuly = 0;
	float avgJuly;
	int notJuly = 0;
	float sumNotJuly = 0;
	float avgNotJuly;
	ifstream inStream;

	inStream.open(fileName);
	if (!inStream.fail())
	{
		
		while (inStream >> mOB >> examScore)
		{
			cout << mOB << ": " << examScore << endl;
			if (mOB == "Jul")
			{
				isJuly++;
				sumJuly += examScore;
			}
			else
			{
				notJuly++;
				sumNotJuly += examScore;
			}
		} 
		avgJuly = sumJuly / isJuly;
		avgNotJuly = sumNotJuly / notJuly;
		cout << "July born students' average: "<< fixed << setprecision(2) << avgJuly <<  endl;
		cout << "Non-july born student's average: " << fixed << setprecision(2) << avgNotJuly << endl;
		if (avgJuly > avgNotJuly)
		{
			cout << "This result supports Dr Tonto's theory of july born students being better at non-july born students at computer science!" << endl;
		}
		else
		{
			cout << "This result does not support Dr Tonto's theory of july born students being better at non-july born students at computer science!" << endl;
		}
	}
	else
	{
		cout << "File open failed!" << endl;

	}

	inStream.close();
}

int main() {
	int studentNum;
	int menuChoice;
	int appendSwitch;
	bool loop = true;
	string fileName;

	while (1)
	{
		cout << "1. Create new data file" << endl;
		cout << "2. Append to an existing data file" << endl;
		cout << "3. Analyze a data file" << endl;
		cout << "4. Quit" << endl;
		cout << "Select menu option: ";
		cin >> menuChoice;

		switch (menuChoice)
		{
		case 1:
			cout << "Enter new file's name: ";
			cin >> fileName;
			getData(fileName, 0);
			break;
		case 2:
			cout << "Enter file's name: ";
			cin >> fileName;
			getData(fileName, 1);
			break;
		case 3:
			cout << "Enter file's name: ";
			cin >> fileName;
			analyzeData(fileName);
			break;
		case 4:
			return 0;
		default:
			break;
		}
	}
}