#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaración de funciones

void allocateMatrix(int ***matrix, int size){
    *matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        (*matrix)[i] = (int *)malloc(size * sizeof(int));
    }
}


void fillMatrix(int **matrix, int size){
    srand(time(NULL)); // Inicializa la semilla para números aleatorios
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = rand() % 2; // Genera 0 o 1 aleatoriamente
        }
    }
}

void findLargestLine(int **matrix, int size, int *result) {
    *result = 0;  // Inicializa el resultado en 0
    int current_sequence = 0;

    for (int i = 0; i < size; i++) {
        current_sequence = 0;
        for (int j = 0; j < size; j++) {
            if (*(*(matrix + i) + j) == 1) {
                current_sequence++;
                if (current_sequence > *result) {
                    *result = current_sequence;
                }
            } else {
                current_sequence = 0;
            }
        }
    }
}

void transposeMatrix(int **matrix, int ***transposedMatrix, int size){
    allocateMatrix(transposedMatrix, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(*transposedMatrix + j) + i) = *(*(matrix + i) + j);
        }
    }
}

void printMatrix(int **matrix, int size){
    printf("Matrix (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

void freeMatrix(int **matrix, int size){
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


int main() {
    // Declaraciones
    int size, largestLine;
    int **matrix = NULL, **transposedMatrix = NULL;

    printf("Ingrese el tamaño de la matriz: ");
    scanf("%d", &size);

    // Llamadas a las funciones
    allocateMatrix(&matrix, size);
    fillMatrix(matrix, size);
    printf("Matriz original:\n");
    printMatrix(matrix, size);

    findLargestLine(matrix, size, &largestLine);
    printf("La secuencia de 1s más larga en la matriz es: %d\n", largestLine);

    transposeMatrix(matrix, &transposedMatrix, size);
    printf("Matriz transpuesta:\n");
    printMatrix(transposedMatrix, size);

    findLargestLine(transposedMatrix, size, &largestLine);
    printf("La secuencia de 1s más larga en la transpuesta es: %d\n", largestLine);

    // Liberar memoria
    freeMatrix(matrix, size);
    freeMatrix(transposedMatrix, size);

    return 0;
}



