#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
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
        printf("\033[0;31mERRO:\033[0m Parâmetros insuficientes! Inclua como argumentos o caminho para os dados e um número que represente um caso teste.\n Ex: ./build/bin/sudoku ./sudoku.csv 2\n");
        exit(0);
    }
    char* data_filepath = argv[1];
    int test_case = atoi(argv[2]);
    struct timeval start, end;

    // lê arquivo
    SudokuInstance* instances = read_dataset(data_filepath);

    int cont = 0;
    double total_time = 0;

    while (cont < 10){
        gettimeofday(&start, NULL); // começa a contagem do tempo
    
        switch(test_case){
            case 1: case_1(instances, MAX_INSTANCES);break;
            case 2: case_2(instances, MAX_INSTANCES); break;
            case 3: case_3(instances, MAX_INSTANCES); break;
            default: printf("\033[0;31mDigite um caso válido\033[0m\n"); break;
        }

        gettimeofday(&end, NULL);
        long seconds = end.tv_sec - start.tv_sec;
        long microseconds = end.tv_usec - start.tv_usec;
        total_time += seconds + microseconds / 1e6; //acúmulo dos tempos de execução
        
        cont++;
    }

    
    printf("Time taken: %.6f seconds\n", total_time/10); //printa a média

    //libera a memória
    for(int i = 0; i < MAX_INSTANCES; i++){
        for(int j = 0; j < DIM; j++){
            free(instances[i].matrix[j]);
        }
        free(instances[i].matrix);
    }
    free(instances);
    return 0;
}
