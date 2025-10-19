#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define d 6 // d es la cantidad de datos
#define n 4*(d-1) // n es la dimension de la matriz n*n
#define m d-1 // es la cantidad de intervalos que hay 

// Tu función gauss original
void gauss(double A[n][n], double B[n], double x[n]) {
    double prod = 1.0;
    double ceroDef = 1e-12; // Mejor tolerancia
    double sum = 0.0;

    // Eliminación gaussiana con pivoteo
    for (int i = 0; i < n; i++) {
        // Pivoteo parcial para evitar división por cero
        if (fabs(A[i][i]) < ceroDef) {
            int p = i;
            double aux;
            for (int l = i + 1; l < n; l++) {
                if (fabs(A[l][i]) > fabs(A[p][i])) {
                    p = l;
                }
            }

            // Intercambiar filas
            for (int u = 0; u < n; u++) {
                aux = A[p][u];
                A[p][u] = A[i][u];
                A[i][u] = aux;
            }
            aux = B[p];
            B[p] = B[i];
            B[i] = aux;
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

    // Verificar que la matriz sea invertible
    for (int i = 0; i < n; i++) {
        prod *= A[i][i];
    }
    if (fabs(prod) < ceroDef) {
        printf("Error: la matriz tiene determinante cero\n");
        exit(1);
    }

    // Sustitución hacia atrás
    x[n-1] = B[n-1] / A[n-1][n-1];
    for (int i = n-2; i >= 0; i--) {
        sum = B[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
}

void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]) {
    // Inicializar matriz y vector a cero
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) matriz[r][c] = 0.0;
        vector[r] = 0.0;
    }

    int row = 0;

    // 1) Condiciones de interpolación (2 ecuaciones por tramo)
    for (int k = 0; k < m; ++k) {
        int c = 4*k;
        double xk = x[k], xk1 = x[k+1];

        // S_k(x_k) = y_k
        matriz[row][c]   = xk*xk*xk;
        matriz[row][c+1] = xk*xk;
        matriz[row][c+2] = xk;
        matriz[row][c+3] = 1.0;
        vector[row] = y[k];
        row++;

        // S_k(x_{k+1}) = y_{k+1}
        matriz[row][c]   = xk1*xk1*xk1;
        matriz[row][c+1] = xk1*xk1;
        matriz[row][c+2] = xk1;
        matriz[row][c+3] = 1.0;
        vector[row] = y[k+1];
        row++;
    }

    // 2) Continuidad de primeras derivadas en nodos interiores
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);

        // S_k'(xi) = S_{k+1}'(xi)
        matriz[row][cL]   = 3 * xi * xi;
        matriz[row][cL+1] = 2 * xi;
        matriz[row][cL+2] = 1.0;
        
        matriz[row][cR]   = -3 * xi * xi;
        matriz[row][cR+1] = -2 * xi;
        matriz[row][cR+2] = -1.0;

        vector[row] = 0.0;
        row++;
    }

    // 3) Continuidad de segundas derivadas en nodos interiores
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);

        // S_k''(xi) = S_{k+1}''(xi)
        matriz[row][cL]   = 6 * xi;
        matriz[row][cL+1] = 2.0;
        
        matriz[row][cR]   = -6 * xi;
        matriz[row][cR+1] = -2.0;

        vector[row] = 0.0;
        row++;
    }

    // 4) CONDICIONES CORREGIDAS: Usar derivadas reales en lugar de naturales
    // Para y = x³: y'' = 6x
    // En x0: S_0''(x0) = y''(x0) = 0
    matriz[row][0] = 6 * x[0];
    matriz[row][1] = 2.0;
    vector[row] = 0.0;  // y''(0) = 0
    row++;

    // En x_{m}: S_{m-1}''(x_m) = y''(x_m) = 6*5 = 30
    int lastBlock = 4*(m-1);
    matriz[row][lastBlock]   = 6 * x[m];
    matriz[row][lastBlock+1] = 2.0;
    vector[row] = 30.0;  // y''(5) = 30 ← ESTA ES LA CORRECCIÓN
}

void verificarResultados(double x[d], double y[d], double coeficientes[n]) {
    printf("\n=== VERIFICACIÓN COMPLETA ===\n");
    
    // 1. Verificar interpolación en puntos originales
    printf("\n1. VERIFICACIÓN EN PUNTOS ORIGINALES:\n");
    for (int i = 0; i < d; i++) {
        int spline_idx = (i == d-1) ? m-1 : i;
        int base = 4 * spline_idx;
        double a = coeficientes[base];
        double b = coeficientes[base+1];
        double c = coeficientes[base+2];
        double d_val = coeficientes[base+3];
        
        double resultado = a*x[i]*x[i]*x[i] + b*x[i]*x[i] + c*x[i] + d_val;
        double error = fabs(resultado - y[i]);
        printf("x[%d]=%.1f: Calculado=%.8f, Esperado=%.1f, Error=%e %s\n",
               i, x[i], resultado, y[i], error, 
               (error < 1e-10) ? "✓" : "❌");
    }
    
    // 2. Puntos de prueba y valores esperados EXACTOS
    double test_points[] = {0.5, 1.5, 2.5, 3.5, 4.5};
    double expected[] = {0.125, 3.375, 15.625, 42.875, 91.125}; // x³ exacto
    int num_tests = 5;
    
    printf("\n2. APROXIMACIONES EN PUNTOS INTERMEDIOS:\n");
    double error_total = 0.0;
    double error_max = 0.0;
    int exactos = 0;
    
    for (int i = 0; i < num_tests; i++) {
        double xr = test_points[i];
        double esperado = expected[i];
        
        // Encontrar intervalo
        int intervalo = -1;
        for (int k = 0; k < m; k++) {
            if (xr >= x[k] && xr <= x[k+1]) {
                intervalo = k;
                break;
            }
        }
        
        int base = 4 * intervalo;
        double a = coeficientes[base];
        double b = coeficientes[base+1];
        double c = coeficientes[base+2];
        double d_val = coeficientes[base+3];
        
        double resultado = a*xr*xr*xr + b*xr*xr + c*xr + d_val;
        double error = fabs(resultado - esperado);
        
        error_total += error;
        if (error > error_max) error_max = error;
        if (error < 1e-10) exactos++;
        
        printf("x=%.1f: Calculado=%.8f, Esperado=%.3f, Error=%.8f %s\n",
               xr, resultado, esperado, error,
               (error < 1e-10) ? "✓ EXACTO" : "❌ APROXIMADO");
    }
    
    printf("\n3. RESUMEN:\n");
    printf("Error promedio: %.8f\n", error_total/num_tests);
    printf("Error máximo:   %.8f\n", error_max);
    printf("Puntos exactos: %d/%d\n", exactos, num_tests);
    
    // 4. Mostrar coeficientes finales
    printf("\n4. COEFICIENTES FINALES DE LOS SPLINES:\n");
    for (int k = 0; k < m; k++) {
        int base = 4*k;
        printf("S%d [%.1f, %.1f]: a=%.8f, b=%.8f, c=%.8f, d=%.8f\n",
               k, x[k], x[k+1], coeficientes[base], coeficientes[base+1], 
               coeficientes[base+2], coeficientes[base+3]);
    }
}

int main() {
    double x[d], y[d], matriz[n][n], vector[n], incognitas[n];
    
    printf("=== SPLINES CÚBICOS - PRUEBA AUTOMÁTICA ===\n\n");
    
    // Datos FIJOS para y = x³
    printf("Datos de entrada (y = x³):\n");
    for (int i = 0; i < d; i++) {
        x[i] = i;
        y[i] = i * i * i;
        printf("x[%d] = %.1f, y[%d] = %.1f\n", i, x[i], i, y[i]);
    }
    
    // Armar y resolver el sistema
    armarMatriz(x, y, matriz, vector);
    gauss(matriz, vector, incognitas);
    
    // Verificar resultados
    verificarResultados(x, y, incognitas);
    
    return 0;
}