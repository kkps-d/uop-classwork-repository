/**
 * Kaung Khant Pyae Sone
 * k_kaung@u.pacific.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "functions.h"

// Constructor for puzzle, returns a puzzle object
struct puzzle create_puzzle(FILE *fp, int width, int height)
{
    // Create a temporary puzzle to store data in
    struct puzzle tempPuzzle;
    tempPuzzle.width = width;
    tempPuzzle.height = height;

    // Buff to store contents of fp, temp used to copy each line read from fgets and copy it to buff
    char *buff = (char *)malloc(sizeof(char) * 300);
    int count = 0;
    while (!feof(fp))
    {
        // Stores character by character into buffer until end of file
        buff[count++] = fgetc(fp);
    }
    buff[count] = '\0';

    // Initialize grid, solvedGrid and invalidGrid
    tempPuzzle.grid = (char **)malloc(sizeof(char *) * tempPuzzle.height);
    tempPuzzle.solvedGrid = (char **)malloc(sizeof(char *) * tempPuzzle.height);
    tempPuzzle.invalidGrid = (char **)malloc(sizeof(char *) * tempPuzzle.height);
    for (int i = 0; i < tempPuzzle.height; i++)
    {
        tempPuzzle.grid[i] = (char *)malloc(sizeof(char) * tempPuzzle.width);
        tempPuzzle.solvedGrid[i] = (char *)malloc(sizeof(char) * tempPuzzle.width);
        tempPuzzle.invalidGrid[i] = (char *)malloc(sizeof(char) * tempPuzzle.width);
    }

    // Start putting contents of buffer into grid and solvedGrid
    // Tracks current index in buff
    int i = 0;
    // Tracks current row and col in grid
    int col = 0;
    int row = 0;

    while (row < tempPuzzle.height)
    {
        // buff read here
        if (buff[i] == '*')
        {
            tempPuzzle.grid[row][col] = tempPuzzle.solvedGrid[row][col] = buff[i + 1];
            tempPuzzle.invalidGrid[row][col] = '1'; // This grid cannot be modified because it is part of the initial puzzle
            i++;
            col++;
        }
        else if (isdigit(buff[i]))
        {
            tempPuzzle.grid[row][col] = '#';
            tempPuzzle.solvedGrid[row][col] = buff[i];
            tempPuzzle.invalidGrid[row][col] = '0';
            col++;
        }
        if (col > tempPuzzle.width - 1)
        {
            // Increment row and reset col
            col = 0;
            row++;
        }
        i++;
    }

    free(buff);
    return tempPuzzle;
}

// Prints the puzzle into console
// puzzle - puzzle to be printed
// solved:
// 0 - print unsolved
// 1 - print solved
// 2 - print invalid locations
// highlight_x, y - Used to highlight previous action, use -1 if no highlights
void print_puzzle(struct puzzle puzzle, int solved, int highlight_row, int highlight_col)
{
    char **grid;
    switch (solved)
    {
    case 0:
        grid = puzzle.grid;
        break;
    case 1:
        grid = puzzle.solvedGrid;
        break;
    case 2:
        grid = puzzle.invalidGrid;
        break;
    }

    printf("     1 2 3   4 5 6   7 8 9  \n");
    printf("   |-----------------------|\n");

    for (int row = 0; row < puzzle.height; row++)
    {
        printf("%i  | ", row + 1);
        for (int col = 0; col < puzzle.width; col++)
        {
            if (row == highlight_row - 1 && col == highlight_col - 1)
            {
                printf("\e[0;33m%c \e[0m", grid[row][col]);
            }
            else if (puzzle.invalidGrid[row][col] == '0')
            {
                printf("\e[0;34m%c \e[0m", grid[row][col]);
            }
            else
            {
                printf("%c ", grid[row][col]);
            }

            if (((col + 1) % 3) == 0)
            {
                printf("| ");
            }
        }
        printf("\n");
        if (((row + 1) % 3) == 0)
        {
            printf("   |-----------------------|\n");
        }
    }
    printf("\n");
}

// Returns 1 if grid is invalid, 0 if grid is valid
int invalid_grid(int row, int col, struct puzzle puzzle)
{
    return puzzle.invalidGrid[row - 1][col - 1] == '1';
}

// Returns 1 if valid, 0 if invalid
int valid_input(int row, int col, int value, struct puzzle puzzle)
{
    return ((row <= puzzle.height && row > 0) && (col <= puzzle.width && col > 0) && (value > 0 && value < 10)) && !invalid_grid(row, col, puzzle);
}

// Returns 1 if puzzle is complete, 0 if not complete
int puzzle_complete(struct puzzle puzzle)
{
    return puzzle_complete_vertical(puzzle) && puzzle_complete_horizontal(puzzle) && puzzle_complete_grid(puzzle);
}

// Check vertically
int puzzle_complete_vertical(struct puzzle puzzle)
{
    // Check vertical
    for (int col = 0; col < puzzle.height; col++)
    {
        // Put contents of column into a string
        char *buff = (char *)malloc(sizeof(char *) * (puzzle.height + 1));
        strcpy(buff, ""); // Init so valgrind doesn't complain
        for (int row = 0; row < puzzle.height; row++)
        {
            char nt[2];
            nt[0] = puzzle.grid[row][col];
            nt[1] = '\0';
            strcat(buff, nt);
        }

        for (int i = 1; i <= 9; i++)
        {
            // Check if numbers exist in temp, if not, return 0
            // Convert int to char*
            char num = i + '0';
            if (strchr(buff, num) == NULL)
            {
                free(buff);
                return 0;
            }
        }
        free(buff);
    }
    return 1;
}

int puzzle_complete_horizontal(struct puzzle puzzle)
{
    for (int row = 0; row < puzzle.height; row++)
    {
        for (int i = 1; i <= 9; i++)
        {
            // Check if numbers exist in temp, if not, return 0
            // Convert int to char*
            char num = i + '0';
            if (strchr(puzzle.grid[row], num) == NULL)
            {
                return 0;
            }
        }
    }
    return 1;
}

int puzzle_complete_grid(struct puzzle puzzle)
{
    for (int grid_row = 0; grid_row < 3; grid_row++)
    {
        for (int grid_col = 0; grid_col < 3; grid_col++)
        {
            char *buff = (char *)malloc(sizeof(char *) * (puzzle.height + 1));
            strcpy(buff, ""); // Init again so valgrind doesnt complain
            // Small 3x3 grid traversal
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    char nt[2];
                    nt[0] = puzzle.grid[row + (grid_row * 3)][col + (grid_col * 3)];
                    nt[1] = '\0';
                    strcat(buff, nt);
                }
            }
            for (int i = 1; i <= 9; i++)
            {
                // Check if numbers exist in temp, if not, return 0
                // Convert int to char*
                char num = i + '0';
                if (strchr(buff, num) == NULL)
                {
                    free(buff);
                    return 0;
                }
            }
            free(buff);
        }
    }
    return 1;
}

void puzzle_free_memory(struct puzzle puzzle)
{
    for (int i = 0; i < puzzle.height; i++)
    {
        free(puzzle.grid[i]);
        free(puzzle.solvedGrid[i]);
        free(puzzle.invalidGrid[i]);
    }
    free(puzzle.grid);
    free(puzzle.solvedGrid);
    free(puzzle.invalidGrid);
}