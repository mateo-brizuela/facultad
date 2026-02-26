#include "spline_cubica.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

// Si MAX_PUNTOS_PROGRAMA no está definido, usar un valor por defecto
#ifndef MAX_PUNTOS_PROGRAMA
#define MAX_PUNTOS_PROGRAMA 20  // Valor por defecto para compilación individual
#endif

// Función para crear matriz dinámica
double** crear_matriz_dinamica(int filas, int columnas) {
    double** matriz = new double*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new double[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0.0;
        }
    }
    return matriz;
}

// Función para liberar matriz dinámica
void liberar_matriz_dinamica(int filas, double** matriz) {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Función interna: construye el sistema lineal para splines (versión dinámica)
void spline_armar_sistema_dinamico(double x[], double y[], int d, double** matriz, double* vector) {
    int n = 4 * (d - 1);  // Tamaño real del sistema
    int m = d - 1;        // Cantidad de segmentos
    
    printf("DEBUG: Construyendo sistema dinámico %dx%d para %d puntos\n", n, n, d);
    
    // Inicializar matriz y vector a cero
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            matriz[r][c] = 0.0;
        }
        vector[r] = 0.0;
    }

    int row = 0;

    // 1) Condiciones de interpolación (2 ecuaciones por tramo)
    for (int k = 0; k < m; ++k) {
        int base = 4 * k;
        double xk = x[k], xk1 = x[k+1];

        // S_k(x_k) = y_k
        matriz[row][base]   = xk * xk * xk;
        matriz[row][base+1] = xk * xk;
        matriz[row][base+2] = xk;
        matriz[row][base+3] = 1.0;
        vector[row] = y[k];
        row++;

        // S_k(x_{k+1}) = y_{k+1}
        matriz[row][base]   = xk1 * xk1 * xk1;
        matriz[row][base+1] = xk1 * xk1;
        matriz[row][base+2] = xk1;
        matriz[row][base+3] = 1.0;
        vector[row] = y[k+1];
        row++;
    }

    // 2) Continuidad de primeras derivadas en nodos interiores
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int baseL = 4 * k;
        int baseR = 4 * (k+1);

        // S_k'(xi) = S_{k+1}'(xi)
        matriz[row][baseL]   = 3 * xi * xi;
        matriz[row][baseL+1] = 2 * xi;
        matriz[row][baseL+2] = 1.0;
        
        matriz[row][baseR]   = -3 * xi * xi;
        matriz[row][baseR+1] = -2 * xi;
        matriz[row][baseR+2] = -1.0;

        vector[row] = 0.0;
        row++;
    }

    // 3) Continuidad de segundas derivadas en nodos interiores
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int baseL = 4 * k;
        int baseR = 4 * (k+1);

        // S_k''(xi) = S_{k+1}''(xi)
        matriz[row][baseL]   = 6 * xi;
        matriz[row][baseL+1] = 2.0;
        
        matriz[row][baseR]   = -6 * xi;
        matriz[row][baseR+1] = -2.0;

        vector[row] = 0.0;
        row++;
    }

    // 4) Condiciones de frontera naturales (segundas derivadas en extremos = 0)
    // En x0: S_0''(x0) = 0
    matriz[row][0] = 6 * x[0];
    matriz[row][1] = 2.0;
    vector[row] = 0.0;
    row++;

    // En x_{m}: S_{m-1}''(x_m) = 0
    int lastBase = 4 * (m-1);
    matriz[row][lastBase]   = 6 * x[m];
    matriz[row][lastBase+1] = 2.0;
    vector[row] = 0.0;

    printf("DEBUG: Sistema dinámico construido. %d ecuaciones\n", row);
}

int spline_calcular_coeficientes(double x[], double y[], int d, double coeficientes[][4]) {
    if (d < 2 || d > MAX_PUNTOS) {
        printf("Error: cantidad de puntos debe estar entre 2 y %d\n", MAX_PUNTOS);
        return -1;
    }

    int n = 4 * (d - 1);
    printf("=== RESOLVIENDO SPLINES CON VERSIÓN DINÁMICA ===\n");
    printf("Sistema: %dx%d, Puntos: %d, Segmentos: %d\n", n, n, d, d-1);

    // Crear arrays dinámicos
    double** matriz = crear_matriz_dinamica(n, n);
    double* vector = new double[n];
    double* incognitas = new double[n];
    double det;

    // Construir el sistema lineal
    spline_armar_sistema_dinamico(x, y, d, matriz, vector);

    // Resolver con eliminación gaussiana DINÁMICA
    printf("Llamando a gauss_solve_dynamic...\n");
    int result = gauss_solve_dynamic(n, matriz, vector, incognitas, det);

    if (result != 0) {
        printf("ERROR: No se pudo resolver el sistema lineal\n");
        printf("Determinante calculado: %e\n", det);
        
        // Liberar memoria
        liberar_matriz_dinamica(n, matriz);
        delete[] vector;
        delete[] incognitas;
        return -1;
    }

    printf("✅ Sistema resuelto exitosamente!\n");
    printf("Determinante: %e\n", det);

    // Reorganizar coeficientes en la matriz estática de salida
    for (int k = 0; k < d-1; k++) {
        int base = 4 * k;
        coeficientes[k][0] = incognitas[base];     // a
        coeficientes[k][1] = incognitas[base + 1]; // b
        coeficientes[k][2] = incognitas[base + 2]; // c
        coeficientes[k][3] = incognitas[base + 3]; // d
    }

    // Liberar memoria
    liberar_matriz_dinamica(n, matriz);
    delete[] vector;
    delete[] incognitas;

    return 0;
}

// Las funciones de evaluación se mantienen igual
int spline_evaluar_punto(double x[], int d, double coeficientes[][4], 
                        double x_punto, double* y_resultado) {
    int intervalo = -1;
    for (int k = 0; k < d-1; k++) {
        if (x_punto >= x[k] && x_punto <= x[k+1]) {
            intervalo = k;
            break;
        }
    }

    if (intervalo == -1) {
        return -1;
    }

    double a = coeficientes[intervalo][0];
    double b = coeficientes[intervalo][1];
    double c = coeficientes[intervalo][2];
    double d_coef = coeficientes[intervalo][3];
    
    *y_resultado = a*x_punto*x_punto*x_punto + b*x_punto*x_punto + c*x_punto + d_coef;
    
    return intervalo;
}

int spline_evaluar_multiples_puntos(double x[], int d, double coeficientes[][4],
                                   double x_aproximar[], int num_aproximaciones,
                                   double y_resultados[]) {
    int exitosas = 0;
    
    printf("\n=== CÁLCULO DE APROXIMACIONES ===\n");
    
    for (int i = 0; i < num_aproximaciones; i++) {
        double x_punto = x_aproximar[i];
        
        // Determinar en qué intervalo está x_punto
        int intervalo = -1;
        for (int k = 0; k < d-1; k++) {
            if (x_punto >= x[k] && x_punto <= x[k+1]) {
                intervalo = k;
                break;
            }
        }
        
        if (intervalo == -1) {
            printf("❌ x = %.6f está fuera del rango [%.2f, %.2f]\n", 
                   x_punto, x[0], x[d-1]);
            y_resultados[i] = 0.0;
            continue;
        }
        
        // Obtener coeficientes del spline correspondiente
        double a = coeficientes[intervalo][0];
        double b = coeficientes[intervalo][1];
        double c = coeficientes[intervalo][2];
        double d_coef = coeficientes[intervalo][3];
        
        // Calcular valor
        double resultado = a*x_punto*x_punto*x_punto + 
                          b*x_punto*x_punto + 
                          c*x_punto + 
                          d_coef;
        
        y_resultados[i] = resultado;
        exitosas++;
        
        // Mostrar cálculo paso a paso
        printf("\n--- Aproximación %d ---\n", i+1);
        printf("Valor a aproximar: x = %.6f\n", x_punto);
        printf("Spline utilizado: S%d en [%.2f, %.2f]\n", 
               intervalo, x[intervalo], x[intervalo+1]);
        printf("Coeficientes: a=%.6f, b=%.6f, c=%.6f, d=%.6f\n", a, b, c, d_coef);
        printf("Cálculo: ");
        printf("(%.6f)*(%.6f)³ + ", a, x_punto);
        printf("(%.6f)*(%.6f)² + ", b, x_punto);
        printf("(%.6f)*(%.6f) + ", c, x_punto);
        printf("(%.6f) = ", d_coef);
        printf("%.8f\n", resultado);
        printf("Resultado: y = %.8f\n", resultado);
    }
    printf("\n");
    
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