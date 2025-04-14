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

void add_matrices(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract_matrices(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen_multiply(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n <= 64) { 
        multiply_matrices_traditional(n, A, B, C);
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
    
    int (*P1)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*P2)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*P3)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*P4)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*P5)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*P6)[new_n] = malloc(sizeof(int[new_n][new_n]));
    int (*P7)[new_n] = malloc(sizeof(int[new_n][new_n]));
    
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
    
    
    subtract_matrices(new_n, B12, B22, temp1);
    strassen_multiply(new_n, A11, temp1, P1);
    
   
    add_matrices(new_n, A11, A12, temp1);
    strassen_multiply(new_n, temp1, B22, P2);
    
   
    add_matrices(new_n, A21, A22, temp1);
    strassen_multiply(new_n, temp1, B11, P3);
    
 
    subtract_matrices(new_n, B21, B11, temp1);
    strassen_multiply(new_n, A22, temp1, P4);
    
   
    add_matrices(new_n, A11, A22, temp1);
    add_matrices(new_n, B11, B22, temp2);
    strassen_multiply(new_n, temp1, temp2, P5);
    
    
    subtract_matrices(new_n, A12, A22, temp1);
    add_matrices(new_n, B21, B22, temp2);
    strassen_multiply(new_n, temp1, temp2, P6);
    
    
    subtract_matrices(new_n, A11, A21, temp1);
    add_matrices(new_n, B11, B12, temp2);
    strassen_multiply(new_n, temp1, temp2, P7);
    
    
    add_matrices(new_n, P5, P4, temp1);
    subtract_matrices(new_n, temp1, P2, temp2);
    add_matrices(new_n, temp2, P6, C11);
    
  
    add_matrices(new_n, P1, P2, C12);
    
   
    add_matrices(new_n, P3, P4, C21);
    
   
    add_matrices(new_n, P5, P1, temp1);
    subtract_matrices(new_n, temp1, P3, temp2);
    subtract_matrices(new_n, temp2, P7, C22);
    
    
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
    free(P1); free(P2); free(P3); free(P4); free(P5); free(P6); free(P7);
    free(temp1); free(temp2);
}

int main() {
    int n = 2; 
    
    for (; n <= 2048; n *= 2) {
        
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
        strassen_multiply(n, A, B, C);
        clock_t end = clock();
        
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Strassen n=%d: %.4f seconds\n", n, time_spent);
        
        free(A);
        free(B);
        free(C);
    }
    
    return 0;
}


