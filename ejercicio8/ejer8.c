#include <stdio.h>
#include <omp.h>

int main() {
    int n, m;

    // pedir  n y m
    printf("introduce n: ");
    scanf("%d", &n);
    printf("introduce m: ");
    scanf("%d", &m);

    int serie[n];

   
    #pragma omp parallel for num_threads(m)
    for (int i = 0; i < n; i++) {
        serie[i] = (i + 1) * 2;
    }

    // print
    #pragma omp parallel for num_threads(m)
    for (int i = 0; i < m; i++) {
        int thread_id = omp_get_thread_num();
        printf("proceso %d: ", thread_id + 1);
        for (int j = 0; j < n; j++) {
            printf("%d ", serie[j]);
        }
        printf("\n");
    }

    return 0;
}
