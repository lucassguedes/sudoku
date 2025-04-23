#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sudoku.h"
#include "cases.h"
#include "data.h"

/**
 * Nome: Sudoku Solution Validator
 * Descrição: Dada uma matriz de sudoku, verifica
 * se a configuração é válida ou não.
 * Última modificação: 4 de abril de 2025
 */

int main(int argc, char **argv)
{

    if (argc < 3){
        printf("\033[0;31mERRO:\033[0m Parâmetros insuficientes! Inclua como argumentos o camimho para os dados e um número que represente um caso teste.\n Ex: ./build/bin/sudoku ./sudoku.csv 2\n");
        exit(0);
    }
    char* data_filepath = argv[1];
    int test_case = atoi(argv[2]);

    
    SudokuInstance* instances = read_dataset(data_filepath);
    
    switch(test_case){
        case 1: case_1(instances, MAX_INSTANCES);break;
        case 2: case_2(instances, MAX_INSTANCES); break;
        case 3: case_3(instances, MAX_INSTANCES); break;
        default: printf("\033[0;31mDigite um caso válido\033[0m\n"); break;
    }

    for(int i = 0; i < MAX_INSTANCES; i++){
        for(int j = 0; j < DIM; j++){
            free(instances[i].matrix[j]);
        }
        free(instances[i].matrix);
    }
    free(instances);
    return 0;
}
