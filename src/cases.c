#include "cases.h"

void case_1(int * values){

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
    
}