#include <iostream>

using namespace std;

bool isFilled(char board[][3], int row, int column) {
	bool filled;
	if (board[row][column] == 'e')
	{
		filled = false;
	}
	else
	{
		filled = true;
	}
	return filled;
}

void printBoard(char board[][3]) {
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			cout << " " << board[row][column];
		}
		cout << endl;
	}
}

void move(char board[][3], char player) {
	int row;
	int col;
	while (1)
	{
		cout << "Player " << player << ": please enter the coordinates of your move (row col): ";
		cin >> row >> col;
		if (row >= 0 && row <= 2 && col >= 0 && col <= 2)
		{
			if (isFilled(board, row, col) == false)
			{
				board[row][col] = player;
				break;
			}
			else
			{
				cout << "This slot is filled. Please try again" << endl;
			}
		}
		else
		{
			cout << "Invalid range. Please try again" << endl;
		}
	}
}

bool isGameOver(char board[][3]) {
	char player;
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == board [i][1] && board[i][0] == board[i][2] && board[i][0] != 'e')
		{
			cout << "Winner " << board[i][0] << endl;
			return true;
		}

		/*if (i == 0)
		{
			player = 'X';
		}
		else
		{
			player = 'O';
		}
		if (
			board[0][0] == player &&
			board[0][1] == player &&
			board[0][2] == player ||
			board[1][0] == player &&
			board[1][1] == player &&
			board[1][2] == player ||
			board[2][0] == player &&
			board[2][1] == player &&
			board[2][2] == player ||
			board[0][0] == player &&
			board[1][0] == player &&
			board[2][0] == player ||
			board[0][1] == player &&
			board[1][1] == player &&
			board[2][1] == player ||
			board[0][2] == player &&
			board[1][2] == player &&
			board[2][2] == player ||
			board[0][0] == player &&
			board[1][1] == player &&
			board[2][2] == player ||
			board[0][2] == player &&
			board[1][1] == player &&
			board[2][0] == player
			)
		{
			cout << "Game over" << endl;
			cout << "Player " << player << " wins!" << endl;
			gameOver = true;
			break;
		}
		else
		{
			gameOver = false;
		}*/
	}
	for (int j = 0; j < 3; j++)
	{
			if (board[0][j] == board [1][j] && board[0][j] == board[2][j] && board[0][j] != 'e')
		{
			cout << "Winner " << board[0][j] << endl;
			return true;
		}
	}
	if 
	(
		board[0][0] == board[1][1] &&
		board[0][0] == board[2][2] ||
		board[2][0] == board[1][1] &&
		board[2][0] == board[0][2] &&
		board[1][1] != 'e'
	)
	{
		cout << "Winner " << board[1][1] << endl;
		return true;
	}
	return false;
	//return gameOver;
}

int main() {
	int boardRow{};
	int boardColumn{};
	char player = 'X';
	char board[3][3];
	bool filled{};
	bool gameOver = false;
	int tie = 0;

	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			board[row][column] = 'e';
		}
	}
	while (gameOver == false)
	{
		printBoard(board);
		if (player == 'X')
		{
			move(board, 'X');
			player = 'O';
		}
		else
		{
			move(board, 'O');
			player = 'X';
		}
		system("cls");
		gameOver = isGameOver(board);
		if (gameOver == true)
		{
			printBoard(board);
		}
		tie++;
		if (tie == 9)
		{
			cout << "It's a tie!" << endl;
			printBoard(board);
			gameOver = true;
		}
	}

}