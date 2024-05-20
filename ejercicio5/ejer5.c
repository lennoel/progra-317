#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void print_vector(int *vector, int x) {
    for (int i = 0; i < x; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void print_matr(int **matriz, int x) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    int N = 4;  
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != N) {
        if (rank == 0) {
            printf("El número de procesos debe ser igual a %d.\n", N);
        }
        MPI_Finalize();
        return -1;
    }

    int *vector = (int*)malloc(N * sizeof(int));
    int *res = (int*)malloc(N * sizeof(int));
    int *mat = (int*)malloc(N * sizeof(int));
    int *resultado_final = NULL;

    if (rank == 0) {
       
        int **matriz = (int**)malloc(N * sizeof(int*));
        for (int i = 0; i < N; i++) {
            matriz[i] = (int*)malloc(N * sizeof(int));
        }

        // Rellenar la matriz y el vector con algunos valores
        int valor = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matriz[i][j] = valor++;
            }
        }

        for (int i = 0; i < N; i++) {
            vector[i] = 1;
        }

        printf("Matriz:\n");
        print_matr(matriz, N);
        printf("Vector:\n");
        print_vector(vector, N);

  
        for (int i = 0; i < N; i++) {
            MPI_Send(matriz[i], N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        resultado_final = (int*)malloc(N * sizeof(int));
        
       
        for (int i = 0; i < N; i++) {
            free(matriz[i]);
        }
        free(matriz);
    }


    MPI_Recv(mat, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

 
    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);
    res[rank] = 0;
    for (int j = 0; j < N; j++) {
        res[rank] += mat[j] * vector[j];
    }

    MPI_Gather(&res[rank], 1, MPI_INT, resultado_final, 1, MPI_INT, 0, MPI_COMM_WORLD);

// print fin
    if (rank == 0) {
        
        printf("Resultado:\n");
        print_vector(resultado_final, N);
        free(resultado_final);
    }

    free(vector);
    free(res);
    free(mat);

    MPI_Finalize();
    return 0;
}
