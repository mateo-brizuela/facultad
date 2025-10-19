#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 6

/*
    Resolución de sistemas lineales por eliminación gaussiana con pivoteo
*/

void cargar(double A[n][n], double B[n]);
void leer(double A[n][n], double B[n]);
void gauss(double A[n][n], double B[n], double x[n]);

int main(int argc, char const *argv[])
{
    double A[n][n], B[n], x[n];
    cargar(A, B);
    leer(A, B);
    gauss(A, B, x);
    return 0;
}

// Carga la matriz A y el vector B desde la entrada estándar
void cargar(double A[n][n], double B[n]) {
    printf("=== CARGA DE DATOS ===\n");
    printf("Vamos a ingresar los elementos de la matriz A:\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d] = ", i+1, j+1);
            scanf("%lf", &A[i][j]);
        }
    }
    
    printf("\nVamos a ingresar los elementos del vector B:\n");
    for (int i = 0; i < n; i++) {
        printf("B[%d] = ", i+1);
        scanf("%lf", &B[i]);
    }
    printf("\n");
}

// Muestra la matriz aumentada [A|B]
void leer(double A[n][n], double B[n]) {
    printf("Matriz aumentada [A|B]:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", A[i][j]);
        }
        printf("| %.2f\n", B[i]);
    }
    printf("\n");
}

// Resuelve el sistema Ax = B por eliminación gaussiana
void gauss(double A[n][n], double B[n], double x[n]) {
    double ceroDef = pow(10, -2);
    double sum = 0.0;
    int intercambios = 0;
    
    // Eliminación gaussiana con pivoteo
    for (int i = 0; i < n; i++) {
        // Pivoteo parcial
        if (fabs(A[i][i]) < ceroDef) {
            int p = i;
            for (int l = i + 1; l < n; l++) {
                if (fabs(A[l][i]) > fabs(A[p][i])) {
                    p = l;
                }
            }
            
            if (p != i) {
                intercambios++;
                double aux;
                for (int m = 0; m < n; m++) {
                    aux = A[p][m];
                    A[p][m] = A[i][m];
                    A[i][m] = aux;
                }
                aux = B[p];
                B[p] = B[i];
                B[i] = aux;
            }
        }
        
        // Eliminación hacia adelante
        for (int j = i + 1; j < n; j++) {
            double factor = -A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] += A[i][k] * factor;
            }
            B[j] += B[i] * factor;
        }
    }
    
    printf("Matriz reducida:\n");
    leer(A, B);
    
    // Calcular determinante
    double prod = 1.0;
    for (int i = 0; i < n; i++) {
        prod *= A[i][i];
    }
    
    double detA = prod;
    if (intercambios % 2 == 1) {
        detA = -prod;
    }
    
    // Verificar si la matriz es singular
    if (fabs(prod) < ceroDef) {
        printf("Error: la matriz es singular\n");
        exit(1);
    }
    
    // Retrosustitución
    x[n-1] = B[n-1] / A[n-1][n-1];
    for (int i = n-2; i >= 0; i--) {
        sum = B[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
    
    // Resultados en notación decimal
    printf("=== RESULTADOS - NOTACIÓN DECIMAL ===\n");
    printf("Solución del sistema:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.10f\n", i+1, x[i]);
    }
    printf("Determinante de A (detA) = %.10f\n", detA);
    printf("Intercambios realizados: %d\n", intercambios);
    
    // Resultados en notación científica
    printf("\n=== RESULTADOS - NOTACIÓN CIENTÍFICA ===\n");
    printf("Solución del sistema:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.10e\n", i+1, x[i]);
    }
    printf("Determinante de A (detA) = %.10e\n", detA);
    printf("Intercambios realizados: %d\n", intercambios);
}