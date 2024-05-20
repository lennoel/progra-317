#include <stdio.h>

// sum
void sumar(int *resultado, int a, int b) {
    *resultado = a + b;
}

// rest
void restar(int *resultado, int a, int b) {
    *resultado = a - b;
}

// multi
void multiplicar(int *resultado, int a, int b) {
    *resultado = 0;
    for (int i = 0; i < b; i++) {
        *resultado += a;
    }
}

// div
void dividir(int *res, int a, int b) {
    *res = 0;
    int temp = a;
    while (temp >= b) {
        temp -= b;
        (*res)++;
    }
}

int main() {
    int a, b, x;
    a = 10;
    b = 5;
    sumar(&x, a, b);
    printf("suma: %d + %d = %d\n", a, b, x);

    restar(&x, a, b);
    printf("resta: %d - %d = %d\n", a, b, x);

    multiplicar(&x, a, b);
    printf("multiplica: %d * %d = %d\n", a, b,x);

    dividir(&x, a, b);
    printf("div: %d / %d = %d\n", a, b, x);

    return 0;
}
