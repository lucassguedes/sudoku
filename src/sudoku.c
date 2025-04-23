#include "sudoku.h"
#include "utils.h"


int row_checker(ThreadParam * data, int instancia);
int column_checker(ThreadParam * data, int instancia);
int square_checker(ThreadParam* data, int instancia);

/**
 * Esta   função  serve  para  destruir  estruturas  do  tipo  ThreadParam.
 * O parâmetro destroy_instances determina se as instâncias também deve ser
 * destruídas  (há  casos  em  que elas  não devem ser destruidas, pois são 
 * compartilhadas por múltiplos objetos).
 */
void destroy_thread_param(ThreadParam* data, bool destroy_instances){
    if(destroy_instances){
        for(int i = 0; i < MAX_INSTANCES; i++){
            for(int j = 0; j < DIM; j++){
                free(data->instances[i].matrix[j]);
            }
            free(data->instances[i].matrix);
        }
        free(data->instances);
    }
    free(data);
}


/**
 * Nome: all_row_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função verifica todas as linhas da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno:
 * constantes SUDOKU_INVALID ou SUDOKU_VALID.
 */
void* all_row_checker(void* arg){
    ThreadParam* data = *(ThreadParam**)arg;

    for(int i = 0; i < MAX_INSTANCES; i++){
        for(int row = 0; row < DIM; row++){
            data->line = row;
            int valido = row_checker(data, i);
            if(!valido){
                data->instances[i].valid = SUDOKU_INVALID;
            }
        }
    }

    pthread_exit(0);
}

/**
 * Nome: all_column_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função verifica todas as colunas da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: 
 */
void* all_column_checker(void* arg){
    ThreadParam* data = *(ThreadParam**)arg;

    for(int i = 0; i < MAX_INSTANCES; i++){
        for(int column = 0; column < DIM; column++){
            data->col = column;
            int valid = column_checker(data, i);
            if(!valid) data->instances[i].valid = SUDOKU_INVALID;
        }
    }
    pthread_exit(0);
}

/**
 * Nome: square_checker
 * Argumentos: ThreadParam* data, a linha do primeiro elemento do quadrado, a coluna do primeiro elemento do quadrado
 * Descrição: Esta função verifica um quadrado da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: 
 */
 void* one_square_checker(void * arg){
    ThreadParam* data = (ThreadParam*)arg;

    for(int instance = 0; instance < MAX_INSTANCES; instance++){
        int valid = square_checker(data, instance);
        if(!valid) data->instances[instance].valid = SUDOKU_INVALID;
    }

    pthread_exit(0);
 }
 
 int square_checker(ThreadParam* data, int instancia){
    int col = data->col;
    int line = data->line;
    uint16_t square_status = 0;
    int** matrix = data->instances[instancia].matrix; 
    for(int i = line; i < line+3; i++){
        for(int j = col; j < col+3; j++){
            /**
            * Aqui verificamos se o numero atual já foi visto no quadrado.
            * Fazemos isso através de uma operação AND bitwise.
            **/
            if(square_status & (int)pow(2,matrix[i][j] - 1)){
                printf("\033[0;31mO quadrado %d é inválido!\033[0m\n", which_square(line, col)+1);
                return SUDOKU_INVALID;
            }
            square_status |= (int)pow(2,matrix[i][j] -1);
        }
    }
    return SUDOKU_VALID;
 }

/**
 * Nome: one_column_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função será passada para a thread e verifica uma coluna da matriz 
 * Retorno: 
 */
 void * one_column_checker(void * arg){
    ThreadParam * data = (ThreadParam*)arg;
    for(int i = 0; i < MAX_INSTANCES; i++){
        int valid = column_checker(data, i);
        if(!valid) data->instances[i].valid = SUDOKU_INVALID;
    }
    pthread_exit(0);
 }

 /**
 * Nome: one_row_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função será passada para a thread e verifica uma linha da matriz 
 * Retorno: 
 */
 void * one_row_checker(void * arg){
    ThreadParam * data = (ThreadParam*)arg;
    for(int i = 0; i < MAX_INSTANCES; i++){
        int valid = row_checker(data, i);
        if(!valid) data->instances[i].valid = SUDOKU_INVALID;
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

/**
 * Nome: row_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função verifica uma linha da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: Retorna  um  ponteiro  para  int contendo uma das
 * constantes SUDOKU_INVALID ou SUDOKU_VALID.
 */

 int row_checker(ThreadParam * data, int instancia){
   
    int row = data->line;
    uint16_t row_status = 0;  
    int** matrix = data->instances[instancia].matrix; //Considerando que há apenas uma instância

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
        
    for(int column = 0; column < DIM; column++){
        /**
         * Aqui verificamos se o número atual já foi visto na linha.
         * Fazemos isso através de uma operação AND bitwise.
         */
        if(row_status & (int)pow(2, matrix[row][column] - 1))
        {
            printf("\033[0;31mA linha %d é inválida!\033[0m\n", row+1);
            return SUDOKU_INVALID;
        }
        
        row_status |= (int)pow(2, matrix[row][column] - 1);
        
    }
    return SUDOKU_VALID;
}

/**
 * Nome: column_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função verifica uma linha da coluna
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: Retorna  um  ponteiro  para  int contendo uma das
 * constantes SUDOKU_INVALID ou SUDOKU_VALID.
 */

int column_checker(ThreadParam * data, int instancia){
    int column = data->col;
    uint16_t column_status = 0; 
    int** matrix = data->instances[instancia].matrix; //Considerando que há apenas uma instância

    /*Funciona da mesma forma que o row_status*/

    for(int row = 0; row < DIM; row++){
        /**
         * Aqui verificamos se o número atual já foi visto na coluna.
         * Fazemos isso através de uma operação AND bitwise.
         */
        if(column_status & (int)pow(2, matrix[row][column] - 1))
        {
            printf("\033[0;31mA coluna %d é inválida!\033[0m\n", column+1);
            return SUDOKU_INVALID;
        }

        column_status |= (int)pow(2, matrix[row][column] - 1);
    }
    return SUDOKU_VALID;
}

void all_validations_checker(SudokuInstance * instances){
    ThreadParam * data = (ThreadParam *)malloc(sizeof(ThreadParam));
    data->instances = instances;
    for(int instance = 0; instance < MAX_INSTANCES; instance++){
        for(int i = 0; i < DIM; i++){
            // checa as colunas
            data->col = i;
            int valid = column_checker(data, instance);
            if(!valid) data->instances[instance].valid = SUDOKU_INVALID;
        }
        for(int i = 0; i < DIM; i++){
            // checa as colunas
            data->line = i;
            int valid = row_checker(data, instance);
            if(!valid) data->instances[instance].valid = SUDOKU_INVALID;
        }
        for(int i = 0; i < 3; i++){
            int line = i*3; //primeira linha do quadrado
            for(int j = 0; j < 3; j++){
                int column = j*3; //primeira coluna do quadrado
                data->line = line;
                data->col = column;
                int valid = square_checker(data, instance);
                if(!valid) data->instances[instance].valid = SUDOKU_INVALID;
            }
        }

    }
}