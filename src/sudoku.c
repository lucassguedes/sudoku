#include "sudoku.h"
#include "utils.h"

/**
 * Nome: row_checker
 * Argumentos: sudoku_data* data
 * Descrição: Esta função verifica todas as linhas da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: Retorna  um  ponteiro  para  int contendo uma das
 * constantes SUDOKU_INVALID ou SUDOKU_VALID.
 */
void* row_checker(void* arg){
    sudoku_data* data = *(sudoku_data**)arg;
    //int* res = (int*)malloc(sizeof(int)); 

    /**
     * row_status:
     * O   número   inteiro  de  16  bits   do   row_status
     * representa    quais    números    existem   na linha 
     * atual.   Cada  bit  em  nível  lógico  alto,  dentre
     * os  9   menos  significativos, representam um número
     * que  está   presente na linha. Bits que correspondem
     * a números que não estão na linha permanecem em nível
     * lógico baixo.
     * 
     * Exemplo: Se a linha tiver apenas os números 5 e 9,
     * o valor em line_status será:
     * 
     * 272 (decimal) = 0000000100010000 (binário)
     */
    uint16_t row_status; 

    for(int row = 0; row < DIM; row++){
        row_status = 0;
        for(int column = 0; column < DIM; column++){
            /**
             * Aqui verificamos se o número atual já foi visto na linha.
             * Fazemos isso através de uma operação AND bitwise.
             */
            if(row_status & (int)pow(2, data->matrix[row][column] - 1))
            {
                printf("\033[0;31mA linha %d é inválida!\033[0m\n", row);
                resp = SUDOKU_INVALID;
            }

            row_status |= (int)pow(2, data->matrix[row][column] - 1);
        }
    }


    pthread_exit(0);
}

/**
 * Nome: column_checker
 * Argumentos: sudoku_data* data
 * Descrição: Esta função verifica todas as colunas da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: Retorna  um  ponteiro  para  int contendo uma das
 * constantes SUDOKU_INVALID ou SUDOKU_VALID.
 */

void* column_checker(void* arg){
    sudoku_data* data = *(sudoku_data**)arg;
    //int* res = (int*)malloc(sizeof(int)); 

    /*Funciona da mesma forma que o row_status*/
    uint16_t column_status; 

    for(int column = 0; column < DIM; column++){
        column_status = 0;
        for(int row = 0; row < DIM; row++){
            /**
             * Aqui verificamos se o número atual já foi visto na coluna.
             * Fazemos isso através de uma operação AND bitwise.
             */
            if(column_status & (int)pow(2, data->matrix[row][column] - 1))
            {
                printf("\033[0;31mA coluna %d é inválida!\033[0m\n", column);
                resp = SUDOKU_INVALID;
            }

            column_status |= (int)pow(2, data->matrix[row][column] - 1);
        }
    }
    pthread_exit(0);
}

/**
 * Nome: square_checker
 * Argumentos: sudoku_data* data, a linha do primeiro elemento do quadrado, a coluna do primeiro elemento do quadrado
 * Descrição: Esta função verifica um quadrado da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: Retorna  um  ponteiro  para  int contendo uma das
 * constantes SUDOKU_INVALID ou SUDOKU_VALID.
 */
 void* square_checker(void * arg){
    sudoku_data* data = (sudoku_data*)arg;
    int col = data->col;
    int line = data->line;

    uint16_t square_status = 0;
    
    for(int i = line; i < line+3; i++){
        for(int j = col; j < col+3; j++){
            /**
             * Aqui verificamos se o numero atual já foi visto no quadrado.
             * Fazemos isso através de uma operação AND bitwise.
            **/
            if(square_status & (int)pow(2, data->matrix[i][j] - 1)){
                printf("\033[0;31mO quadrado tal é inválida!\033[0m\n");
                resp = SUDOKU_INVALID;
            }
            square_status |= (int)pow(2, data->matrix[i][j] -1);
        }
    }
    
    pthread_exit(0);
 }


int** initialize_sudoku_matrix(int* values){
    int **matrix = (int **)malloc(sizeof(int *) * DIM);

    int currval_idx = 0;
    for (int i = 0; i < DIM; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * DIM);
        for (int j = 0; j < DIM; j++)
        {
            matrix[i][j] = values[currval_idx++];
        }
    }

    return matrix;
}