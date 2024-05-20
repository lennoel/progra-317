#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void multiplicamv(int** matriz, int* vector, int* resultado, int N) {
    
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        resultado[i] = 0;
    }

    // multiplicamos la matriz por el vector en paralelo
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            #pragma omp atomic
            resultado[i] += matriz[i][j] * vector[j];
        }
    }
}

int main() {
    int N;

    
    printf("ingrese tamaño  matriz y vector: ");
    scanf("%d", &N);

    
    int** matriz = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; ++i) {
        matriz[i] = (int*)malloc(N * sizeof(int));
    }
    int* vector = (int*)malloc(N * sizeof(int));
    int* resultado = (int*)malloc(N * sizeof(int));

    
    printf("introdusca la matriz (%d x %d):\n", N, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &matriz[i][j]);
        }
    }

    printf("introdusca el vector (%d):\n", N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &vector[i]);
    }

    
    multiplicamv(matriz, vector, resultado, N);

    // print
    printf("Resultado:\n");
    for (int i = 0; i < N; ++i) {
        printf("%d\n", resultado[i]);
    }

  
    for (int i = 0; i < N; ++i) {
        free(matriz[i]);
    }
    free(matriz);
    free(vector);
    free(resultado);

    return 0;
}
