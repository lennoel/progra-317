#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, N, M;
    int *local_series, *full_series = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    N = atoi(argv[1]);
    M = atoi(argv[2]);

    int local_size = (N + size - 1) / size; 
    int start = rank * local_size;
    int end = start + local_size > N ? N : start + local_size;

    local_series = (int *)malloc(local_size * sizeof(int));

    // Generar la serie localmente
    for (int i = start, j = 0; i < end; i++, j++) {
        local_series[j] = 2 * (i + 1);
    }


    if (rank == 0) {
        full_series = (int *)malloc(N * sizeof(int));
    }
    
    MPI_Gather(local_series, local_size, MPI_INT, full_series, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // serie
    if (rank == 0) {
        printf("Serie completa: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", full_series[i]);
        }
        printf("\n");
        free(full_series);
    }

    free(local_series);
    MPI_Finalize();
    return 0;
}
