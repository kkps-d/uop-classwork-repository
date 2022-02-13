/*
Kaung Khant Pyae Sone
Project 2
COMP 051 - 01
*/
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

int main()
{
	srand((unsigned)time(0)); // Initialize random number generator

	//Variables for menu//
	int menuChoice;
	bool menuInvalid = 1;
	//////////////////////

	//Variables for random number counter//
	int randomUpperBound; //Random upper bound
	int numberOfLoops; // Number of loops when printing table
	int randomNumber = 0; // Randomly generated number, initially 0
	int randomLowest = 100000; // Lowest randomly generated number, initially very high so the next random number is definitely lowest
	int randomHighest = 0; // Highest randomly generated number, initially 0 so the next random number is definitely highest
	int randomTotal = 0; // Total of randomly generated numbers
	float randomAverage; // Average of randomly generated numbers
	///////////////////////////////////////

	//Variables for character input counter//
	char charInput; // Character input from user
	char charChoice; // Continue, yes or no?
	bool charChoiceError = 1; // Invalid choice checking for charChoice, charChoiceError == 0 means valid
	int asciiVal; // charInput converted to int
	bool charContinue{}; // Continue, yes or no? but charContinue == 0 exits loop
	int smallLetter = 0; // Number of small letters
	int capitalLetter = 0; // Number of capital letters
	int smallVowel = 0; // Number of small vowels
	int capitalVowel = 0; // Number of capital vowels
	int smallConsonant = 0; // Number of small consonants
	int capitalConsonant = 0; // Number of capital consonants
	int digits = 0; // Number of numbers
	int others = 0; // Number of other characters
	/////////////////////////////////////////

	cout << "Letter and number counter by Kaung Khant Pyae Sone" << endl << endl;
	cout << "(1) Count randomly generated numbers" << endl;
	cout << "(2) Count character input" << endl;
	cout << "(3) Exit" << endl;
	cout << "Enter your choice: ";
	cin >> menuChoice;


	while (1) // Unwanted character checking for menuChoice
	{
		if (cin.fail())
		{
			cin.clear(); // Clears cin buffer
			cin.ignore(1,'/n'); // Ignores 1 character and newline
			cout << "Invalid character. Please enter again: ";
			cin >> menuChoice;
		}
		else
		{
			break;
		}
	}

	do 	// Invalid choice checking for menuChoice //
	{
		switch (menuChoice)
		{
		case 1:

			/////////////////////////////////////////////////////////////
			//	             Randomly Generated Numbers                //
			/////////////////////////////////////////////////////////////

			menuInvalid = 0; // Tells choice is valid so program can exit after running
			cout << endl << "Counting randomly generated numbers" << endl;
			cout << "Enter the upper bound for the generated number (1-1000): ";
			cin >> randomUpperBound;
			do  // Loops error checking and input prompting if randomUpperBound is not within 10-1000
			{
				if (cin.fail()) // Unwanted character checking for randomUpperBound
				{
					cin.clear();
					cin.ignore(1, '/n');
					cout << "Invalid character. Please enter again: ";
					cin >> randomUpperBound;
				}
				else if (randomUpperBound < 10 || randomUpperBound > 1000) // Prints message and re-prompts input if randomUpperBound is not within 10-1000
				{
					cout << "Invalid range. Please enter again: ";
					cin >> randomUpperBound;
				}
				else
				{
					break;
				}
			} while (randomUpperBound < 10 || randomUpperBound > 1000); // Read - do


			cout << "Enter number of times to run the loop (>3): ";
			cin >> numberOfLoops;
			do  // Loops error checking and input prompting if numberOfLoops is not greater than 3
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1, '/n');
					cout << "Invalid character. Please enter again: ";
					cin >> numberOfLoops;
				}
				else if (numberOfLoops < 3) // Prints message and re-prompts input if numberOfLoops is not greater than 3
				{
					cout << "Invalid range. Please enter again: ";
					cin >> numberOfLoops;
				}
				else
				{
					break;
				}
			} while (numberOfLoops < 3); // Read - do

			//Start Printing Table//
			//First Row//
			cout << setfill('_') << setw(74) << "_" << endl;
			cout << setfill(' ');
			cout << "|" << setw(18) << " " << left;
			cout << "|" << setw(9) << "Counter" << left;
			cout << "|" << setw(6) << "Loops" << left;
			cout << "|" << setw(9) << "Current" << left;
			cout << "|" << setw(8) << "Lowest" << left;
			cout << "|" << setw(8) << "Highest" << left;
			cout << "|" << setw(8) << "Total" << left << "|";
			cout << endl;
			/////////////

			//Second Row//
			cout << "|" << setfill('-') << setw(73) << right << "|" << endl;
			cout << setfill(' ') << left;
			cout << "|" << setw(18) << "Initial values" << right;
			cout << "|" << setw(9) << "0" << right;
			cout << "|" << setw(6) << numberOfLoops << right;
			cout << "|" << setw(9) << "0" << right;
			cout << "|" << setw(8) << "0" << right;
			cout << "|" << setw(8) << "0" << right;
			cout << "|" << setw(8) << "0" << left << "|";
			cout << endl;
			//////////////

			//Other Rows that can be looped//
			for (int i = 1; i <= numberOfLoops; i++)
			{
				
				randomNumber = rand() % randomUpperBound + 1; // Generates a number between 1-randomUpperBound 
				if (randomNumber < randomLowest) // Compares current number to previous lowest number
				{
					randomLowest = randomNumber; // If smaller, current number becomes new lowest number
				}
				if (randomNumber > randomHighest) // Compares current number to previous highest number
				{
					randomHighest = randomNumber; // If larger, current number becomes new highest number
				}
				randomTotal = randomTotal + randomNumber;
				cout << left;
				// Converting i to string and then combining with a to produce "End of loop (num)"
				// Needed to do this, because formatting breaks if using cout << "End of loop " << i;
				string a = "End of loop ";
				string b;
				ostringstream convert;
				convert << i;
				b = convert.str();
				cout << "|" << setw(18) << a + b << left << right;
				cout << "|" << setw(9) << i << right;
				cout << "|" << setw(6) << numberOfLoops << right;
				cout << "|" << setw(9) << randomNumber << right;
				cout << "|" << setw(8) << randomLowest << right;
				cout << "|" << setw(8) << randomHighest << right;
				cout << "|" << setw(8) << randomTotal << left << "|";
				cout << endl;
			}
			/////////////////////////////////
			
			//Printing final lowest, final highest and average of total//
			cout << "|" << setfill('-') << setw(73) << right << "|" << endl;
			cout << "Final lowest random value = " << randomLowest << endl;
			cout << "Final highest random value = " << randomHighest << endl;

			randomAverage = float(randomTotal) / float(numberOfLoops);
			cout << "Average of total value = " << randomAverage << endl;
			/////////////////////////////////////////////////////////////
			break;

		case 2:

			/////////////////////////////////////////////////////////////
			//	                  Character input                      //
			/////////////////////////////////////////////////////////////

			menuInvalid = 0; // Tells choice is valid so program can exit after running
			cout << endl << "Counting character input" << endl;

			do
			{
				cout << "Enter a character: ";
				cin >> charInput;
				asciiVal = charInput; // converts char charInput to int asciiVal
				cout << endl << "The character: '" << charInput << "'" << endl;
				cout << "The numeric decimal value for this character: " << asciiVal << endl;
				cout << "Character type: ";
				
				//Small Letters//
				if (asciiVal >= 97 && asciiVal <= 122) // Range checking for 'a' to 'z'
				{
					smallLetter++;
					cout << "Small letter, ";
					// Vowels
					if (asciiVal == 97 || asciiVal == 101 || asciiVal == 105 || asciiVal == 111 || asciiVal == 117)
					{
						smallVowel++;
						cout << "Vowel" << endl;
					}
					// Consonant
					else
					{
						smallConsonant++;
						cout << "Consonant" << endl;
					}
				}
				/////////////////

				//Capital Letters//
				else if (asciiVal >= 65 && asciiVal <= 90) // Range checking for 'A' to 'Z'
				{
					cout << "Capital letter, ";
					capitalLetter++;
					// Vowel
					if (asciiVal == 65 || asciiVal == 69 || asciiVal == 73 || asciiVal == 79 || asciiVal == 85)
					{
						capitalVowel++;
						cout << "Vowel" << endl;
					}
					// Consonant
					else
					{
						capitalConsonant++;
						cout << "Consonant" << endl;
					}
				}
				///////////////////
				
				//Numbers//
				else if (asciiVal >= 48 && asciiVal <= 57) // Range checking for '0' to '9'
				{
					cout << "Number" << endl;
					digits++;
				}
				else {
					cout << "Other character" << endl;
					others++;
				}
				///////////

				//Continue, yes or no?//
				do
				{
					cout << endl << "Do you want to keep entering numbers? (Y/N): ";
					cin >> charChoice;
					if (charChoice == 'y' || charChoice == 'Y')
					{
						charContinue = 1;
						charChoiceError = 0;
					}
					else if (charChoice == 'n' || charChoice == 'N')
					{
						charContinue = 0;
						charChoiceError = 0;
					}
					else
					{
						cout << "Invalid Choice. Please try again" << endl;
						charChoiceError = 1;
					}
				} while (charChoiceError == 1);
				////////////////////////

			} while (charContinue == 1); // Prints the number of each type of words entered
			cout << "Small letters: " << smallLetter << endl;
			cout << "Small vowels: " << smallVowel << endl;
			cout << "Small consonants: " << smallConsonant << endl;
			cout << "Capital letters: " << capitalLetter << endl;
			cout << "Capital vowels: " << capitalVowel << endl;
			cout << "Capital consonants: " << capitalConsonant << endl;
			cout << "Numbers: " << digits << endl;
			cout << "Other characters: " << others << endl;
			break;

		case 3:
			return 0;

		default:
			cout << "Invalid choice. Enter new choice: ";
			cin >> menuChoice;
			break;
		}
	} while (menuInvalid == 1);
}

