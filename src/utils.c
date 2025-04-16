#include "utils.h"

void show_matrix(int** matrix, int dim)
{
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int which_square(int line, int column){
    return (line/3)*3 + column/3;
}