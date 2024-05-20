#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    int rank, size, n;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Cuantos terminos de Fibonacci? ");
        scanf("%d", &n);

        
        for (int i = 1; i < size; i++) {
            MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        int term;
        for (int i = 0; i < n; i++) {
            MPI_Recv(&term, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("fibo(%d) = %d\n", i, term);
        }
    } else {
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = rank - 1; i < n; i += size - 1) {
            int term = fibonacci(i);
            MPI_Send(&term, 1, MPI_INT, 0, i, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
