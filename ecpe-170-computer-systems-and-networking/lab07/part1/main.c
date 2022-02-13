#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
    uint32_t array1[3][5];    // 2D array
    uint32_t array2[2][3][5]; // 3D array

    printf("Memory address of two dimensional array array1[3][5] printed in row order\n");
    printf("             0              1              2              3              4\n");
    for (int row = 0; row < 3; row++)
    {
        printf("%i     ", row);
        for (int col = 0; col < 5; col++)
        {
            /* code */
            printf("%p ", &array1[row][col]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Memory addresses of row 1 col 4 to row 2 col 2:\n");
    printf("Row 1 col 4: %p\n", &array1[0][3]);
    printf("Row 1 col 5: %p\n", &array1[0][4]);
    printf("Row 2 col 1: %p\n", &array1[1][0]);
    printf("Row 2 col 2: %p\n", &array1[1][1]);

    printf("Last three hexadecimals show that the memory addresses are adjacent to each other in memory.\n");
    printf("Row 1 col 5 and row 2 col 1 are adjacent in memory.\n");
    printf("C reads two dimensional array rowwise and stores it in one dimensional memory\n\n");

    printf("Memory address of three dimensional array array3[2][3][5] printed in row order\n");
    printf("Block 1\n");
    printf("             0              1              2              3              4\n");
    for (int row = 0; row < 3; row++)
    {
        printf("%i     ", row);
        for (int col = 0; col < 5; col++)
        {
            printf("%p ", &array2[0][row][col]);
        }
        printf("\n");
    }

    printf("\nBlock 2\n");
    printf("             0              1              2              3              4\n");
    for (int row = 0; row < 3; row++)
    {
        printf("%i     ", row);
        for (int col = 0; col < 5; col++)
        {
            printf("%p ", &array2[1][row][col]);
        }
        printf("\n");
    }

    printf("\nMemory addresses of block 1 row 3 col 5 to block 2 row 1 col 1:\n");
    printf("Block 1 row 3 col 5: %p\n", &array2[0][2][4]);
    printf("Block 2 row 1 col 1: %p\n", &array2[1][0][0]);

    printf("Last two hexadecimals show that they are apart by 4 bytes and adjacent to each other.\n");
    printf("Block 1 row 3 col 5 and block 2 row 1 col 1 are adjacent in memory.\n");
    printf("C treats each block like a two dimensional array and continuosly reads all the blocks.\n\n");

}