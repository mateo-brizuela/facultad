#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "../../librerias/eliminacionGaussiana/gauss_solver.h"

#define d 6 // d es la cantidad de datos
#define n 4*(d-1) // n es la dimension de la matriz n*n
#define m d-1 // es la cantidad de intervalos que hay 

// Funciones para cargar y leer los datos
void cargarVector(double x[d], double y[d]);
void leerVector(double x[d], double y[d]);

// Funciones para armar, leer y resolver la matriz
void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]);
void leerMatriz(double A[n][n], double B[n]);

// NUEVA: Función para aproximar valores usando los splines
void aproximarSpline(double x[d], double y[d], double coeficientes[n]);

int main(int argc, char const *argv[])
{
    double x[d], y[d], matriz[n][n], vector[n], incognitas[n], det = 1.0;
    
    cargarVector(x,y);
    armarMatriz(x,y,matriz,vector);
    gauss_solve(matriz,vector,incognitas,det);
    
    // NUEVO: Llamar a la función de aproximación
    aproximarSpline(x, y, incognitas);

    return 0;
}

void cargarVector(double x[d], double y[d]){
    printf("=== CARGA DE DATOS PARA SPLINES CUBICOS ===\n");

    for (int i = 0; i < d; i++)
    {
        printf("Ingrese x[%d]: ", i);
        scanf("%lf", &x[i]);
        printf("Ingrese y[%d]: ", i);
        scanf("%lf", &y[i]);
    }
    printf("\nDatos ingresados:\n");
    leerVector(x,y);
}

void leerVector(double x[d], double y[d]){
    printf("x\t|\ty\n");
    for (int i = 0; i < d; i++)
    {
        printf("%.2f\t|\t%.2f | indice: %d \n", x[i], y[i], i);
    }
    printf("\n");
}

void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]) {
    // Inicializar matriz y vector a cero
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) matriz[r][c] = 0.0;
        vector[r] = 0.0;
    }

    int row = 0; // Contador de filas

    // 1) Condiciones de interpolación (2 ecuaciones por tramo)
    for (int k = 0; k < m; ++k) {
        int c = 4*k; // Bloque del tramo k (coeficientes a,b,c,d para el spline k)
        double xk = x[k], xk1 = x[k+1];

        // S_k(x_k) = y_k  (ecuación: a*x³ + b*x² + c*x + d = y)
        matriz[row][c]   = xk*xk*xk;    // coeficiente a
        matriz[row][c+1] = xk*xk;       // coeficiente b  
        matriz[row][c+2] = xk;          // coeficiente c
        matriz[row][c+3] = 1.0;         // coeficiente d
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
        double xi = x[k+1]; // Punto de unión entre splines
        int cL = 4*k;     // Coeficientes del spline izquierdo
        int cR = 4*(k+1); // Coeficientes del spline derecho

        // S_k'(xi) = S_{k+1}'(xi)
        // Derivada: 3a*x² + 2b*x + c
        matriz[row][cL]   = 3 * xi * xi;   // 3a_k
        matriz[row][cL+1] = 2 * xi;        // 2b_k
        matriz[row][cL+2] = 1.0;           // c_k
        
        matriz[row][cR]   = -3 * xi * xi;  // -3a_{k+1}
        matriz[row][cR+1] = -2 * xi;       // -2b_{k+1}
        matriz[row][cR+2] = -1.0;          // -c_{k+1}

        vector[row] = 0.0;
        row++;
    }

    // 3) Continuidad de segundas derivadas en nodos interiores
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);

        // S_k''(xi) = S_{k+1}''(xi)
        // Segunda derivada: 6a*x + 2b
        matriz[row][cL]   = 6 * xi;    // 6a_k
        matriz[row][cL+1] = 2.0;       // 2b_k
        
        matriz[row][cR]   = -6 * xi;   // -6a_{k+1}
        matriz[row][cR+1] = -2.0;      // -2b_{k+1}

        vector[row] = 0.0;
        row++;
    }

    // 4) Condiciones de frontera naturales (segundas derivadas en extremos = 0)
    // En x0: S_0''(x0) = 0
    matriz[row][0] = 6 * x[0];  // 6a_0
    matriz[row][1] = 2.0;       // 2b_0
    vector[row] = 0.0;
    row++;

    // En x_{m}: S_{m-1}''(x_m) = 0
    int lastBlock = 4*(m-1); // Último bloque de coeficientes
    matriz[row][lastBlock]   = 6 * x[m];  // 6a_{m-1}
    matriz[row][lastBlock+1] = 2.0;       // 2b_{m-1}
    vector[row] = 0.0;

    printf("=== SISTEMA LINEAL CONSTRUIDO ===\n");
    leerMatriz(matriz, vector);
}

void leerMatriz(double A[n][n], double B[n]){
    printf("Matriz del sistema (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%8.2f ", A[i][j]);
        }
        printf(" | %8.2f\n", B[i]);
    }
    printf("\n");
}

// NUEVA FUNCIÓN: Mostrar splines y aproximar valores
void aproximarSpline(double x[d], double y[d], double coeficientes[n]) {
    printf("\n=== RESULTADOS - COEFICIENTES DE LOS SPLINES ===\n");
    
    // Mostrar coeficientes de cada spline
    for (int k = 0; k < m; k++) {
        int base = 4*k; // Posición base para los 4 coeficientes del spline k
        
        printf("\n--- Spline S%d (intervalo [%.2f, %.2f]) ---\n", 
               k, x[k], x[k+1]);
        printf("S%d(x) = a*x³ + b*x² + c*x + d\n", k);
        
        // Mostrar en notación decimal y científica
        printf("a = %12.6f  (%10.2e)\n", coeficientes[base], coeficientes[base]);
        printf("b = %12.6f  (%10.2e)\n", coeficientes[base+1], coeficientes[base+1]);
        printf("c = %12.6f  (%10.2e)\n", coeficientes[base+2], coeficientes[base+2]);
        printf("d = %12.6f  (%10.2e)\n", coeficientes[base+3], coeficientes[base+3]);
        
        // Mostrar ecuación completa
        printf("Ecuacion: S%d(x) = ", k);
        printf("(%.6f)x³ + (%.6f)x² + (%.6f)x + (%.6f)\n", 
               coeficientes[base], coeficientes[base+1], 
               coeficientes[base+2], coeficientes[base+3]);
    }

    // APROXIMACIÓN DE VALORES - MODIFICADO PARA MÚLTIPLES APROXIMACIONES
    printf("\n=== APROXIMACION DE VALORES ===\n");
    
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        double xr;
        
        printf("\nIngrese el valor xr que desea aproximar: ");
        scanf("%lf", &xr);
        
        // Determinar en qué intervalo está xr
        int intervalo = -1;
        for (int k = 0; k < m; k++) {
            if (xr >= x[k] && xr <= x[k+1]) {
                intervalo = k;
                break;
            }
        }
        
        if (intervalo == -1) {
            printf("ADVERTENCIA: xr = %.2f está fuera del rango [%.2f, %.2f]\n", 
                   xr, x[0], x[d-1]);
            printf("Se usará el spline más cercano.\n");
            // Usar el último intervalo por defecto
            intervalo = m-1;
        }
        
        // Calcular valor aproximado usando el spline correspondiente
        int base = 4 * intervalo;
        double a = coeficientes[base];
        double b = coeficientes[base+1];
        double c = coeficientes[base+2];
        double dr = coeficientes[base+3];
        
        // Evaluar polinomio: a*xr³ + b*xr² + c*xr + d
        double resultado = a*xr*xr*xr + b*xr*xr + c*xr + dr;
        
        printf("\n--- RESULTADO DE LA APROXIMACION ---\n");
        printf("Valor a aproximar: xr = %.6f\n", xr);
        printf("Spline utilizado: S%d (intervalo [%.2f, %.2f])\n", 
               intervalo, x[intervalo], x[intervalo+1]);
        printf("Resultado:\n");
        printf("  Notacion decimal:    %12.8f\n", resultado);
        printf("  Notacion cientifica: %12.6e\n", resultado);
        
        // Mostrar cálculo paso a paso
        printf("\nCalculo detallado:\n");
        printf("S%d(%.6f) = ", intervalo, xr);
        printf("(%.6f)*(%.6f)³ + ", a, xr);
        printf("(%.6f)*(%.6f)² + ", b, xr);
        printf("(%.6f)*(%.6f) + ", c, xr);
        printf("(%.6f) = %.8f\n", dr, resultado);
        
        // Preguntar si desea continuar
        printf("\n¿Desea aproximar otro valor? (s/n): ");
        scanf(" %c", &continuar); // El espacio antes de %c es importante para ignorar el enter anterior
    }
    
    printf("\n=== FIN DE LAS APROXIMACIONES ===\n");
}