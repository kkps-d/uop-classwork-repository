/**
 * Kaung Khant Pyae Sone
 * k_kaung@u.pacific.edu
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct puzzle
{
    int height, width;
    char **grid;
    char **solvedGrid;
    char **invalidGrid;
};

struct puzzle create_puzzle(FILE *fp, int width, int height);
void print_puzzle(struct puzzle puzzle, int solved, int highlight_x, int highlight_y);
void print_header();
int valid_input(int row, int col, int value, struct puzzle puzzle);
int invalid_grid(int row, int col, struct puzzle puzzle);
int puzzle_complete(struct puzzle puzzle);
int puzzle_complete_vertical(struct puzzle puzzle);
int puzzle_complete_horizontal(struct puzzle puzzle);
int puzzle_complete_grid(struct puzzle puzzle);
void puzzle_free_memory(struct puzzle puzzle);

#endif