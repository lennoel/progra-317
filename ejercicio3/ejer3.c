#include <stdio.h>
#include <omp.h>

// 3.	En openMP realice la multiplicación y división en base a sumas y restas.
void mult(int a, int b, int* result) {
    *result = 0;
    int result2 = 0;

    #pragma omp parallel for reduction(+: result2)
    for (int i = 0; i < b; i++) {
        result2 += a;
    }

    *result = result2;
}

// divisin en base a restas
void div(int a, int b, int* cociente) {
    *cociente = 0;
    int temp = a;

    #pragma omp parallel
    {
        int cociente2 = 0;
        #pragma omp for
        for (int i = 0; i < a; ++i) {
            if (temp >= b) {
                #pragma omp critical
                {
                    if (temp >= b) {
                        temp -= b;
                        cociente2++;
                    }
                }
            }
        }
        #pragma omp atomic
        *cociente += cociente2;
    }
}

int main() {
    int a = 15;
    int b = 3;
    int x;

    // multiplicacion
    mult(a, b, &x);
    printf("multiplicacion: %d * %d = %d\n", a, b, x);

    // division
    div(a, b, &x);
    printf("dibision: %d / %d = %d\n", a, b, x);

    return 0;
}
