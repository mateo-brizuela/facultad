// gauss_solver.cpp (versión extendida)
#include "gauss_solver.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// ========== VERSIÓN ORIGINAL (TAMAÑO FIJO) ==========
int gauss_solve(double A[][N], double B[], double X[], double &determinant) {
    double ceroDef = 1e-10;
    double sum = 0.0;
    int intercambios = 0;
    
    // Copiamos para no modificar los originales
    double A_copy[N][N], B_copy[N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A_copy[i][j] = A[i][j];
        }
        B_copy[i] = B[i];
    }
    
    // Eliminación gaussiana con pivoteo
    for (int i = 0; i < N; i++) {
        // Pivoteo parcial
        if (fabs(A_copy[i][i]) < ceroDef) {
            int p = i;
            for (int l = i + 1; l < N; l++) {
                if (fabs(A_copy[l][i]) > fabs(A_copy[p][i])) {
                    p = l;
                }
            }
            
            if (p != i) {
                intercambios++;
                // Intercambiar filas
                for (int m = 0; m < N; m++) {
                    double aux = A_copy[p][m];
                    A_copy[p][m] = A_copy[i][m];
                    A_copy[i][m] = aux;
                }
                double aux = B_copy[p];
                B_copy[p] = B_copy[i];
                B_copy[i] = aux;
            }
        }
        
        // Verificar si la matriz es singular después del pivoteo
        if (fabs(A_copy[i][i]) < ceroDef) {
            determinant = 0.0;
            return 1;  // Matriz singular
        }
        
        // Eliminación hacia adelante
        for (int j = i + 1; j < N; j++) {
            double factor = -A_copy[j][i] / A_copy[i][i];
            for (int k = i; k < N; k++) {
                A_copy[j][k] += A_copy[i][k] * factor;
            }
            B_copy[j] += B_copy[i] * factor;
        }
    }
    
    // MOSTRAR MATRIZ REDUCIDA
    printf("\n=== MATRIZ REDUCIDA ===\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%8.4f\t", A_copy[i][j]);
        }
        printf("| %8.4f\n", B_copy[i]);
    }
    
    // CALCULAR DETERMINANTE
    double det = 1.0;
    for (int i = 0; i < N; i++) {
        det *= A_copy[i][i];
    }
    if (intercambios % 2 == 1) {
        det = -det;
    }
    determinant = det;
    
    printf("Determinante: %.6f\n", det);
    printf("Intercambios realizados: %d\n", intercambios);
    
    // Retrosustitución
    X[N-1] = B_copy[N-1] / A_copy[N-1][N-1];
    for (int i = N-2; i >= 0; i--) {
        sum = B_copy[i];
        for (int j = i + 1; j < N; j++) {
            sum -= A_copy[i][j] * X[j];
        }
        X[i] = sum / A_copy[i][i];
    }
    
    return 0;  // Éxito
}

double compute_residual(double A[][N], double X[], double B[]) {
    double max_residual = 0.0;
    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        for (int j = 0; j < N; j++) {
            sum += A[i][j] * X[j];
        }
        double residual = fabs(sum - B[i]);
        if (residual > max_residual) {
            max_residual = residual;
        }
    }
    return max_residual;
}

// ========== VERSIÓN DINÁMICA (PARA SPLINES) ==========
int gauss_solve_dynamic(int n, double** A, double* B, double* X, double& determinant) {
    double ceroDef = 1e-10;
    double sum = 0.0;
    int intercambios = 0;
    
    // Crear copias dinámicas
    double** A_copy = new double*[n];
    double* B_copy = new double[n];
    
    for (int i = 0; i < n; i++) {
        A_copy[i] = new double[n];
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
        B_copy[i] = B[i];
    }
    
    // EL MISMO ALGORITMO QUE LA VERSIÓN ORIGINAL
    // Eliminación gaussiana con pivoteo
    for (int i = 0; i < n; i++) {
        // Pivoteo parcial
        if (fabs(A_copy[i][i]) < ceroDef) {
            int p = i;
            for (int l = i + 1; l < n; l++) {
                if (fabs(A_copy[l][i]) > fabs(A_copy[p][i])) {
                    p = l;
                }
            }
            
            if (p != i) {
                intercambios++;
                // Intercambiar filas
                for (int m = 0; m < n; m++) {
                    double aux = A_copy[p][m];
                    A_copy[p][m] = A_copy[i][m];
                    A_copy[i][m] = aux;
                }
                double aux = B_copy[p];
                B_copy[p] = B_copy[i];
                B_copy[i] = aux;
            }
        }
        
        // Verificar si la matriz es singular después del pivoteo
        if (fabs(A_copy[i][i]) < ceroDef) {
            determinant = 0.0;
            // Liberar memoria antes de retornar
            for (int i = 0; i < n; i++) {
                delete[] A_copy[i];
            }
            delete[] A_copy;
            delete[] B_copy;
            return 1;  // Matriz singular
        }
        
        // Eliminación hacia adelante
        for (int j = i + 1; j < n; j++) {
            double factor = -A_copy[j][i] / A_copy[i][i];
            for (int k = i; k < n; k++) {
                A_copy[j][k] += A_copy[i][k] * factor;
            }
            B_copy[j] += B_copy[i] * factor;
        }
    }
    
    // MOSTRAR MATRIZ REDUCIDA
    printf("\n=== MATRIZ REDUCIDA (n=%d) ===\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.4f\t", A_copy[i][j]);
        }
        printf("| %8.4f\n", B_copy[i]);
    }
    
    // CALCULAR DETERMINANTE
    double det = 1.0;
    for (int i = 0; i < n; i++) {
        det *= A_copy[i][i];
    }
    if (intercambios % 2 == 1) {
        det = -det;
    }
    determinant = det;
    
    printf("Determinante: %.6f\n", det);
    printf("Intercambios realizados: %d\n", intercambios);
    
    // Retrosustitución
    X[n-1] = B_copy[n-1] / A_copy[n-1][n-1];
    for (int i = n-2; i >= 0; i--) {
        sum = B_copy[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A_copy[i][j] * X[j];
        }
        X[i] = sum / A_copy[i][i];
    }
    
    // Liberar memoria
    for (int i = 0; i < n; i++) {
        delete[] A_copy[i];
    }
    delete[] A_copy;
    delete[] B_copy;
    
    return 0;  // Éxito
}

double compute_residual_dynamic(int n, double** A, double* X, double* B) {
    double max_residual = 0.0;
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * X[j];
        }
        double residual = fabs(sum - B[i]);
        if (residual > max_residual) {
            max_residual = residual;
        }
    }
    return max_residual;
}

// ========== FUNCIONES AUXILIARES PARA ENTRADA DE DATOS ==========

void cargarVectorTeclado(double vector[], int tamaño) {
    printf("\n=== CARGA DE VECTOR ===\n");
    printf("Ingrese los %d elementos del vector:\n", tamaño);
    
    for (int i = 0; i < tamaño; i++) {
        printf("Elemento [%d] = ", i);
        scanf("%lf", &vector[i]);
    }
    printf("Vector cargado exitosamente.\n\n");
}

void leerVectorPantalla(double vector[], int tamaño) {
    printf("\n=== VECTOR (%d elementos) ===\n", tamaño);
    for (int i = 0; i < tamaño; i++) {
        printf("[%d] = %10.6f\n", i, vector[i]);
    }
    printf("\n");
}

void cargarMatrizTeclado(double matriz[][N], int filas, int columnas) {
    printf("\n=== CARGA DE MATRIZ ===\n");
    printf("Ingrese los elementos de la matriz (%d x %d):\n", filas, columnas);
    
    for (int i = 0; i < filas; i++) {
        printf("Fila %d: ", i);
        for (int j = 0; j < columnas; j++) {
            scanf("%lf", &matriz[i][j]);
        }
    }
    printf("Matriz cargada exitosamente.\n\n");
}

void leerMatrizPantalla(double matriz[][N], int filas, int columnas) {
    printf("\n=== MATRIZ (%d x %d) ===\n", filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%10.4f ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void leerVectoresTabla(double x[], double y[], int tamaño) {
    printf("\n=== TABLA DE DATOS ===\n");
    printf("Índice\t|\tX\t|\tY\n");
    printf("--------+---------------+---------------+----------\n");
    
    for (int i = 0; i < tamaño; i++) {
        printf("  %d\t|\t%8.4f\t|\t%8.4f\n", i, x[i], y[i]);
    }
    printf("\n");
}