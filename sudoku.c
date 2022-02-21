#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "uarray2.h"
#include "assert.h"
#include "pnmrdr.h"
#include "fileio.h"
#include "except.h"

UArray2_T read_in_PGM(FILE *fp);
UArray2_T read_in_board(Pnmrdr_T rdr, Pnmrdr_mapdata data);
void check_row_digits(int col, int row, UArray2_T board, void *val, void *cl);
void check_col_digits(int col, int row, UArray2_T board, void *val, void *cl);
void check_submap(UArray2_T board, int col, int row);
void clear_array(int *arr);

int main(int argc, char *argv[])
{

    /* error checking, expect 2 arguments from command line */
    assert(argc <= 2);
    
    FILE *fp = argc == 2 ? fileopen(argv[1]) : stdin;
    if (fp == stdin) {
        if ()
    }

    assert(fp != NULL);

    UArray2_T sudoku = read_in_PGM(fp);
    
    fileclose(fp);

    int row_check[9] = {0};
    UArray2_map_row_major(sudoku, check_row_digits, &row_check);

    int col_check[9] = {0};
    UArray2_map_col_major(sudoku, check_col_digits, &col_check);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            check_submap(sudoku, (i * 3), (j * 3));
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", *((int *)UArray2_at(sudoku, j, i)));
        }
        printf("\n");
    }

    UArray2_free(&sudoku);
    exit(EXIT_SUCCESS);
}


void check(bool e, UArray2_T sudoku)
{
    if (!e) {
        UArray2_free(&sudoku);
        exit(EXIT_FAILURE);
    }
}

UArray2_T read_in_PGM(FILE *fp)
{
    /* create the Pnmrdr_T rdr */
    Pnmrdr_T rdr = Pnmrdr_new(fp);
    Pnmrdr_mapdata data = Pnmrdr_data(rdr);
    
    /* check to make sure image is pgm */
    assert(data.type == Pnmrdr_gray);
    
    /* exit if incorrect pgm dimensions */
    if ((data.width != 9) || (data.height != 9) || (data.denominator != 9)) {
        Pnmrdr_free(&rdr);
        exit(EXIT_FAILURE);
    }

    UArray2_T sudoku = read_in_board(rdr, data);

    Pnmrdr_free(&rdr);

    return sudoku;
}

UArray2_T read_in_board(Pnmrdr_T rdr, Pnmrdr_mapdata data)
{
    /* make new array with correct dimensions */
    UArray2_T board = UArray2_new(data.width, data.height, sizeof(int)); // sizeof -> size_t???
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            unsigned n = Pnmrdr_get(rdr);
            assert(n <= data.denominator);
            *((int *)UArray2_at(board, j, i)) = n;
        }
    }

    return board;
}

void check_row_digits(int col, int row, UArray2_T board, void *val, void *cl)
{   
    int curr = *(int *)val;
    check(curr > 0, board);
    int *visited = (int *)cl;
    check(visited[curr - 1] == 0, board);
    visited[curr - 1]++;


    if (col == UArray2_width(board) - 1) {
        clear_array(visited);
    }

    (void)row;

}

void check_col_digits(int col, int row, UArray2_T board, void *val, void *cl)
{
    int curr = *(int *)val;
    int *visited = (int *)cl;
    check(visited[curr - 1] == 0, board);
    visited[curr - 1]++;


    if (row == UArray2_height(board) - 1) {
        clear_array(visited);
    }

    (void)col;

}

void check_submap(UArray2_T board, int col, int row)
{
    int visited[9] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int curr = *(int *)UArray2_at(board, j+col, i+row);
            check(visited[curr - 1] == 0, board);
            visited[curr - 1]++;
        }
    }
}


void clear_array(int *arr)
{
    for (int i = 0; i < 9; i++) {
        arr[i] = 0;
    }
}