#ifndef __DATA_H__
#define __DATA_H__
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM 9
#define MAX_INSTANCES 450000

typedef struct {
    bool valid; /*Indica se a instância é ou não válida*/
    int** matrix;
}SudokuInstance;

SudokuInstance* read_dataset(char* filepath);
void            print_instance(SudokuInstance* instance);





#endif