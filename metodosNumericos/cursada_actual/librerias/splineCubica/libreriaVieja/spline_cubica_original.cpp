#include "spline_cubica.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

// Función de debug para ver el sistema
void debug_sistema(double matriz[][MAX_ECUACIONES], double vector[], int n, const char* nombre) {
    printf("\n=== %s (%dx%d) ===\n", nombre, n, n);
    for (int i = 0; i < n; i++) {
        printf("Fila %2d: ", i);
        for (int j = 0; j < n; j++) {
            if (fabs(matriz[i][j]) > 1e-10) {
                printf("%8.2f ", matriz[i][j]);
            } else {
                printf("    .    ");
            }
        }
        printf(" | %8.2f\n", vector[i]);
    }
}

// Función interna corregida
void spline_armar_sistema(double x[], double y[], int d, double matriz[][MAX_ECUACIONES], double vector[]) {
    int n = 4 * (d - 1);  // Tamaño real del sistema
    int m = d - 1;        // Cantidad de segmentos
    
    printf("DEBUG: Construyendo sistema %dx%d para %d puntos, %d segmentos\n", n, n, d, m);
    
    // Inicializar matriz y vector a cero
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            matriz[r][c] = 0.0;
        }
        vector[r] = 0.0;
    }

    int row = 0;

    // 1) Condiciones de interpolación (2 ecuaciones por tramo)
    printf("DEBUG: Agregando condiciones de interpolación...\n");
    for (int k = 0; k < m; ++k) {
        int base = 4 * k;
        double xk = x[k], xk1 = x[k+1];

        // S_k(x_k) = y_k
        matriz[row][base]   = xk * xk * xk;     // a * xk³
        matriz[row][base+1] = xk * xk;          // b * xk²
        matriz[row][base+2] = xk;               // c * xk
        matriz[row][base+3] = 1.0;              // d
        vector[row] = y[k];
        printf("DEBUG: Fila %d - S%d(%.1f)=%.1f\n", row, k, xk, y[k]);
        row++;

        // S_k(x_{k+1}) = y_{k+1}
        matriz[row][base]   = xk1 * xk1 * xk1;  // a * xk1³
        matriz[row][base+1] = xk1 * xk1;        // b * xk1²
        matriz[row][base+2] = xk1;              // c * xk1
        matriz[row][base+3] = 1.0;              // d
        vector[row] = y[k+1];
        printf("DEBUG: Fila %d - S%d(%.1f)=%.1f\n", row, k, xk1, y[k+1]);
        row++;
    }

    // 2) Continuidad de primeras derivadas en nodos interiores
    printf("DEBUG: Agregando continuidad primeras derivadas...\n");
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int baseL = 4 * k;
        int baseR = 4 * (k+1);

        // S_k'(xi) = S_{k+1}'(xi)
        // Derivada: 3a*x² + 2b*x + c
        matriz[row][baseL]   = 3 * xi * xi;   // 3a_k
        matriz[row][baseL+1] = 2 * xi;        // 2b_k
        matriz[row][baseL+2] = 1.0;           // c_k
        
        matriz[row][baseR]   = -3 * xi * xi;  // -3a_{k+1}
        matriz[row][baseR+1] = -2 * xi;       // -2b_{k+1}
        matriz[row][baseR+2] = -1.0;          // -c_{k+1}

        vector[row] = 0.0;
        printf("DEBUG: Fila %d - S%d'(%.1f)=S%d'(%.1f)\n", row, k, xi, k+1, xi);
        row++;
    }

    // 3) Continuidad de segundas derivadas en nodos interiores
    printf("DEBUG: Agregando continuidad segundas derivadas...\n");
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int baseL = 4 * k;
        int baseR = 4 * (k+1);

        // S_k''(xi) = S_{k+1}''(xi)
        // Segunda derivada: 6a*x + 2b
        matriz[row][baseL]   = 6 * xi;    // 6a_k
        matriz[row][baseL+1] = 2.0;       // 2b_k
        
        matriz[row][baseR]   = -6 * xi;   // -6a_{k+1}
        matriz[row][baseR+1] = -2.0;      // -2b_{k+1}

        vector[row] = 0.0;
        printf("DEBUG: Fila %d - S%d''(%.1f)=S%d''(%.1f)\n", row, k, xi, k+1, xi);
        row++;
    }

    // 4) Condiciones de frontera naturales (segundas derivadas en extremos = 0)
    printf("DEBUG: Agregando condiciones de frontera...\n");
    
    // En x0: S_0''(x0) = 0
    matriz[row][0] = 6 * x[0];  // 6a_0
    matriz[row][1] = 2.0;       // 2b_0
    vector[row] = 0.0;
    printf("DEBUG: Fila %d - S0''(%.1f)=0\n", row, x[0]);
    row++;

    // En x_{m}: S_{m-1}''(x_m) = 0
    int lastBase = 4 * (m-1);
    matriz[row][lastBase]   = 6 * x[m];  // 6a_{m-1}
    matriz[row][lastBase+1] = 2.0;       // 2b_{m-1}
    vector[row] = 0.0;
    printf("DEBUG: Fila %d - S%d''(%.1f)=0\n", row, m-1, x[m]);
    row++;

    printf("DEBUG: Sistema completo. Total filas: %d (esperadas: %d)\n", row, n);
}

int spline_calcular_coeficientes(double x[], double y[], int d, double coeficientes[][4]) {
    if (d < 2 || d > MAX_PUNTOS) {
        printf("Error: cantidad de puntos debe estar entre 2 y %d\n", MAX_PUNTOS);
        return -1;
    }

    int n = 4 * (d - 1);
    printf("DEBUG: Resolviendo sistema de %d ecuaciones para %d puntos\n", n, d);
    
    double matriz[MAX_ECUACIONES][MAX_ECUACIONES];
    double vector[MAX_ECUACIONES];
    double incognitas[MAX_ECUACIONES];
    double det;

    // Construir el sistema lineal
    spline_armar_sistema(x, y, d, matriz, vector);
    
    // Mostrar sistema para debug
    debug_sistema(matriz, vector, n, "SISTEMA SPLINE ANTES DE RESOLVER");

    // Resolver con eliminación gaussiana
    printf("\nDEBUG: Llamando a gauss_solve...\n");
    int result = gauss_solve(matriz, vector, incognitas, det);

    if (result != 0) {
        printf("ERROR: No se pudo resolver el sistema. Determinante: %e\n", det);
        printf("Posibles causas:\n");
        printf("1. Matriz singular (determinante ≈ 0)\n");
        printf("2. Sistema mal condicionado\n");
        printf("3. Error en la construcción de la matriz\n");
        return -1;
    }

    printf("DEBUG: Sistema resuelto exitosamente. Determinante: %e\n", det);

    // Reorganizar coeficientes
    for (int k = 0; k < d-1; k++) {
        int base = 4 * k;
        coeficientes[k][0] = incognitas[base];     // a
        coeficientes[k][1] = incognitas[base + 1]; // b
        coeficientes[k][2] = incognitas[base + 2]; // c
        coeficientes[k][3] = incognitas[base + 3]; // d
        
        printf("DEBUG: Coeficientes S%d: a=%.6f, b=%.6f, c=%.6f, d=%.6f\n",
               k, coeficientes[k][0], coeficientes[k][1], 
               coeficientes[k][2], coeficientes[k][3]);
    }

    return 0;
}

int spline_evaluar_punto(double x[], int d, double coeficientes[][4], 
                        double x_punto, double* y_resultado) {
    // Determinar en qué intervalo está x_punto
    int intervalo = -1;
    for (int k = 0; k < d-1; k++) {
        if (x_punto >= x[k] && x_punto <= x[k+1]) {
            intervalo = k;
            break;
        }
    }

    if (intervalo == -1) {
        printf("DEBUG: x=%.2f fuera de rango [%.2f, %.2f]\n", x_punto, x[0], x[d-1]);
        return -1;
    }

    // Evaluar polinomio cúbico
    double a = coeficientes[intervalo][0];
    double b = coeficientes[intervalo][1];
    double c = coeficientes[intervalo][2];
    double d_coef = coeficientes[intervalo][3];
    
    *y_resultado = a*x_punto*x_punto*x_punto + b*x_punto*x_punto + c*x_punto + d_coef;
    
    printf("DEBUG: S%d(%.2f) = %.6f\n", intervalo, x_punto, *y_resultado);
    return intervalo;
}

int spline_evaluar_multiples_puntos(double x[], int d, double coeficientes[][4],
                                   double x_aproximar[], int num_aproximaciones,
                                   double y_resultados[], int segmentos_usados[]) {
    int exitosas = 0;
    
    for (int i = 0; i < num_aproximaciones; i++) {
        int segmento = spline_evaluar_punto(x, d, coeficientes, x_aproximar[i], &y_resultados[i]);
        if (segmentos_usados != NULL) {
            segmentos_usados[i] = segmento;
        }
        if (segmento >= 0) {
            exitosas++;
        }
    }
    
    return exitosas;
}

void spline_imprimir_ecuaciones(double x[], int d, double coeficientes[][4]) {
    printf("\n=== ECUACIONES DE LOS SPLINES ===\n");
    
    for (int k = 0; k < d-1; k++) {
        printf("\nS%d(x) = ", k);
        printf("(%.6f)x³ + (%.6f)x² + (%.6f)x + (%.6f)", 
               coeficientes[k][0], coeficientes[k][1], 
               coeficientes[k][2], coeficientes[k][3]);
        printf("  para x en [%.2f, %.2f]\n", x[k], x[k+1]);
    }
    printf("\n");
}