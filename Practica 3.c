#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_COMB 100
#define MAX_TAMA 5  


const char *map[] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};


void checa(char *digits, int index, char *actual, char **result, int *cont) {
    if (digits[index] == '\0') {
        result[*cont] = strdup(actual);
        (*cont)++;
        return;
    }


    int digit = digits[index] - '0';
    const char *letters = map[digit];


    for (int i = 0; letters[i] != '\0'; i++) {
        actual[index] = letters[i];
        checa(digits, index + 1, actual, result, cont);
    }
}


char **digCombi(char *digits, int *returnTam) {
    if (digits[0] == '\0') {
        *returnTam = 0;
        return NULL;
    }


    char **result = (char **)malloc(MAX_COMB * sizeof(char *));
    char actual[MAX_TAMA] = {0};  
    int cont = 0;


    checa(digits, 0, actual, result, &cont);


    *returnTam = cont;
    return result;
}


int main() {
    char digits[MAX_TAMA];
    printf("Ingrese los dígitos: ");
    scanf("%s", digits);


    int returnTam;
    char **combi = digCombi(digits, &returnTam);


    printf("Output: [");
    for (int i = 0; i < returnTam; i++) {
        printf("\"%s\"", combi[i]);
        if (i < returnTam - 1) {
            printf(", ");
        }
        free(combi[i]);  
    }
    printf("]\n");


    free(combi);
    return 0;
}

