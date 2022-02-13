#include <iostream>
#include <ctime>

using namespace std;

// Used only for printing bankrupt message, main loop seperately detects and exits loop
void detectBankrupt(int currentBalance) {
	if (currentBalance == 0)
	{
		cout << "Oh No! You're bankrupt! You don't belong here anymore!" << endl;
	}
}

// Used to generate the initial bank balance between $100 and $200
int generateBankBalance() {	
	return rand() % 101 + 100;
}

// Accepts input and checks for invalid characters
// Almost every user input uses this function
int intChecker() {	
	int input;
	cin >> input;
	do
	{

		if (cin.fail())
		{
			cin.clear(); // Clears cin buffer
			cin.ignore(1, '/n'); // Ignores 1 character and newline
			cout << "Invalid character. Please enter again: ";
			cin >> input;
		}
	} while (cin.fail());
	return input;
}

// Prevents user from entering 0 or entering more than they have in their account
int moneyChecker(int currentBalance) {	
	int betAmount;
	do
	{
		betAmount = intChecker();
		if (betAmount > currentBalance)
		{
			cout << "You have entered more money than you have!" << endl;
			cout << "Please try again: $";
		}
	} while (betAmount > currentBalance);
	do
	{
		if (betAmount <= 0)
		{
			cout << "Amount cannot be $0 or less than $0! Please enter again: ";
			cin >> betAmount;
		}
	} while (betAmount <= 0);
	return betAmount;
}

// Used to generate points for 21
int twentyOneRand() {	
	int randNum = rand() % 13 + 1;
	if (randNum > 10)
	{
		randNum = 10;
	}
	return randNum;
}

// Calculates money won and returns it in 'newBalance'
void moneyWin(int currentBalance, int payoff, int betAmount, int &newBalance) {
	newBalance = currentBalance + (betAmount * payoff);
}
// Calculates money lost and returns int in 'newBalance', and prevents the balance from becoming negative
void moneyLose(int currentBalance, int betAmount, int& newBalance) {
	newBalance = currentBalance - betAmount;
	if (newBalance < 0)
	{
		cout << "Negative balance not allowed. Setting to 0" << endl;
		newBalance = 0;
	}
}

// Start High-Low game
int highLow(int currentBalance) {
	int newBalance;	// Balance to be returned after calculating win or loss
	int payoff = 1;	// How many times the betting amount to win
	int betAmount;	// The bet amount
	int randomNumber1;	// User guesses if next number is higher or lower than this number
	int randomNumber2;	// User guesses if this number is higher or lower than previous number
	char userGuess;	// User's guess, (H)igh/(L)ow
	bool validChoice = false; // Keeps menu looping if user selects anything that's not H/L

	cout << "Welcome to High-Low!" << endl;
	cout << "Your current balance is: $" << currentBalance << endl;
	cout << "Enter the amount you want to bet: $";
	betAmount = moneyChecker(currentBalance);	// Function to check if bet amount is less than user's balance. Function takes care of input
	randomNumber1 = rand() % 10 + 1;
	cout << endl;
	cout << "Here's the first number: " << randomNumber1 << endl;
	do // Menu that loops when user selects invalid choice
	{
		cout << "Do you think the next number will be higher or lower than the first? (H/L): ";
		cin >> userGuess;
		randomNumber2 = rand() % 10 + 1;
		switch (userGuess)
		{
		case 'H':
		case 'h':
			cout << "The second number is: " << randomNumber2 << endl << endl;
			if (randomNumber2 > randomNumber1)
			{
				cout << "You're right! You Win!" << endl;
				moneyWin(currentBalance, payoff, betAmount, newBalance);	// Calculates amount of money won and updates balance
			}
			else
			{
				cout << "Too bad! You Lost!" << endl;
				moneyLose(currentBalance, betAmount, newBalance);	// Calculates amount of money lost and updates balance
			}
			validChoice = true; // Allows invalid-choice-checking loop to exit
			break;
		case 'L':
		case 'l':
			cout << "The second number is: " << randomNumber2 << endl << endl;
			if (randomNumber2 < randomNumber1)
			{
				cout << "You're right! You Win!" << endl;
				moneyWin(currentBalance, payoff, betAmount, newBalance);	// Calculates amount of money won and updates balance
			}
			else
			{
				cout << "Too bad! You Lost!" << endl;
				moneyLose(currentBalance, betAmount, newBalance);	// Calculates amount of money lost and updates balance
			}
			validChoice = true;	// Allows invalid-choice-checking loop to exit
			break;
		default:
			cout << "Invalid choice, please try again" << endl;
			validChoice = false; // Allows invalid-choice-checking loop to exit
			break;
		}
	} while (validChoice == false);
	cout << endl << "Your new balance is: $" << newBalance << endl;
	return newBalance;	// Returns new balance to main
}

// Start 21 game
int twentyOne(int currentBalance) {
	int numSum;	// Total amount of points you have
	int betAmount;	// The bet amount
	int newBalance{};	// Balance to be returned after calculating win or loss
	int payoff = 2;	// How many times the betting amount to win
	int computerNum;	// Computer's points, to be compared to user's points
	char userGuess;	// User's guess, (H)it/(S)tay
	bool loopBreak = false;	// Keeps menu looping if user selects anything that's not H/S
	bool lost = false;	// Used to skip comparing to computer's points when your points go over 21 and lose

	cout << "Welcome to 21!" << endl;
	cout << "Your current balance is: $" << currentBalance << endl;
	cout << "Enter the amount you want to bet: $";
	betAmount = moneyChecker(currentBalance);

	numSum = twentyOneRand() + twentyOneRand();	// Generates two points from 1-10 and add them together

	cout << endl << "You currently have " << numSum << " points." << endl;

	do // Menu that loops when user selects invalid choice
	{
		cout << "Do you want to hit or stay?(H/S): ";
		cin >> userGuess;
		cout << endl;
		switch (userGuess)	// Loop where user can choose to add points(hit) or not(stay)
		{
		case 'H':
		case 'h':
			numSum += twentyOneRand();	// Adds a number from 1-10 and add to user's current points
			cout << "You currently have " << numSum << " points." << endl;
			break;
		case 'S':
		case 's':
			loopBreak = true;	// Allows invalid-choice-checking loop to exit
			break;
		default:
			cout << "Invalid choice, please try again" << endl;
			loopBreak = false;
			break;
		}
		if (numSum > 21)	// User loses when point's over 21
		{
			cout << "Oh no! You went over 21 points! You lost!" << endl;
			moneyLose(currentBalance, betAmount, newBalance);
			loopBreak = true;	// Allows invalid-choice-checking loop to exit
			lost = true;	// Skips comparing to computer's points when you lose
		}
	} while (loopBreak == false);

	if (lost != true)	// Flow control to compare user's points to computer's points
	{
		computerNum = rand() % 8 + 16;	// Generates computer's points
		cout << "The computer has " << computerNum << " points." << endl;
		if (computerNum >= 22)
		{
			cout << "The computer went over 21 points! You Win!" << endl;
			moneyWin(currentBalance, payoff, betAmount, newBalance);
		}
		else if (numSum > computerNum)
		{
			cout << "You got " << numSum << " points over the computer's " << computerNum << " points! You Win!" << endl;
			moneyWin(currentBalance, payoff, betAmount, newBalance);
		}
		else if (numSum < computerNum)
		{
			cout << "The computer got " << computerNum << " points over your " << numSum << " points! You Lose!" << endl;
			moneyLose(currentBalance, betAmount, newBalance);
		}
		else if (numSum == computerNum)
		{
			cout << "A tie!" << endl;
			newBalance = currentBalance;	// Balance remains the same when there is a tie
		}
	}
	
	cout << endl << "Your new balance is: $" << newBalance << endl;
	system("pause");
	return newBalance;
}

int craps(int currentBalance) {
	int newBalance{};	// Balance to be returned after calculating win or loss
	int betAmount;	// The bet amount
	int diceOne, diceTwo; // Dice two roll
	int diceSumOne;	// Sum of two dice for first round to check for craps or naturals
	int diceSumTwo;	// Sum of two dice for second round if there is no craps or naturals in the first round
	int payoff = 1;	// How many times the betting amount to win
	char userChoice;	// User's choice, (P)ass/(N)o Pass
	bool userPass;	// User passes or not, translated into boolean from userChoice
	bool loopBreak = false;	// Keeps menu looping if user selects anything that's not P/N
	cout << "Welcome to Craps!" << endl;
	cout << "Your current balance is: $" << currentBalance << endl;
	cout << "Enter the amount you want to bet: $";
	betAmount = moneyChecker(currentBalance);
	cout << endl;

	do // Menu that loops when user selects invalid choice
	{
		cout << "Do you want to bet on 'Pass' or 'No pass'?(P/N): ";
		cin >> userChoice;
		cout << endl;
		switch (userChoice)
		{
		case 'P':
		case 'p':
			userPass = true;	// User passes
			loopBreak = true;	// Allows invalid-choice-checking loop to exit
			break;
		case 'N':
		case 'n':
			userPass = false;	// User does not pass
			loopBreak = true;	// Allows invalid-choice-checking loop to exit
			break;
		default:
			cout << "Invalid choice, please try again" << endl;
			loopBreak = false;
			break;
		}
	} while (loopBreak == false);

	// Rolls two dice
	diceOne = rand() % 6 + 1;
	diceTwo = rand() % 6 + 1;

	diceSumOne = diceOne + diceTwo;	// Adds together values of the two dice
	cout << "The dice rolled a " << diceOne << " and a " << diceTwo << ", for a sum of " << diceSumOne << "! ";

	if (diceSumOne == 2 || diceSumOne == 3 || diceSumOne == 12)	// If sum of two dice is 2, 3 or 12, it's a Craps
	{
		switch (userPass)
		{
		case true:
			cout << "It's a Craps! You lost!" << endl;
			moneyLose(currentBalance, betAmount, newBalance);
			break;
		case false:
			cout << "It's a Craps! You win!" << endl;
			moneyWin(currentBalance, payoff, betAmount, newBalance);
			break;
		}
	}
	else if (diceSumOne == 7 || diceSumOne == 11)	// If sum of two dice is 7 or 11, it's a Natural
	{
		switch (userPass)
		{
		case true:
			cout << "It's a Natural! You win!" << endl;
			moneyWin(currentBalance, payoff, betAmount, newBalance);
			break;
		case false:
			cout << "It's a Natural! You lose!" << endl;
			moneyLose(currentBalance, betAmount, newBalance);
			break;
		}
	}
	else // If neither, roll second pair of dice and check if second result is equal to the first or is equal to 7
	{
		cout << "No craps or naturals! Rolling dice again" << endl;
		do
		{
			diceOne = rand() % 6 + 1;
			diceTwo = rand() % 6 + 1;
			diceSumTwo = diceOne + diceTwo;
		} while (diceSumTwo != diceSumOne && diceSumTwo != 7);

		cout << "The dice rolled a " << diceSumTwo << "! ";
		if (diceSumTwo == 7)	// Second roll is equal to first
		{
			switch (userPass)
			{
			case true:
				cout << "You lose!" << endl;
				moneyLose(currentBalance, betAmount, newBalance);
				break;
			case false:
				cout << "You win!" << endl;
				moneyWin(currentBalance, payoff, betAmount, newBalance);
				break;
			}
		}
		else if (diceSumTwo == diceSumOne)	// Second roll is equal to first roll
		{
			cout << endl << "This second roll matches the first roll! " << endl;
			switch (userPass)
			{
			case true:
				cout << "You win!" << endl;
				moneyWin(currentBalance, payoff, betAmount, newBalance);
				break;
			case false:
				cout << "You lose!" << endl;
				moneyLose(currentBalance, betAmount, newBalance);
				break;
			}
		}
	}
	cout << endl << "Your new balance is: $" << newBalance << endl;
	system("pause");
	return newBalance;
}

// Start the Slots game
int theSlots(int currentBalance, bool testCaseDriver) {
	int betAmount{};	// The bet amount
	int newBalance;	// Balance to be returned after calculating win or loss
	int numOne, numTwo, numThree;	// The three numbers of the slot machine

	switch (testCaseDriver)	// Check if function is being run from test case
	{
	case true:	// Test case skips asking user for bet amount and generates it instead
		betAmount = rand() % 200 + 1;	// Bet amount generated from $1-$100
		cout << "Bet amount: $" << betAmount;
		break;
	case false:	// Non test-case shows balance and asks user for bet amount
		cout << "Welcome to the Slots!" << endl;
		cout << "Your current balance is: $" << currentBalance << endl;
		cout << "Enter the amount you want to bet: $";
		betAmount = moneyChecker(currentBalance);
		break;
	}
	cout << endl;
	// Generates the three random numbers
	numOne = rand() % 10;
	numTwo = rand() % 10;
	numThree = rand() % 10;

	cout << " " << numOne << " ";
	cout << " " << numTwo << " ";
	cout << " " << numThree << " " << endl;

	if (numOne == numTwo && numOne == numThree && numTwo == numThree) // If all three numbers are equal, user wins with 99 payout
	{
		cout << "All three numbers are the same! You Win!" << endl;
		moneyWin(currentBalance, 99, betAmount, newBalance);
	}
	else if (numOne == numTwo || numOne == numThree || numTwo == numThree)	// If two out of three numbers are equal, user wins with 10 payout
	{
		cout << "Two numbers are the same! You Win!" << endl;
		moneyWin(currentBalance, 10, betAmount, newBalance);
	}
	else // If no numbers are same
	{
		cout << "None of the numbers are the same! You Lose!" << endl;
		moneyLose(currentBalance, betAmount, newBalance);
	}
	if (testCaseDriver != true) // Skips balance display and pause during test case
	{
		cout << endl << "Your new balance is: $" << newBalance << endl;
		system("pause");
	}
	return newBalance;
}

int duplicateCheck(int value, int valueCount, int numbers[]) {
	if (valueCount != 0)
	{
		for (int i = 0; i < valueCount; i++)
		{
			if (value == numbers[i])
			{
				cout << value << " is a duplicate. Discarded" << endl;
				return -1;
			}
		}
	}
	return value;
}
// Simple roulette wheel
// The wheel has 8 sections, 1 2 3 4 5 6 7 8
// The odd numbers are black, 1 3 5 7
// The even numbers are red, 2 4 6 8
// The game starts with payoff = 8
// Etc. if the user chooses one number, payoff = 8
// After choosing the first number, the second number starts with payoff = 6 and every extra number subtracts 1 from payoff
// If the user chooses 2 3, payoff = 6
// If the user chooses 1 5 7 8, payoff = 4
// If the user chooses black or red, payoff = 4

int rouletteWheel(int currentBalance) {
	int betAmount;	// The bet amount
	int newBalance;	// Balance to be returned after calculating win or loss
	int payoff = 8;	// How many times the betting amount to win
	int numbers[8];	// The array that contains the numbers you chose
	char userChoice; // The numbers and color you chose
	int value;	// userChoice but converted into numbers
	int valueCount = 0;	// The number of numbers you chose
	int rouletteResult;	// The result of the roulette
	bool loopBreak = false;	// Keeps menu looping if user selects anything that's 1-8 or B/R
	bool rouletteWin = false;	// Roulette win status

	cout << "Welcome to the Simple Roulette!" << endl;
	cout << "Your current balance is: $" << currentBalance << endl;
	cout << "Enter the amount you want to bet: $";
	betAmount = moneyChecker(currentBalance);
	cout << endl;
	
	cout << "You can choose from the following: " << endl;
	cout << "Numbers: 1 2 3 4 5 6 7 8" << endl;
	cout << "Colors: (B)lack (R)ed" << endl;
	cout << "Black is odds: 1 3 5 7" << endl;
	cout << "Red is even: 2 4 6 8" << endl << endl;
	cout << "You can choose multiple options, but you cannot choose duplicate numbers or more than 7 numbers" << endl << endl;

	while (loopBreak == false)
	{
		cout << "Enter your choice, one at a time" << endl;
		cout << "Enter (S) to stop entering values: ";
		cin >> userChoice;
		cout << endl;
		switch (userChoice)
		{
		case '1':	//
		case '2':	//
		case '3':	//
		case '4':	// Characters, later converted into integers and put into array
		case '5':	//
		case '6':	//
		case '7':	//
		case '8':	//
			value = duplicateCheck(int(userChoice)-48, valueCount, numbers);	// Checks if there are any duplicates in the array and discards value if so
			if (value != -1)
			{
				numbers[valueCount] = value;	// Puts number into array
				valueCount++;	// Increases how many values you have chosen
				payoff--;	// Decreases payoff. More numbers, less payoff
			}
			break;
		case 'B':
		case 'b':
			// Same thing as case: 'numbers', but done 4 times for 1 3 5 7
			value = duplicateCheck(1, valueCount, numbers);
			if (value != -1)
			{
				numbers[valueCount] = value;
				valueCount++;
				payoff--;
			}
			value = duplicateCheck(3, valueCount, numbers);
			if (value != -1)
			{
				numbers[valueCount] = value;
				valueCount++;
				payoff--;
			}
			value = duplicateCheck(5, valueCount, numbers);
			if (value != -1)
			{
				numbers[valueCount] = value;
				valueCount++;
				payoff--;
			}
			value = duplicateCheck(7, valueCount, numbers);
			if (value != -1)
			{
				numbers[valueCount] = value;
				valueCount++;
				payoff--;
			}
			break;
		case 'R':
		case 'r':
			// Same thing as case: 'numbers', but done 4 times for 2 4 6 8
			value = duplicateCheck(2, valueCount, numbers);
			if (value != -1)
			{
				numbers[valueCount] = value;
				valueCount++;
				payoff--;
			}
			value = duplicateCheck(4, valueCount, numbers);
			if (value != -1)
			{
				numbers[valueCount] = value;
				valueCount++;
				payoff--;
			}
			value = duplicateCheck(6, valueCount, numbers);
			if (value != -1)
			{
				numbers[valueCount] = value;
				valueCount++;
				payoff--;
			}
			value = duplicateCheck(8, valueCount, numbers);
			if (value != -1)
			{
				numbers[valueCount] = value;
				valueCount++;
				payoff--;
			}
			break;
		case 'S':	// Stops entering characters 
		case 's':	//
			loopBreak = true;	// Allows invalid-choice-checking loop to exit
			break;
		default:
			cout << "Invalid choice, please try again" << endl;
			loopBreak = false;
			break;
		}
		if (valueCount >= 7)
		{
			cout << "Maximum amount of numbers reached" << endl;
			valueCount = 7;	// Limits value count to 7
			payoff = 1;	// Limits payoff to 1
			break;
		}
	}
	cout << "You have choosen these numbers:";
	for (int i = 0; i < valueCount; i++)	// Prints the numbers you have chosen
	{
		cout << " " << numbers[i];
	}
	cout << endl;
	if (valueCount == 1)	// To keep the first choice from not reducing payoff, so that by choosing only one number the payoff remains 8
	{
		payoff++;
	}
	
	rouletteResult = rand() % 8 + 1;
	cout << "The number is: ";
	if (rouletteResult == 1 || rouletteResult == 3 || rouletteResult == 5 || rouletteResult == 7)	// Checks if the number is a black
	{
		cout << "Black ";
	}
	else // Checks if the number is a black
	{
		cout << "Red ";
	}
	cout << rouletteResult << endl;
	cout << endl;

	for (int i = 0; i < 8; i++)
	{
		if (numbers[i] == rouletteResult)	//	Checks if the rouletteResult is equal to one of your choice
		{
			rouletteWin = true;
		}
	}
	switch (rouletteWin)
	{
	case true:
		cout << "You Won!" << endl;
		moneyWin(currentBalance, payoff, betAmount, newBalance);
		break;
	case false:
		cout << "You Lose!" << endl;
		moneyLose(currentBalance, betAmount, newBalance);
	}
	cout << "Your new balance is: $" << newBalance << endl;
	system("pause");
	return newBalance;
}


// Runs the test cases
int testCaseDriver() {
	system("cls");
	cout << "Running Tests" << endl;
	cout << "==================" << endl << endl;

	// Tests if balance is generated correctly
	cout << "Testing bank balance range" << endl;
	int a;
	int b = 1000;
	int c = -1;
	for (int i = 0; i < 1000; i++)
	{
		a = generateBankBalance();	// Generates bank balance from $100-$200
		if (a < b)
		{
			b = a;
		}
		if (a > c)
		{
			c = a;
		}
	}
	cout << "Max balance: $" << c << endl;	// This should be $200
	cout << "Min balance: $" << b << endl << endl;	// This should be $100

	// Tests balance validation
	int currentBalance = 100;
	int newBalance;
	cout << "Testing balance validation when betting" << endl << endl;
	cout << "Current balance is set to $" << currentBalance << endl;
	cout << "Enter valid amount from $1-$100, should output equal: ";	// Tested with valid amount
	cout << moneyChecker(currentBalance) << endl;
	cout << "Enter invalid amount > $100, should reprompt for valid amount: ";	// Tested with invalid amount
	cout << moneyChecker(currentBalance) << endl << endl;

	// Tests balance updating function when user wins money
	cout << "Testing Win" << endl << endl;
	int payoff = 1;
	int betAmount = 20;
	cout << "Current balance is set to $" << currentBalance << endl;
	moneyWin(currentBalance, payoff, betAmount, newBalance);	// Tested win with $20 bet and payoff = 1
	cout << "Won $20 bet with payoff = 1: $" << newBalance << endl << endl;

	cout << "Current balance is set to $" << currentBalance << endl;
	payoff = 2;
	betAmount = 50;
	moneyWin(currentBalance, payoff, betAmount, newBalance);	// Tested win with $50 bet and payoff = 2
	cout << "Won $50 bet with payoff = 2: $" << newBalance << endl << endl;

	// Tests balance updating function when user loses money
	cout << "Testing loss" << endl << endl;
	cout << "Current balance is set to $" << currentBalance << endl;
	betAmount = 20;
	moneyLose(currentBalance, betAmount, newBalance);	// Tested loss with $20 bet
	cout << "Lost $20: $" << newBalance << endl << endl;

	
	moneyLose(currentBalance, currentBalance, newBalance);	// Tested loss with all in bet, user goes bankrupt
	cout << "Current balance is set to $" << currentBalance << endl;
	cout << "Lost current balance ($100): " << newBalance << endl;
	cout << "Detecting bankrupcy" << endl;
	detectBankrupt(newBalance);
	cout << endl;

	betAmount = 200;
	cout << "Current balance is set to $" << currentBalance << endl;
	cout << "Lost $200, error should pop up" << endl;	// Tested loss with more than user has, error should pop up and user goes bankrupt
	moneyLose(currentBalance, betAmount, newBalance);
	cout << "New Balance: " << newBalance << endl;
	cout << "Detecting bankrupcy" << endl;
	detectBankrupt(newBalance);
	cout << endl << endl;


	int slotsTimes;	// Number of times to run the slots test case
	int resultBalance;	// Generates a balance with a win or a loss calculated at the end of every run
	cout << "Testing Slots function" << endl << endl;
	cout << "Balance resets to $200 every loop" << endl;
	cout << "How many times do you want to test this function?: ";
	do // Prevents user from entering an invalid number of time
	{
		slotsTimes = intChecker();
		if (slotsTimes < 1)
		{
			cout << "Cannot be less than one time! Please try again: ";
		}
	} while (slotsTimes < 1);
	for (int i = 0; i <= slotsTimes; i++)
	{
		currentBalance = 200;
		resultBalance = theSlots(currentBalance, true);	// Calls the slots function with testcasedriver mode
		cout << "Resulting Balance: " << resultBalance << endl << endl;
	}
	system("pause");
	return 0;
}



int main() {
	srand((unsigned)time(0));

	int bankBalance = generateBankBalance();
	int userChoice;
	
	while (bankBalance != 0)
	{
		cout << "Welcome to the Casino!" << endl;
		cout << "======================" << endl;
		cout << "(1) Play High-Low" << endl;
		cout << "(2) Play 21" << endl;
		cout << "(3) Play Craps" << endl;
		cout << "(4) Play the Slots"<< endl;
		cout << "(5) Play the Simple Roulette" << endl;
		cout << "(6) Run Tests" << endl;
		cout << "(7) Exit" << endl;
		cout << "Enter your choice: ";
		userChoice = intChecker();
		cout << endl;

		switch (userChoice)
		{
		case 1:
			bankBalance = highLow(bankBalance);
			break;
		case 2:
			bankBalance = twentyOne(bankBalance);
			break;
		case 3:
			bankBalance = craps(bankBalance);
			break;
		case 4:
			bankBalance = theSlots(bankBalance, false);	// Calls the slots function with non-testcasedriver mode
			break;
		case 5:
			bankBalance = rouletteWheel(bankBalance);
			break;
		case 6:
			testCaseDriver();
			break;
		case 7:
			return 0;
		default:
			cout << "Invalid choice! Please try again" << endl << endl;
			break;
		}
	}
	detectBankrupt(bankBalance);
	return 0;
}