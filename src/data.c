#include "data.h"

int** create_matrix(int dimension){
    int** res = (int**)malloc(sizeof(int*)*DIM);
    
    for(int i = 0; i < DIM; i++){
        res[i] = (int*)malloc(sizeof(int)*DIM);
    }

    return res;
}

void add_empty_instance(SudokuInstance** instances, int* size, int* actual_size){
    /*Adicionando nova instância à lista de instâncias*/
    if(*size == *actual_size){ /*Se o array já estiver cheio, adicionamos mais espaço*/
        *actual_size *= 2;
        *instances = (SudokuInstance*)realloc(*instances, sizeof(SudokuInstance)*(*actual_size));
    }
    (*size)++;
    (*instances)[*size - 1].valid = true;
    (*instances)[*size - 1].matrix = create_matrix(DIM);
}

SudokuInstance* read_dataset(char* filepath, int* n_instances){
    FILE* file = fopen(filepath, "r");

    char byte;
    
    int size, actual_size; /*Variáveis utilizadas para controlar o tamanho da lista de instâncias*/
    SudokuInstance* instances = (SudokuInstance*)malloc(sizeof(SudokuInstance));
    size = actual_size = 1; /*Inicialmente, a lista contém apenas uma instância*/

    instances[size - 1].valid = true; /*Todas as instâncias são válidas até que se prove o contrário*/
    instances[size - 1].matrix = create_matrix(DIM);

    int currline, currcol;
    currline = currcol = 0;
    while((byte = getc(file)) != EOF){

        if(byte == ','){/*Se encontrou uma vírgula*/
            /*Ignoramos os próximos 9 bytes, pois eles correspondem à matriz de solução*/
            for(int i = 0; i < DIM*DIM; i++){
                byte = getc(file);
            }
            /*Adicionando nova instância à lista de instâncias*/
            currline = currcol = 0;
            continue;
        }

        if(byte == '\n'){ /*Se encontrou um final de linha*/
            if(size == *n_instances){
                break;
            }
            /*Adicionando nova instância à lista de instâncias*/
            add_empty_instance(&instances, &size, &actual_size);
            currline = currcol = 0;
            continue;
        }

        instances[size - 1].matrix[currline][currcol] = byte - '0';
        currcol++;

        if(currcol == DIM){
            currcol = 0;
            currline++;
        }

        
    }

    if(byte == EOF){
        size--;
        *n_instances = size;
    }

    printf("size: %d\n", size);

    fclose(file);

    return instances;
}

void print_instance(SudokuInstance* instance){
    printf("\033[0;35mMatriz:\033[0m\n");
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            printf("%d ", instance->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\033[0;35mStatus:\033[0m ");
    if(instance->valid){
        printf("\033[0;32m Válida\033[0m\n");
    }else{
        printf("\033[0;31m Inválida\033[0m\n");
    }
}