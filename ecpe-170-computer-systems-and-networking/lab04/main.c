/**
 * Kaung Khant Pyae Sone
 * k_kaung@u.pacific.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    print_header();

    // Get file name
    char *filePathBuffer = (char *)malloc(sizeof(char) * 1024);
    printf("Available files\n");
    printf("------------------------------------------------------------------------\n");
    system("ls -1 *.txt");
    printf("------------------------------------------------------------------------\n");
    printf("Enter filename of puzzle to load (including .txt extension): ");
    scanf("%s", filePathBuffer);

    // Try opening file name
    struct puzzle currentPuzzle;
    FILE *fp = fopen(filePathBuffer, "r");
    free(filePathBuffer);
    if (fp)
    {
        currentPuzzle = create_puzzle(fp, 9, 9); // MUST BE 9, 9
    }
    else
    {
        printf("File cannot be opened, exiting\n");
        return 0;
    }
    fclose(fp);

    // Enable this block to autocomplete sudoku except row 8 col 8
    // for (int row = 0; row < currentPuzzle.height; row++)
    // {
    //     for (int col = 0; col < currentPuzzle.width; col++)
    //     {
    //         currentPuzzle.grid[row][col] = currentPuzzle.solvedGrid[row][col];
    //     }
    // }
    // currentPuzzle.grid[7][7] = '#'; // Put in 3 at row 8 col 8 to solve the puzzle

    // Start sudoku game
    int row, col, value;
    row = col = value = 0;
    char message[1024] = ""; // Message to display at before asking for input
    while (1)
    {
        print_header();
        print_puzzle(currentPuzzle, 0, row, col);
        // Row Col Value Entry
        printf("%s", message);
        printf("Enter row,col,value to solve a square, or -1 to exit: ");

        scanf("%d,%d,%d", &row, &col, &value);

        if (row == -1)
        {   
            system("clear");
            printf("Game has been exited! Here's one solution to the puzzle!\n\n");
            print_puzzle(currentPuzzle, 1, -1, -1);
            printf("\n");
            puzzle_free_memory(currentPuzzle);
            return 0; // If -1 is entered, quit
        }

        // Validate, row, col and value entered
        if (valid_input(row, col, value, currentPuzzle))
        {
            snprintf(message, 1024, "\e[0;33mLast action: Entered %d at row %d, col %d\e[0m\n", value, row, col);
            char temp = value + '0';
            currentPuzzle.grid[row - 1][col - 1] = temp;
        }
        else
        {
            snprintf(message, 1024, "Input is invalid, please try again\n");
            // TODO flush input buffer on invalid input 
            row = col = -1; // Board highlighting, see puzzle.c:85
        }

        if (puzzle_complete(currentPuzzle))
        {
            system("clear");
            printf("Congratulations! You have solved the puzzle!\n\n");
            print_puzzle(currentPuzzle, 0, -1, -1);
            printf("Here is an alternate solution to this puzzle!\n\n");
            print_puzzle(currentPuzzle, 1, -1, -1);
            puzzle_free_memory(currentPuzzle);
            return 0;
        }
    }
}

// Clears the screen and prints the title and rule
void print_header()
{
    system("clear");
    printf("\nSUDOKU GAME\n\nRules: Fill the 9x9 square such that each row, column,\nor block contains all of the numbers 1-9\n");
    printf("\e[0;34mBlue\e[0m locations can be changed\n\n");
}