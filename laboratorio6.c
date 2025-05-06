#include <stdio.h>
#include <stdbool.h>

// DOSAL RUIZ VICTOR MANUEL

bool esPrimo(int n) {
    if (n < 2) return false;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return false;
    return true;
}


int generarFibonacciFiltrado(int fib[], int K) {
    fib[0] = 0;
    fib[1] = 1;
    int i = 2, pos = 2;
    while (1) {
        int nuevo = fib[i - 1] + fib[i - 2];
        if (nuevo > K) break;
        if (!esPrimo(pos)) {
            fib[i] = nuevo;
            i++;
        }
        pos++;
    }
    return i;  
}


int obtenerMinimoTerminos(int fib[], int n, int K) {
    int usados = 0;
    int ultimoUsado = -2;  

    for (int i = n - 1; i >= 0; i--) {
        
        if (fib[i] <= K && i != ultimoUsado - 1 && i != ultimoUsado + 1) {
            K -= fib[i];
            usados++;
            ultimoUsado = i;
        }
        if (K == 0) break;
    }
    return usados;
}


int calcularK(int dia, int mes, int año) {
    return (dia * 100) + (mes * 10) + (año % 100);
}


int main() {
    int dia = 27, mes = 10, año = 1999;
    int K = calcularK(dia, mes, año);
    printf("K = %d\n", K);

    int fib[100];  
    int n = generarFibonacciFiltrado(fib, K);

    printf("Secuencia filtrada:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    int resultado = obtenerMinimoTerminos(fib, n, K);
    printf("Número mínimo de términos = %d\n", resultado);

    return 0;
}
