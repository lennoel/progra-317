#include <iostream>


void sumar(int &resultado, int a, int b) {
    resultado = a + b;
}

void restar(int &resultado, int a, int b) {
    resultado = a - b;
}


void multiplicar(int &resultado, int a, int b) {
    resultado = 0;
    for (int i = 0; i < b; i++) {
        resultado += a;
    }
}

void dividir(int &resultado, int a, int b) {
    resultado = 0;
    int temp = a;
    while (temp >= b) {
        temp -= b;
        resultado++;
    }
}

int main() {
    int a, b, resultado;

    a = 10;
    b = 5;
    sumar(resultado, a, b);
    std::cout << "sum: " << a << " + " << b << " = " << resultado << std::endl;

    restar(resultado, a, b);
    std::cout << "res: " << a << " - " << b << " = " << resultado << std::endl;

    multiplicar(resultado, a, b);
    std::cout << "multi: " << a << " * " << b << " = " << resultado << std::endl;

    dividir(resultado, a, b);
    std::cout << "div: " << a << " / " << b << " = " << resultado << std::endl;

    return 0;
}
