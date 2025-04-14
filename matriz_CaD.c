#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add_matrices(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiply_matrices_dac(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    
    int new_n = n / 2;
    

    int (*A11)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*A12)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*A21)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*A22)[new_n] = malloc(sizeof(int[new_n][new_n]));
    
    int (*B11)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*B12)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*B21)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*B22)[new_n] = malloc(sizeof(int[new_n][new_n]));
    
    int (*C11)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*C12)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*C21)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*C22)[new_n] = malloc(sizeof(int[new_n][new_n]));
    
    int (*temp1)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*temp2)[new_n] = malloc(sizeof(int[new_n][new_n]));
    
    
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_n];
            A21[i][j] = A[i + new_n][j];
            A22[i][j] = A[i + new_n][j + new_n];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_n];
            B21[i][j] = B[i + new_n][j];
            B22[i][j] = B[i + new_n][j + new_n];
        }
    }
    
   
    multiply_matrices_dac(new_n, A11, B11, temp1);
    multiply_matrices_dac(new_n, A12, B21, temp2);
    add_matrices(new_n, temp1, temp2, C11);
    
    multiply_matrices_dac(new_n, A11, B12, temp1);
    multiply_matrices_dac(new_n, A12, B22, temp2);
    add_matrices(new_n, temp1, temp2, C12);
    
    multiply_matrices_dac(new_n, A21, B11, temp1);
    multiply_matrices_dac(new_n, A22, B21, temp2);
    add_matrices(new_n, temp1, temp2, C21);
    
    multiply_matrices_dac(new_n, A21, B12, temp1);
    multiply_matrices_dac(new_n, A22, B22, temp2);
    add_matrices(new_n, temp1, temp2, C22);
    
    
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            C[i][j] = C11[i][j];
            C[i][j + new_n] = C12[i][j];
            C[i + new_n][j] = C21[i][j];
            C[i + new_n][j + new_n] = C22[i][j];
        }
    }
    
    
    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(C11); free(C12); free(C21); free(C22);
    free(temp1); free(temp2);
}

int main() {
    int n = 2; 
    
    for (; n <= 1024; n *= 2) {
       
        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        int (*C)[n] = malloc(sizeof(int[n][n]));
        
       
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 100;
                B[i][j] = rand() % 100;
            }
        }
        
        clock_t start = clock();
        multiply_matrices_dac(n, A, B, C);
        clock_t end = clock();
        
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Divide and Conquer n=%d: %.4f seconds\n", n, time_spent);
        
        free(A);
        free(B);
        free(C);
    }
    
    return 0;
}



