#include <stdio.h>

#define VALOR_MAX 2147483647
#define VALOR_MIN -2147483648

int division(int dividend, int divisor) {
    
    if (divisor == 0) {
        printf("NO PUEDES DIVIDIR ENTRE ");
        return 0;
    }

    
    if (dividend == VALOR_MIN && divisor == -1) {
        return VALOR_MAX;
    }

    
    int signo = (dividend < 0) ^ (divisor < 0) ? -1 : 1;

    
    unsigned int ldividend = dividend < 0 ? -dividend : dividend;
    unsigned int ldivisor = divisor < 0 ? -divisor : divisor;

    
    unsigned int suma = 0, resultado = 0;
    while (suma + ldivisor <= ldividend) {
        suma += ldivisor;
        resultado++;
    }

    return signo * resultado;
}

int main() {
    
    printf("RESULTADO: %d\n", division(10, 3));  
    printf("RESULTADO: %d\n", division(7, -3));  
    printf("%d\n", division(5, 0));   

    return 0;
}
