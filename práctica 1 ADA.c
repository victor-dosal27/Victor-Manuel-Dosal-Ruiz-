/******************************************************************************

                            Online C Debugger.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Debug" button to debug program.

*******************************************************************************/

#include <stdio.h>

int palindromo(int num){
    
    int numoriginal = num;
    int reverso = 0,digito;
    
    while (num > 0){
        digito = num % 10;
        reverso = reverso * 10 + digito;
        num /= 10;
    }
    
    return numoriginal == reverso;
}

int main()
{
    int numero;
    printf("INSERTA UN NUMERO > ");
    scanf("%d",&numero);
    
    if(palindromo(numero)){
        printf("TRUE\n");
    }
    else{
        printf("FALSE\n");
    }
    

    return 0;
}