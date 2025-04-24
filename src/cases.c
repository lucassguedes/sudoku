#include "cases.h"
#include "sudoku.h"

void case_1(SudokuInstance* instances, int n_instances){

    pthread_t lcid; // ID da thread de verificação das linhas
    pthread_t ccid; // ID da thread de verificação das colunas
    pthread_t scid[DIM]; // array de ID das threads de verificação dos quadrados

    ThreadParam *data = (ThreadParam *)malloc(sizeof(ThreadParam));
    data->instances = instances; //Apenas uma instância

    ThreadParam *data_squares[DIM];
    

    pthread_create(&lcid, NULL, all_row_checker, &data);
    pthread_create(&ccid, NULL, all_column_checker, &data);


    int thread_counter = 0; //irá contabilizar as threads criadas
    for(int i = 0; i < 3; i++){
        int line = i*3; //primeira linha do quadrado
        for(int j = 0; j < 3; j++){
            int column = j*3; //primeira coluna do quadrado

            data_squares[thread_counter] = (ThreadParam *)malloc(sizeof(ThreadParam));
            data_squares[thread_counter]->instances = instances;


            data_squares[thread_counter]->line = line;
            data_squares[thread_counter]->col = column;
            pthread_create(&scid[thread_counter], NULL, one_square_checker, data_squares[thread_counter]);

            thread_counter++;
        }
    }

    void *lc_status = NULL;
    void *cc_status = NULL;
    void ** sc_status = (void **)malloc(sizeof(void *)*DIM);

    for(int i = 0; i < DIM; i++)sc_status[i] = NULL;

    pthread_join(lcid, &lc_status);
    pthread_join(ccid, &cc_status);
    for (int i = 0; i < DIM; i++) {
        pthread_join(scid[i], sc_status[i]);
    }
    
    int n_valid = 0;
    for(int i = 0; i < MAX_INSTANCES; i++){
        if(instances[i].valid){
            n_valid++;
        }
    }
    printf("\033[0;35mInstâncias válidas:\033[0m %d/%d\n", n_valid, MAX_INSTANCES);
    
    destroy_thread_param(data, false);
    free(lc_status);
    free(cc_status);
    for(int i = 0; i < DIM; i++)
        free(sc_status[i]);
    free(sc_status);

    for(int i = 0; i < DIM; i++)
        destroy_thread_param(data_squares[i], false);
    
}

void case_2(SudokuInstance* instances, int n_instances){

    ThreadParam * data_columns[DIM];
    ThreadParam * data_lines[DIM];
    ThreadParam * data_squares[DIM];

    pthread_t lcid[DIM]; // ID da thread de verificação das linhas
    pthread_t ccid[DIM]; // ID da thread de verificação das colunas
    pthread_t scid[DIM]; // array de ID das threads de verificação dos quadrados

    //CODIGO DE UMA THREAD POR COLUNA

    for(int col = 0; col < DIM; col++){
        data_columns[col] = (ThreadParam *)malloc(sizeof(ThreadParam));
        data_columns[col]->instances = instances;
        data_columns[col]->col = col;
        pthread_create(&ccid[col], NULL, one_column_checker, data_columns[col]);
    }

    for(int row = 0; row < DIM; row++){
        data_lines[row] = (ThreadParam *)malloc(sizeof(ThreadParam));
        data_lines[row]->instances = instances;
        data_lines[row]->line = row;
        pthread_create(&lcid[row], NULL, one_row_checker, data_lines[row]);
    }

    int thread_counter = 0; //irá contabilizar as threads criadas
    for(int i = 0; i < 3; i++){
        int line = i*3; //primeira linha do quadrado
        for(int j = 0; j < 3; j++){
            int column = j*3; //primeira coluna do quadrado

            data_squares[thread_counter] = (ThreadParam *)malloc(sizeof(ThreadParam));
            data_squares[thread_counter]->instances = instances;
            data_squares[thread_counter]->line = line;
            data_squares[thread_counter]->col = column;
            pthread_create(&scid[thread_counter], NULL, one_square_checker, data_squares[thread_counter]);
            thread_counter++;
        }
    }

    void ** cc_status = (void **)malloc(sizeof(void *)*DIM);
    void ** lc_status = (void **)malloc(sizeof(void*)*DIM);
    void ** sc_status = (void **)malloc(sizeof(void *)*DIM);

    for(int i = 0; i < DIM; i++){
        cc_status[i] = NULL;
        lc_status[i] = NULL;
        sc_status[i] = NULL;
    }


    for (int i = 0; i < DIM; i++) {
        pthread_join(ccid[i], cc_status[i]);
        pthread_join(lcid[i], lc_status[i]);
        pthread_join(scid[i], sc_status[i]);
    }

    int n_valid = 0;
    for(int i = 0; i < MAX_INSTANCES; i++){
        if(instances[i].valid){
            n_valid++;
        }
    }

    printf("\033[0;35mInstâncias válidas:\033[0m %d/%d\n", n_valid, MAX_INSTANCES);


    free(cc_status);
    free(sc_status);
    free(lc_status);


    for(int i = 0; i < DIM; i++){
        destroy_thread_param(data_columns[i], false);
        destroy_thread_param(data_lines[i], false);
        destroy_thread_param(data_squares[i], false);
    }
}

void case_3(SudokuInstance* instances, int n_instances){
    all_validations_checker(instances);

    int n_valid = 0;
    for(int i = 0; i < MAX_INSTANCES; i++){
        if(instances[i].valid){
            n_valid++;
        }
    }

    printf("\033[0;35mInstâncias válidas:\033[0m %d/%d\n", n_valid, MAX_INSTANCES);

}