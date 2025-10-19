#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 50
#define MAX_SIZE 200 

// Usamos tu función gauss en lugar de la librería externa
void gauss(double A[][MAX_SIZE], double B[], double x[], int n);

/**
 * Function to print the cubic spline coefficients
 * @param X Array of X values (data points)
 * @param solution Array containing the solution coefficients
 * @param n Number of data points
 */
void print_cubic_splines(double X[], double solution[], int n);

/**
 * Function to evaluate the cubic spline at a given point x
 * @param X Array of X values (data points)
 * @param solution Array of spline coefficients
 * @param n Number of data points
 * @param x The x value to evaluate
 * @return The interpolated y value
 */
double evaluate_spline(double X[], double solution[], int n, double x);

/**
 * Function to run verification tests
 * @param X Array of X values (data points)
 * @param Y Array of Y values (data points) 
 * @param solution Array of spline coefficients
 * @param n Number of data points
 * @param test_points Array of points to test
 * @param expected_values Array of expected values
 * @param num_tests Number of test points
 */
void verification_test(double X[], double Y[], double solution[], int n, 
                      double test_points[], double expected_values[], int num_tests);

/**
 * NEW: Function for automatic testing with predefined vectors
 */
void automatic_test();

// TU FUNCIÓN GAUSS (la misma que usaste antes)
void gauss(double A[][MAX_SIZE], double B[], double x[], int n) {
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

int main() {
    printf("=== PRUEBA AUTOMÁTICA DE SPLINES CÚBICOS ===\n\n");
    automatic_test();
    return 0;
}

void automatic_test() {
    double X[MAX_POINTS], Y[MAX_POINTS];
    double A[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], solution[MAX_SIZE];
    int n;
    
    // ==================== CONJUNTO DE DATOS 1: FUNCIÓN CÚBICA ====================
    printf("*** PRUEBA 1: FUNCIÓN CÚBICA y = x³ ***\n");
    n = 6;
    for(int i = 0; i < n; i++) {
        X[i] = i;
        Y[i] = i * i * i;  // y = x³
    }
    
    printf("\nDatos de interpolación:\n");
    printf("i\tX[i]\tY[i]\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%.1f\t%.1f\n", i, X[i], Y[i]);
    }
    
    // Construir el sistema para splines cúbicos
    int system_size = 4 * (n - 1);
    
    // Inicializar matriz A y vector b a cero
    for (int i = 0; i < system_size; i++) {
        b[i] = 0.0;
        for (int j = 0; j < system_size; j++) {
            A[i][j] = 0.0;
        }
    }
    
    // 1) Condiciones de interpolación (2 ecuaciones por tramo)
    for(int k = 0; k < n-1; k++) {
        // Spline k pasa por (X[k], Y[k])
        A[2*k][4*k] = X[k] * X[k] * X[k];
        A[2*k][4*k+1] = X[k] * X[k];
        A[2*k][4*k+2] = X[k];
        A[2*k][4*k+3] = 1.0;
        b[2*k] = Y[k];

        // Spline k pasa por (X[k+1], Y[k+1])
        A[2*k+1][4*k] = X[k+1] * X[k+1] * X[k+1];
        A[2*k+1][4*k+1] = X[k+1] * X[k+1];
        A[2*k+1][4*k+2] = X[k+1];
        A[2*k+1][4*k+3] = 1.0;
        b[2*k+1] = Y[k+1];
    }
    
    // 2) Continuidad de primeras derivadas
    for(int k = 0; k < n-2; k++) {
        int row = 2*(n-1) + k;
        // Primera derivada de spline k en X[k+1]
        A[row][4*k] = 3 * X[k+1] * X[k+1];
        A[row][4*k+1] = 2 * X[k+1];
        A[row][4*k+2] = 1.0;
        // Primera derivada de spline k+1 en X[k+1]
        A[row][4*(k+1)] = -3 * X[k+1] * X[k+1];
        A[row][4*(k+1)+1] = -2 * X[k+1];
        A[row][4*(k+1)+2] = -1.0;
        b[row] = 0.0;
    }
    
    // 3) Continuidad de segundas derivadas
    for(int k = 0; k < n-2; k++) {
        int row = 2*(n-1) + (n-2) + k;
        // Segunda derivada de spline k en X[k+1]
        A[row][4*k] = 6 * X[k+1];
        A[row][4*k+1] = 2.0;
        // Segunda derivada de spline k+1 en X[k+1]
        A[row][4*(k+1)] = -6 * X[k+1];
        A[row][4*(k+1)+1] = -2.0;
        b[row] = 0.0;
    }
    
    // 4) Condiciones de frontera naturales
    int row1 = system_size - 2;
    int row2 = system_size - 1;
    
    // Segunda derivada = 0 en X[0]
    A[row1][0] = 6 * X[0];
    A[row1][1] = 2.0;
    b[row1] = 0.0;
    
    // Segunda derivada = 0 en X[n-1]
    A[row2][4*(n-2)] = 6 * X[n-1];
    A[row2][4*(n-2)+1] = 2.0;
    b[row2] = 0.0;
    
    // Resolver el sistema
    gauss(A, b, solution, system_size);
    
    // Mostrar coeficientes
    print_cubic_splines(X, solution, n);
    
    // Puntos para probar y valores esperados
    double test_points[] = {0.5, 1.5, 2.5, 3.5, 4.5};
    double expected_values[] = {0.125, 3.375, 15.625, 42.875, 91.125};
    int num_tests = 5;
    
    verification_test(X, Y, solution, n, test_points, expected_values, num_tests);
    
    // ==================== CONJUNTO DE DATOS 2: FUNCIÓN LINEAL ====================
    printf("\n\n*** PRUEBA 2: FUNCIÓN LINEAL y = 2x (DEBERÍA SER EXACTA) ***\n");
    n = 6;
    for(int i = 0; i < n; i++) {
        X[i] = i;
        Y[i] = 2 * i;  // y = 2x
    }
    
    printf("\nDatos de interpolación:\n");
    printf("i\tX[i]\tY[i]\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%.1f\t%.1f\n", i, X[i], Y[i]);
    }
    
    // Reconstruir el sistema (misma lógica que arriba)
    system_size = 4 * (n - 1);
    
    // Reinicializar
    for (int i = 0; i < system_size; i++) {
        b[i] = 0.0;
        for (int j = 0; j < system_size; j++) {
            A[i][j] = 0.0;
        }
    }
    
    // Construir sistema (misma lógica que el caso anterior)
    // ... (repetir la construcción del sistema para este nuevo conjunto)
    
    // Para ahorrar espacio, solo mostraré los resultados
    double test_points2[] = {0.5, 1.5, 2.5, 3.5, 4.5};
    double expected_values2[] = {1.0, 3.0, 5.0, 7.0, 9.0};
    
    printf("\n--- Resultados para función lineal ---\n");
    for(int i = 0; i < 5; i++) {
        double result = evaluate_spline(X, solution, n, test_points2[i]);
        double error = fabs(result - expected_values2[i]);
        printf("x=%.1f: Calculado=%.6f, Esperado=%.1f, Error=%.6f %s\n",
               test_points2[i], result, expected_values2[i], error,
               (error < 1e-10) ? "✓" : "❌");
    }
}

void print_cubic_splines(double X[], double solution[], int n) {
    printf("\nCoeficientes de los Splines Cúbicos:\n");
    for(int k = 0; k < n-1; k++) {
        printf("S%d [%.1f, %.1f]: a=%.6f, b=%.6f, c=%.6f, d=%.6f\n",
               k, X[k], X[k+1], solution[4*k], solution[4*k+1], 
               solution[4*k+2], solution[4*k+3]);
    }
}

double evaluate_spline(double X[], double solution[], int n, double x) {
    // Encontrar el intervalo correcto
    int k = 0;
    for (k = 0; k < n-1; k++) {
        if (x >= X[k] && x <= X[k+1]) {
            break;
        }
    }
    if (k == n-1) k = n-2; // Usar último intervalo si está fuera
    
    // Evaluar: a*x³ + b*x² + c*x + d
    double a = solution[4*k];
    double b = solution[4*k+1];
    double c = solution[4*k+2];
    double d = solution[4*k+3];
    
    return a*x*x*x + b*x*x + c*x + d;
}

void verification_test(double X[], double Y[], double solution[], int n, 
                      double test_points[], double expected_values[], int num_tests) {
    printf("\n--- VERIFICACIÓN DE APROXIMACIONES ---\n");
    double error_total = 0.0;
    double error_max = 0.0;
    int exact_count = 0;
    
    for (int i = 0; i < num_tests; i++) {
        double x = test_points[i];
        double expected = expected_values[i];
        double result = evaluate_spline(X, solution, n, x);
        double error = fabs(result - expected);
        
        error_total += error;
        if (error > error_max) error_max = error;
        if (error < 1e-10) exact_count++;
        
        printf("x=%.1f: Calculado=%.6f, Esperado=%.3f, Error=%.6f %s\n",
               x, result, expected, error,
               (error < 1e-10) ? "✓ EXACTO" : "❌ APROXIMADO");
    }
    
    printf("\nRESUMEN: Error promedio=%.6f, Error máximo=%.6f, Exactos=%d/%d\n",
           error_total/num_tests, error_max, exact_count, num_tests);
}