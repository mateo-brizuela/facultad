// main.cpp
#include <stdio.h>
#include <stdlib.h>
#include "gauss_solver.h"

// Función para imprimir matrices
void print_matrix(int n, double** A, double* B) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4f ", A[i][j]);
        }
        printf("| %8.4f\n", B[i]);
    }
}

void print_matrix_fixed(double A[][N], double* B) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.4f ", A[i][j]);
        }
        printf("| %8.4f\n", B[i]);
    }
}

// Función para crear matriz dinámica
double** create_matrix(int n) {
    double** A = new double*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
        for (int j = 0; j < n; j++) {
            A[i][j] = 0.0;
        }
    }
    return A;
}

// Función para liberar matriz dinámica
void free_matrix(int n, double** A) {
    for (int i = 0; i < n; i++) {
        delete[] A[i];
    }
    delete[] A;
}

int main() {
    printf("=========================================\n");
    printf("   DEMOSTRACION LIBRERIA GAUSS SOLVER\n");
    printf("=========================================\n");
    
    // ========== EJEMPLO 1: VERSIÓN FIJA (N=4) ==========
    printf("\n*** EJEMPLO 1: SISTEMA 4x4 (VERSION FIJA) ***\n");
    
    double A_fixed[N][N] = {
        {4.0, 1.0, 1.0, 0.0},
        {2.0, 5.0, 2.0, 1.0},
        {1.0, 2.0, 4.0, 1.0},
        {0.0, 1.0, 1.0, 3.0}
    };
    
    double B_fixed[N] = {7.0, 15.0, 11.0, 8.0};
    double X_fixed[N];
    double det_fixed;
    
    printf("\n=== SISTEMA ORIGINAL ===\n");
    print_matrix_fixed(A_fixed, B_fixed);
    
    int result1 = gauss_solve(A_fixed, B_fixed, X_fixed, det_fixed);
    
    if (result1 == 0) {
        printf("\n=== SOLUCION ===\n");
        for (int i = 0; i < N; i++) {
            printf("x%d = %10.6f\n", i+1, X_fixed[i]);
        }
        
        printf("\n=== INFORMACION ADICIONAL ===\n");
        printf("Determinante: %f\n", det_fixed);
        
        double residual1 = compute_residual(A_fixed, X_fixed, B_fixed);
        printf("Error residual máximo: %e\n", residual1);
    } else {
        printf("Error: matriz singular\n");
    }
    
    // ========== EJEMPLO 2: VERSIÓN DINÁMICA ==========
    printf("\n\n*** EJEMPLO 2: SISTEMA 3x3 (VERSION DINAMICA) ***\n");
    
    int n1 = 3;
    double** A_dyn1 = create_matrix(n1);
    double* B_dyn1 = new double[n1];
    double* X_dyn1 = new double[n1];
    double det_dyn1;
    
    // Sistema 3x3
    A_dyn1[0][0] = 2.0; A_dyn1[0][1] = 1.0; A_dyn1[0][2] = -1.0;
    A_dyn1[1][0] = -3.0; A_dyn1[1][1] = -1.0; A_dyn1[1][2] = 2.0;
    A_dyn1[2][0] = -2.0; A_dyn1[2][1] = 1.0; A_dyn1[2][2] = 2.0;
    
    B_dyn1[0] = 8.0;
    B_dyn1[1] = -11.0;
    B_dyn1[2] = -3.0;
    
    printf("\n=== SISTEMA ORIGINAL ===\n");
    print_matrix(n1, A_dyn1, B_dyn1);
    
    int result2 = gauss_solve_dynamic(n1, A_dyn1, B_dyn1, X_dyn1, det_dyn1);
    
    if (result2 == 0) {
        printf("\n=== SOLUCION ===\n");
        for (int i = 0; i < n1; i++) {
            printf("x%d = %10.6f\n", i+1, X_dyn1[i]);
        }
        
        printf("\n=== INFORMACION ADICIONAL ===\n");
        printf("Determinante: %f\n", det_dyn1);
        
        double residual2 = compute_residual_dynamic(n1, A_dyn1, X_dyn1, B_dyn1);
        printf("Error residual máximo: %e\n", residual2);
    } else {
        printf("Error: matriz singular\n");
    }
    
    // Liberar memoria del primer sistema dinámico
    free_matrix(n1, A_dyn1);
    delete[] B_dyn1;
    delete[] X_dyn1;
    
    // ========== EJEMPLO 3: MATRIZ SINGULAR ==========
    printf("\n\n*** EJEMPLO 3: MATRIZ SINGULAR (VERSION DINAMICA) ***\n");
    
    int n2 = 2;
    double** A_dyn2 = create_matrix(n2);
    double* B_dyn2 = new double[n2];
    double* X_dyn2 = new double[n2];
    double det_dyn2;
    
    // Matriz singular 2x2
    A_dyn2[0][0] = 1.0; A_dyn2[0][1] = 2.0;
    A_dyn2[1][0] = 2.0; A_dyn2[1][1] = 4.0;  // Segunda fila es múltiplo de la primera
    
    B_dyn2[0] = 3.0;
    B_dyn2[1] = 6.0;
    
    printf("\n=== SISTEMA ORIGINAL ===\n");
    print_matrix(n2, A_dyn2, B_dyn2);
    
    int result3 = gauss_solve_dynamic(n2, A_dyn2, B_dyn2, X_dyn2, det_dyn2);
    
    if (result3 == 0) {
        printf("\n=== SOLUCION ===\n");
        for (int i = 0; i < n2; i++) {
            printf("x%d = %10.6f\n", i+1, X_dyn2[i]);
        }
        printf("Determinante: %f\n", det_dyn2);
    } else {
        printf("Resultado: %d (Matriz singular - esperado)\n", result3);
        printf("Determinante: %f\n", det_dyn2);
    }
    
    // Liberar memoria del segundo sistema dinámico
    free_matrix(n2, A_dyn2);
    delete[] B_dyn2;
    delete[] X_dyn2;
    
    // ========== EJEMPLO 4: SISTEMA 5x5 ==========
    printf("\n\n*** EJEMPLO 4: SISTEMA 5x5 (VERSION DINAMICA) ***\n");
    
    int n3 = 5;
    double** A_dyn3 = create_matrix(n3);
    double* B_dyn3 = new double[n3];
    double* X_dyn3 = new double[n3];
    double det_dyn3;
    
    // Sistema 5x5 diagonal dominante
    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n3; j++) {
            if (i == j) {
                A_dyn3[i][j] = 10.0 + i;  // Elementos grandes en la diagonal
            } else {
                A_dyn3[i][j] = 1.0;       // Elementos pequeños fuera de la diagonal
            }
        }
        B_dyn3[i] = (i + 1) * 5.0;  // Vector B simple
    }
    
    printf("\n=== SISTEMA ORIGINAL (primeras 3 filas) ===\n");
    for (int i = 0; i < 3 && i < n3; i++) {
        for (int j = 0; j < n3; j++) {
            printf("%8.4f ", A_dyn3[i][j]);
        }
        printf("| %8.4f\n", B_dyn3[i]);
    }
    printf("...\n");
    
    int result4 = gauss_solve_dynamic(n3, A_dyn3, B_dyn3, X_dyn3, det_dyn3);
    
    if (result4 == 0) {
        printf("\n=== SOLUCION ===\n");
        for (int i = 0; i < n3; i++) {
            printf("x%d = %10.6f\n", i+1, X_dyn3[i]);
        }
        
        printf("\n=== INFORMACION ADICIONAL ===\n");
        printf("Determinante: %f\n", det_dyn3);
        
        double residual4 = compute_residual_dynamic(n3, A_dyn3, X_dyn3, B_dyn3);
        printf("Error residual máximo: %e\n", residual4);
    } else {
        printf("Error: matriz singular\n");
    }
    
    // Liberar memoria del tercer sistema dinámico
    free_matrix(n3, A_dyn3);
    delete[] B_dyn3;
    delete[] X_dyn3;

    // ========== TESTING DE LAS NUEVAS FUNCIONES ==========
    printf("\n\n=========================================\n");
    printf("   TESTING NUEVAS FUNCIONES AUXILIARES\n");
    printf("=========================================\n");
    
    // Test 1: Cargar y mostrar un vector pequeño
    printf("\n*** TEST 1: VECTOR PEQUEÑO ***\n");
    double test_vector[3];
    cargarVectorTeclado(test_vector, 3);
    printf("Vector cargado:\n");
    leerVectorPantalla(test_vector, 3);
    
    // Test 2: Cargar y mostrar una matriz pequeña
    printf("\n*** TEST 2: MATRIZ PEQUEÑA ***\n");
    double test_matriz[2][N];
    cargarMatrizTeclado(test_matriz, 2, 2);
    printf("Matriz cargada:\n");
    leerMatrizPantalla(test_matriz, 2, 2);
    
    // Test 3: Resolver un sistema usando las nuevas funciones
    printf("\n*** TEST 3: SISTEMA COMPLETO ***\n");
    int test_n = 2;
    double test_A[2][N];
    double test_B[2];
    double test_X[2];
    double test_det;
    
    printf("Cargando sistema %dx%d:\n", test_n, test_n);
    cargarMatrizTeclado(test_A, test_n, test_n);
    cargarVectorTeclado(test_B, test_n);
    
    printf("\n=== SISTEMA CARGADO ===\n");
    leerMatrizPantalla(test_A, test_n, test_n);
    leerVectorPantalla(test_B, test_n);
    
    int test_result = gauss_solve(test_A, test_B, test_X, test_det);
    
    if (test_result == 0) {
        printf("=== SOLUCION DEL SISTEMA ===\n");
        leerVectorPantalla(test_X, test_n);
        printf("Determinante: %f\n", test_det);
        
        double test_residual = compute_residual(test_A, test_X, test_B);
        printf("Error residual máximo: %e\n", test_residual);
    } else {
        printf("El sistema no pudo resolverse (matriz singular)\n");
    }
    

    // En cualquier programa
    double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double y[5] = {2.5, 4.8, 6.1, 8.9, 10.2};
    
    leerVectoresTabla(x, y, 5);


    printf("\n=========================================\n");
    printf("   DEMOSTRACION COMPLETADA\n");
    printf("=========================================\n");
    
    return 0;
}