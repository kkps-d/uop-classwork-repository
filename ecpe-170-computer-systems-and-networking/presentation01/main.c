#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 5

int main() {
    // Allocate the first dimension of our two dimensional array
    int** numbers = (int**)malloc(sizeof(int*) * SIZE);

    // Allocate the second dimension of our two dimensional array
    for (int i = 0; i < SIZE; i++)
    {
        numbers[i] = (int*)malloc(sizeof(int) * SIZE);
    }
    
    // Fill up our array with random numbers from 1-9
    srand(time(0));
    if (SIZE < 10) printf("Our randomly generated numbers:\n");
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            int tempNum = (rand() % (9 - 1 + 1)) + 1;
            if (SIZE < 10) printf(" %i", tempNum);
            numbers[row][col] = tempNum;
        }
    if (SIZE < 10) printf("\n");
    }

    // Add the numbers from the two dimensional array and display it
    int result = 0;
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            result = result + numbers[row][col];
        }
    }
    printf("Result of addition: %i\n", result);

    // Deallocate our two dimensional array from memory
    for (int i = 0; i < SIZE; i++)
    {
        free(numbers[i]);
    }
    free(numbers);
}
