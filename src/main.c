#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sudoku.h"
#include "cases.h"

/**
 * Nome: Sudoku Solution Validator
 * Descrição: Dada uma matriz de sudoku, verifica
 * se a configuração é válida ou não.
 * Última modificação: 4 de abril de 2025
 */
int resp = SUDOKU_VALID;

int main(int argc, char **argv)
{
    if (!argv[1]){
        printf("Inclua um número que representa um caso teste como argumento.\n Ex: ./build/bin/sudoku 2\n");
        exit(0);
    }
    int test_case = atoi(argv[1]);
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

    switch(test_case){
        case 1: case_1(values);break;
        case 2: case_2(values); break;
        default: printf("\033[0;31mDigite um caso válido\033[0m\n"); break;
    }
    return 0;
}
