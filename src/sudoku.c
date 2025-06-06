#include "sudoku.h"
#include "utils.h"


int row_checker(ThreadParam * data, int instancia);
int column_checker(ThreadParam * data, int instancia);
int square_checker(ThreadParam* data, int instancia);

/**
 * Nome: destroy_thread_param
 * Esta   função  serve  para  destruir  estruturas  do  tipo  ThreadParam.
 * O parâmetro destroy_instances determina se as instâncias também deve ser
 * destruídas  (há  casos  em  que elas  não devem ser destruidas, pois são 
 * compartilhadas por múltiplos objetos).
 */
void destroy_thread_param(ThreadParam* data, int n_instances, bool destroy_instances){
    if(destroy_instances){
        for(int i = 0; i < n_instances; i++){
            for(int j = 0; j < DIM; j++){
                free(data->instances[i].matrix[j]);
            }
            free(data->instances[i].matrix);
        }
        free(data->instances);
    }
    free(data);
}

/*
 * Nome: initialize_sudoku_matrix
 * Esta função serve para incializar a matriz de cada jogo do sudoku
*/
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
 * Nome: all_row_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função verifica todas as linhas da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 */
void* all_row_checker(void* arg){
    ThreadParam* data = *(ThreadParam**)arg;
    const int n_instances = data->n_instances;
    for(int i = 0; i < n_instances; i++){
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
 * Descrição: Esta função é usada pela thread para verificar todas 
 * as colunas da matriz do   sudoku   em   busca  de  uma  configuração  inválida. 
 */
void* all_column_checker(void* arg){
    ThreadParam* data = *(ThreadParam**)arg;
    const int n_instances = data->n_instances;
    for(int i = 0; i < n_instances; i++){
        for(int column = 0; column < DIM; column++){
            data->col = column;
            int valid = column_checker(data, i);
            if(!valid) data->instances[i].valid = SUDOKU_INVALID;
        }
    }
    pthread_exit(0);
}

/**
 * Nome: one_square_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função é usada pela thread para verificar um quadrado da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 */
 void* one_square_checker(void * arg){
    ThreadParam* data = (ThreadParam*)arg;
    const int n_instances = data->n_instances;
    for(int instance = 0; instance < n_instances; instance++){
        int valid = square_checker(data, instance);
        if(!valid) data->instances[instance].valid = SUDOKU_INVALID;
    }

    pthread_exit(0);
 }

/**
 * Nome: one_column_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função será passada para a thread e verifica uma coluna da matriz 
 */
 void * one_column_checker(void * arg){
    ThreadParam * data = (ThreadParam*)arg;
    const int n_instances = data->n_instances;
    for(int i = 0; i < n_instances; i++){
        int valid = column_checker(data, i);
        if(!valid) data->instances[i].valid = SUDOKU_INVALID;
    }
    pthread_exit(0);
 }

 /**
 * Nome: one_row_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função será passada para a thread e verifica uma linha da matriz 
 */
 void * one_row_checker(void * arg){
    ThreadParam * data = (ThreadParam*)arg;
    const int n_instances = data->n_instances;
    for(int i = 0; i < n_instances; i++){
        int valid = row_checker(data, i);
        if(!valid) data->instances[i].valid = SUDOKU_INVALID;
    }
    pthread_exit(0);
 }


/*
 * Nome:all_validations_checker
 * Esta função verifica o jogo do sudoku inteiro em apenas um fluxo,
 * sendo chamada no caso 3. 
*/
void all_validations_checker(SudokuInstance * instances, int n_instances){
    ThreadParam * data = (ThreadParam *)malloc(sizeof(ThreadParam));
    data->instances = instances;
    for(int instance = 0; instance < n_instances; instance++){
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
    free(data);
}

/**
 * Nome: row_checker
 * Argumentos: ThreadParam* data
 * Descrição: Esta função verifica uma linha da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: Retorna  um int contendo uma das
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
 * Retorno: Retorna  um  int contendo uma das
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

 
 /**
 * Nome: square_checker
 * Argumentos: ThreadParam* data, a linha do primeiro elemento
 * do quadrado, a coluna do primeiro elemento do quadrado
 * Descrição: Esta função verifica um quadrado da matriz
 * do   sudoku   em   busca  de  uma  configuração  inválida. 
 * Retorno: 
 */
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
