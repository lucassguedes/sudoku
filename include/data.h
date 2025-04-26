#ifndef __DATA_H__
#define __DATA_H__
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM 9

typedef struct {
    bool valid; /*Indica se a instância é ou não válida*/
    int** matrix;
}SudokuInstance;

SudokuInstance* read_dataset(char* filepath, int n_instances);
void            print_instance(SudokuInstance* instance);





#endif