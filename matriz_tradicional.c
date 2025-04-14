#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiply_matrices_traditional(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n = 2; 
    
    for (; n <= 1024; n *= 2) {
       
        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        int (*C)[n] = malloc(sizeof(int[n][n]));
        
       
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }
        
        clock_t start = clock();
        multiply_matrices_traditional(n, A, B, C);
        clock_t end = clock();
        
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Traditional n=%d: %.4f seconds\n", n, time_spent);
        
        free(A);
        free(B);
        free(C);
    }
    
    return 0;
}

