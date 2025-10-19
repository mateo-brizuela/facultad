#include "splineCubica.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

// ===============================
// FUNCIONES AUXILIARES INTERNAS
// ===============================

// Arma el sistema lineal para los coeficientes del spline cúbico
// x[], y[]: datos originales (d puntos)
// matriz: matriz del sistema (tamaño n*n, almacenada como vector)
// vector: vector de términos independientes (tamaño n)
static void armarMatriz(
    double x[], double y[], int d, 
    double* matriz, double* vector
);

// Resuelve el sistema lineal Ax = B por eliminación gaussiana con pivoteo
// A: matriz (n*n, almacenada como vector)
// B: vector de términos independientes (n)
// x: solución (n)
// n: dimensión del sistema
static void gauss(
    double* A, double* B, double* x, int n
);

// =======================================
// FUNCIÓN PRINCIPAL DE LA LIBRERÍA
// =======================================

// Interpola valores usando spline cúbica natural
// x[], y[]: tabla original de tamaño d
// d: cantidad de datos originales
// x_interp[]: puntos donde se desea interpolar (tamaño n_interp)
// y_interp[]: resultados de la interpolación (tamaño n_interp)
// n_interp: cantidad de puntos a interpolar
void splineCubicaAproximar(
    double x[], double y[], int d,
    double x_interp[], double y_interp[], int n_interp
) {
    int m = d - 1;         // cantidad de intervalos
    int n = 4 * m;         // cantidad de incógnitas (4 por intervalo)
    double matriz[n * n], vector[n], coef[n];

    // 1. Armar el sistema lineal para los coeficientes del spline
    armarMatriz(x, y, d, matriz, vector);

    // 2. Resolver el sistema lineal para obtener los coeficientes
    gauss(matriz, vector, coef, n);

    // 3. Evaluar el spline en cada punto de x_interp[]
    for (int j = 0; j < n_interp; ++j) {
        double xr = x_interp[j];
        int intervalo = -1;
        // Buscar en qué intervalo cae xr
        for (int k = 0; k < m; ++k) {
            if (xr >= x[k] && xr <= x[k+1]) {
                intervalo = k;
                break;
            }
        }
        // Si está fuera del rango, usar el último intervalo
        if (intervalo == -1) intervalo = m-1;
        int base = 4 * intervalo;
        double a = coef[base];
        double b = coef[base+1];
        double c = coef[base+2];
        double d0 = coef[base+3];
        // Evaluar el polinomio cúbico correspondiente
        y_interp[j] = a*xr*xr*xr + b*xr*xr + c*xr + d0;
    }
}

// =======================================
// IMPLEMENTACIÓN DE FUNCIONES AUXILIARES
// =======================================

// Arma la matriz y el vector del sistema lineal para el spline cúbico natural
static void armarMatriz(
    double x[], double y[], int d, 
    double* matriz, double* vector
) {
    int m = d - 1;         // cantidad de intervalos
    int n = 4 * m;         // cantidad de incógnitas

    // Inicializar matriz y vector a cero
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) matriz[r * n + c] = 0.0;
        vector[r] = 0.0;
    }

    int row = 0;
    // 1) Condiciones de interpolación: S_k(x_k) = y_k y S_k(x_{k+1}) = y_{k+1}
    for (int k = 0; k < m; ++k) {
        int c = 4 * k;
        double xk = x[k], xk1 = x[k+1];

        // S_k(x_k) = y_k
        matriz[row * n + c]   = xk*xk*xk;
        matriz[row * n + c+1] = xk*xk;
        matriz[row * n + c+2] = xk;
        matriz[row * n + c+3] = 1.0;
        vector[row] = y[k];
        row++;

        // S_k(x_{k+1}) = y_{k+1}
        matriz[row * n + c]   = xk1*xk1*xk1;
        matriz[row * n + c+1] = xk1*xk1;
        matriz[row * n + c+2] = xk1;
        matriz[row * n + c+3] = 1.0;
        vector[row] = y[k+1];
        row++;
    }

    // 2) Continuidad de primeras derivadas en nodos interiores
    // S'_k(x_{k+1}) = S'_{k+1}(x_{k+1}) para k = 0..m-2
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);

        // Derivada del tramo izquierdo
        matriz[row * n + cL]   = 3 * xi * xi;
        matriz[row * n + cL+1] = 2 * xi;
        matriz[row * n + cL+2] = 1.0;

        // Derivada del tramo derecho (con signo negativo)
        matriz[row * n + cR]   = -3 * xi * xi;
        matriz[row * n + cR+1] = -2 * xi;
        matriz[row * n + cR+2] = -1.0;

        vector[row] = 0.0;
        row++;
    }

    // 3) Continuidad de segundas derivadas en nodos interiores
    // S''_k(x_{k+1}) = S''_{k+1}(x_{k+1}) para k = 0..m-2
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);

        // Segunda derivada del tramo izquierdo
        matriz[row * n + cL]   = 6 * xi;
        matriz[row * n + cL+1] = 2.0;

        // Segunda derivada del tramo derecho (con signo negativo)
        matriz[row * n + cR]   = -6 * xi;
        matriz[row * n + cR+1] = -2.0;

        vector[row] = 0.0;
        row++;
    }

    // 4) Condiciones de frontera naturales (segunda derivada nula en los extremos)
    // S''_0(x_0) = 0
    matriz[row * n + 0] = 6 * x[0];
    matriz[row * n + 1] = 2.0;
    vector[row] = 0.0;
    row++;

    // S''_{m-1}(x_m) = 0
    int lastBlock = 4*(m-1);
    matriz[row * n + lastBlock]   = 6 * x[m];
    matriz[row * n + lastBlock+1] = 2.0;
    vector[row] = 0.0;
}

// Resuelve el sistema lineal Ax = B por eliminación gaussiana con pivoteo parcial
static void gauss(
    double* A, double* B, double* x, int n
) {
    double prod = 1.0;
    double ceroDef = 1e-2; // tolerancia para considerar un pivote como cero
    double sum = 0.0;

    // Eliminación hacia adelante
    for (int i = 0; i < n; i++) {
        // Pivoteo parcial: buscar el mayor elemento en la columna i
        if (fabs(A[i*n + i]) < ceroDef) {
            int p = i;
            for (int l = i + 1; l < n; l++) {
                if (fabs(A[l*n + i]) > fabs(A[p*n + i])) {
                    p = l;
                }
            }
            // Intercambiar filas i y p en A y B
            for (int u = 0; u < n; u++) {
                double aux = A[p*n + u];
                A[p*n + u] = A[i*n + u];
                A[i*n + u] = aux;
            }
            double aux = B[p];
            B[p] = B[i];
            B[i] = aux;
        }
        // Eliminar debajo del pivote
        for (int j = i + 1; j < n; j++) {
            double factor = -A[j*n + i] / A[i*n + i];
            for (int k = i; k < n; k++) {
                A[j*n + k] += A[i*n + k] * factor;
            }
            B[j] += B[i] * factor;
        }
    }
    // Verificar que la matriz no sea singular
    for (int i = 0; i < n; i++) prod *= A[i*n + i];
    if (fabs(prod) < ceroDef) {
        printf("Error: la matriz tiene determinante cero\n");
        exit(1);
    }
    // Sustitución hacia atrás
    x[n-1] = B[n-1] / A[(n-1)*n + (n-1)];
    for (int i = n-2; i >= 0; i--) {
        sum = B[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i*n + j] * x[j];
        }
        x[i] = sum / A[i*n + i];
    }
}