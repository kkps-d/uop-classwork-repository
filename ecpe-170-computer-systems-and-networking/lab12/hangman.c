/**
 * Kaung Khant Pyae Sone
 * k_kaung@u.pacific.edu
 */
#include <stdio.h>
#include "hangman.h"

// Word to guess
// Change this to change words
const char *WORD_GUESS = "HANGMAN";
int word_length; // The length of WORD_GUESS

// Buffer to display the hidden word to the user
// HANGMAN will look like _______
char word_buffer[46]; // Can use variable size arrays, but easier to translate to mips


// Tracks used letters and how many of them
char used_letters[26] = ""; // Same thing as word buffer
int used_letters_length = 0;

// Only 5 wrong guesses allowed,
// 6th wrong guess loses
char missed_letters[7] = "\0"; // Same thing as word buffer
int wrong_counter = 0;

int main()
{
    // Get length of WORD_GUESS
    word_length = 0;
    int i = 0;
    while (WORD_GUESS[i] != '\0')
    {
        i++;
        word_length++;
    }

    // Fill word buffer with '_'s according to word length and null terminate
    for (int i = 0; i < word_length; i++)
    {
        word_buffer[i] = '_';
    }
    word_buffer[word_length] = '\0';

    printf("Welcome to Hangman!\n");
    printf("Implemented by Kaung\n\n");

    // State of the game
    // 0 - not won, 1 - won, 2 - lost
    int state = 0;

    while (state == 0)
    {
        print_game();
        char c = user_input();
        // If c is 0, exit the program
        if (c == '0')
        {
            return 0;
        }
        state = check_game(c);
    }

    // Program reaches this part if user has either won or lost
    if (state == 1)
    {
        print_game();
        printf("Congratulations - you win!\n");
    }
    else
    {
        print_game();
        printf("You lose - out of moves!\n");
    }
    return 0;
}

// Prints the game
void print_game()
{
    printf("\n   |-----|   Word: %s\n", word_buffer);
    printf("   |     |\n");
    if (wrong_counter >= 1)
    {
        printf("   O     |   ");
    }
    else
    {
        printf("         |   ");
    }
    printf("Misses: %s\n", missed_letters);
    switch (wrong_counter)
    {
    case 2:
        printf("   |     |\n");
        printf("   |     |\n");
        break;
    case 3:
        printf("  \\|     |\n");
        printf("   |     |\n");
        break;
    case 4:
    case 5:
    case 6:
        printf("  \\|/    |\n");
        printf("   |     |\n");
        break;
    default:
        printf("         |\n");
        printf("         |\n");
        break;
    }

    switch (wrong_counter)
    {
    case 5:
        printf("  /      |\n");
        break;
    case 6:
        printf("  / \\    |\n");
        break;
    default:
        printf("         |\n");
        break;
    }
    printf("         |\n");
    printf(" ---------\n");
}

// List of alphabets to accept
const char *ACCEPT = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char user_input()
{
    char c;
    while (1)
    {
        printf("Enter next character (A-Z), or 0 (zero) to exit: ");
        fflush(stdout);
        scanf(" %c", &c);
        if (c == '0')
            return '0';
        for (int i = 0; i < 26; i++)
        {
            if (ACCEPT[i] == c)
            {
                return ACCEPT[i];
            }
        }
        printf("- Invalid input -\n");
    }
}

// 0 - not won
// 1 - won
// 2 - lost
int check_game(char c)
{
    // Checks if letter is already used
    for (int i = 0; i < used_letters_length; i++)
    {
        if (used_letters[i] == c)
        {
            printf("- Letter already used -\n");
            return 0;
        }
    }

    // New letter, add to used letters and increment length
    used_letters[used_letters_length] = c;
    used_letters_length++;

    // Replaces word if it exists
    int word_replaced = 0; // Whether a word was replaced or not
    for (int i = 0; i < word_length; i++)
    {
        if (WORD_GUESS[i] == c)
        {
            word_buffer[i] = c;
            word_replaced = 1;
        }
    }

    // If no words were replaced, wrong letter picked
    // Increment wrong_counter and add to missed_letters
    if (word_replaced == 0)
    {
        missed_letters[wrong_counter] = c;
        wrong_counter++;
        missed_letters[wrong_counter] = '\0';
        if (wrong_counter == 6)
        {
            return 2;
        }
        return 0;
    }
    else
    {
        // If words were replaced, check if won
        for (int i = 0; i < word_length; i++)
        {
            if (WORD_GUESS[i] != word_buffer[i])
            {
                return 0;
            }
        }
        return 1;
    }
}