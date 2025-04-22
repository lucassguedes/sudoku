#ifndef __VALIDATOR_H__
#define __VALIDATOR_H__
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>
#include "data.h"

#define DIM 9

enum{
    SUDOKU_VALID,
    SUDOKU_INVALID
};

typedef struct{
    int line;
    int col;
    SudokuInstance* instances; //Lista de instâncias
}sudoku_data;

extern int resp;


void* all_row_checker(void* arg);
void* all_column_checker(void* arg);
void* square_checker(void * arg);
void* one_column_checker(void * arg);
void* one_row_checker(void * arg);

int** initialize_sudoku_matrix(int* values);


void destroy_sudoku_data(sudoku_data* data, bool destroy_matrix);






#endif 