#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__
#include <stdlib.h>
#include <stdint.h>
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

void* row_checker(void* arg);
void* column_checker(void* arg);

int** initialize_sudoku_matrix(int* values);






#endif 