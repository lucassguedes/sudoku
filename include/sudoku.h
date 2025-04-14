#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

#define DIM 9

enum{
    SUDOKU_VALID,
    SUDOKU_INVALID
};

typedef struct{
    int row;
    int column;
    int** matrix;
}sudoku_data;

typedef struct {
    sudoku_data* data;
    int col;
    int line;
} square_args;

extern int resp;


void* row_checker(void* arg);
void* column_checker(void* arg);
void* square_checker(void * arg);

int** initialize_sudoku_matrix(int* values);






#endif 