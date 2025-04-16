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

int resp = SUDOKU_VALID;

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
    pthread_t scid[DIM]; // array de ID das threads de verificação dos quadrados

    int** matrix = initialize_sudoku_matrix(values);

    sudoku_data *data = (sudoku_data *)malloc(sizeof(sudoku_data));
    sudoku_data *data_squares[DIM];
    data->matrix = matrix;

    pthread_create(&lcid, NULL, row_checker, &data);
    pthread_create(&ccid, NULL, column_checker, &data);

    int thread_counter = 0; //irá contabilizar as threads criadas
    for(int i = 0; i < 3; i++){
        int line = i*3; //primeira linha do quadrado
        for(int j = 0; j < 3; j++){
            int column = j*3; //primeira coluna do quadrado

            data_squares[thread_counter] = (sudoku_data *)malloc(sizeof(sudoku_data));
            data_squares[thread_counter]->matrix = matrix;
            data_squares[thread_counter]->line = line;
            data_squares[thread_counter]->col = column;
            pthread_create(&scid[thread_counter], NULL, square_checker, data_squares[thread_counter]);
            thread_counter++;
        }
    }

    void *lc_status = NULL;
    void *cc_status = NULL;
    void ** sc_status = (void **)malloc(sizeof(void *)*9);

    pthread_join(lcid, &lc_status);
    pthread_join(ccid, &cc_status);
    for (int i = 0; i < 9; i++) {
        pthread_join(scid[i], sc_status[i]);
    }
    
    
    if(resp == SUDOKU_VALID){
        printf("\033[0;32mO jogo é válido!\033[0m\n");
    }else{
        printf("\033[0;31mO jogo não é válido!\033[0m\n");
    }
    

    for(int i = 0; i < DIM; i++){
        free(matrix[i]);
    }
    free(matrix);
    free(data);
    free(lc_status);
    free(cc_status);
    for(int i = 0; i < DIM; i++)
        free(data_squares[i]);

    return 0;
}