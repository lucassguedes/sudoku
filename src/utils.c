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