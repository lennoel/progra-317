#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size, n = 10000000;
    int i;
    double local_sum = 0.0, total_sum = 0.0;
    
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    for (i = rank; i < n; i += size) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        local_sum += term;
    }
    
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        double pi = total_sum * 4.0;
        printf("pi: %f\n", pi);
    }
    
    MPI_Finalize();
    return 0;
}
