#include "cases.h"

void case_1(int * values){

    pthread_t lcid; // ID da thread de verificação das linhas
    pthread_t ccid; // ID da thread de verificação das colunas
    pthread_t scid[DIM]; // array de ID das threads de verificação dos quadrados


    int** matrix = initialize_sudoku_matrix(values);

    sudoku_data *data = (sudoku_data *)malloc(sizeof(sudoku_data));

    data->instances = (SudokuInstance*)malloc(sizeof(SudokuInstance)); //Apenas uma instância
    data->instances[0].matrix = matrix;


    sudoku_data *data_squares[DIM];
    

    pthread_create(&lcid, NULL, all_row_checker, &data);
    pthread_create(&ccid, NULL, all_column_checker, &data);


    int thread_counter = 0; //irá contabilizar as threads criadas
    for(int i = 0; i < 3; i++){
        int line = i*3; //primeira linha do quadrado
        for(int j = 0; j < 3; j++){
            int column = j*3; //primeira coluna do quadrado

            data_squares[thread_counter] = (sudoku_data *)malloc(sizeof(sudoku_data));
            data_squares[thread_counter]->instances = (SudokuInstance*)malloc(sizeof(SudokuInstance)); //Apenas uma instância
            data_squares[thread_counter]->instances[0].matrix = matrix;


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
    destroy_sudoku_data(data, false);
    free(lc_status);
    free(cc_status);
    for(int i = 0; i < DIM; i++)
        free(sc_status[i]);

    for(int i = 0; i < DIM; i++)
        destroy_sudoku_data(data_squares[i], false);
    
}

void case_2(int * values){

    int** matrix = initialize_sudoku_matrix(values);

    sudoku_data * data_columns[DIM];
    sudoku_data * data_lines[DIM];
    sudoku_data * data_squares[DIM];

    pthread_t lcid[DIM]; // ID da thread de verificação das linhas
    pthread_t ccid[DIM]; // ID da thread de verificação das colunas
    pthread_t scid[DIM]; // array de ID das threads de verificação dos quadrados

    //CODIGO DE UMA THREAD POR COLUNA

    for(int col = 0; col < DIM; col++){
        data_columns[col] = (sudoku_data *)malloc(sizeof(sudoku_data));
        data_columns[col]->instances = (SudokuInstance*)malloc(sizeof(SudokuInstance)); //Apenas uma instância
        data_columns[col]->instances[0].matrix = matrix;
        data_columns[col]->col = col;
        pthread_create(&ccid[col], NULL, one_column_checker, data_columns[col]);
    }

    for(int row = 0; row < DIM; row++){
        data_lines[row] = (sudoku_data *)malloc(sizeof(sudoku_data));
        data_lines[row]->instances = (SudokuInstance*)malloc(sizeof(SudokuInstance)); //Apenas uma instância
        data_lines[row]->instances[0].matrix = matrix;
        data_lines[row]->line = row;
        pthread_create(&lcid[row], NULL, one_row_checker, data_lines[row]);
    }

    int thread_counter = 0; //irá contabilizar as threads criadas
    for(int i = 0; i < 3; i++){
        int line = i*3; //primeira linha do quadrado
        for(int j = 0; j < 3; j++){
            int column = j*3; //primeira coluna do quadrado

            data_squares[thread_counter] = (sudoku_data *)malloc(sizeof(sudoku_data));
            data_squares[thread_counter]->instances = (SudokuInstance*)malloc(sizeof(SudokuInstance)); //Apenas uma instância
            data_squares[thread_counter]->instances[0].matrix = matrix;
            data_squares[thread_counter]->line = line;
            data_squares[thread_counter]->col = column;
            pthread_create(&scid[thread_counter], NULL, square_checker, data_squares[thread_counter]);
            thread_counter++;
        }
    }

    void ** cc_status = (void **)malloc(sizeof(void *)*9);
    void ** lc_status = (void **)malloc(sizeof(void*)*9);
    void ** sc_status = (void **)malloc(sizeof(void *)*9);


    for (int i = 0; i < 9; i++) {
        pthread_join(ccid[i], cc_status[i]);
        pthread_join(lcid[i], lc_status[i]);
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
    free(cc_status);
    free(sc_status);
    free(lc_status);

    for(int i = 0; i < DIM; i++){
        destroy_sudoku_data(data_columns[i], false);
        destroy_sudoku_data(data_lines[i], false);
        destroy_sudoku_data(data_squares[i], false);
    }
}