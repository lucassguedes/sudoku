#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sudoku.h"

/**
 * Nome: Sudoku Solution Validator
 * Descrição: Dada uma matriz de sudoku, verifica
 * se a configuração é válida ou não.
 * Última modificação: 4 de abril de 2025
 */

int main(int argc, char **argv)
{
    /*Estado inicial da matriz*/
    int values[] = {5, 3, 0, 0, 7, 0, 0, 0, 0,
                    6, 0, 0, 1, 9, 5, 0, 0, 0,
                    0, 9, 8, 0, 0, 0, 0, 6, 0,
                    8, 0, 0, 0, 6, 0, 0, 0, 3,
                    4, 0, 0, 8, 0, 3, 0, 0, 1,
                    7, 0, 0, 0, 2, 0, 0, 0, 6,
                    0, 6, 0, 0, 0, 0, 2, 8, 0,
                    0, 0, 0, 4, 1, 9, 0, 0, 5,
                    0, 0, 0, 0, 8, 0, 0, 7, 9};

    pthread_t lcid; // ID da thread de verificação das linhas
    pthread_t ccid; // ID da thread de verificação das colunas

    int** matrix = initialize_sudoku_matrix(values);

    sudoku_data *data = (sudoku_data *)malloc(sizeof(sudoku_data));

    data->matrix = matrix;
    data->row = 5;
    data->column = 8;

    pthread_create(&lcid, NULL, row_checker, &data);
    pthread_create(&ccid, NULL, column_checker, &data);

    void *lc_status = NULL;
    void *cc_status = NULL;

    pthread_join(lcid, &lc_status);
    pthread_join(ccid, &cc_status);


    if(*((int *)lc_status) == SUDOKU_VALID){
        printf("\033[0;32mTodas as linhas são válidas!\033[0m\n");
    }else{
        printf("\033[0;31mHá uma ou mais linhas inválidas!\033[0m\n");
    }

    if(*((int *)cc_status) == SUDOKU_VALID)
    {
        printf("\033[0;32mTodas as colunas são válidas!\033[0m\n");
    }else{
        printf("\033[0;31mHá uma ou mais colunas inválidas!\033[0m\n");
    }


    for(int i = 0; i < DIM; i++){
        free(matrix[i]);
    }
    free(matrix);
    free(data);
    free(lc_status);
    free(cc_status);

    return 0;
}