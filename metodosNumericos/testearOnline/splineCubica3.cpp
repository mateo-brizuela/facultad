#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define d 6 // d es la cantidad de datos
#define n 4*(d-1) // n es la dimension de la matriz n*n
#define m d-1 // es la cantidad de intervalos que hay 

// Funciones para cargar y leer los datos
void cargarVector(double x[d], double y[d]);
void leerVector(double x[d], double y[d]);

// Funciones para armar, leer y resolver la matriz
void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]);
void leerMatriz(double A[n][n], double B[n]);
void gauss(double A[n][n], double B[n], double x[n]);

// Función para aproximar valores usando los splines
void aproximarSpline(double x[d], double y[d], double coeficientes[n]);

// Función para verificar resultados exactos
void verificarExactitud(double x[d], double y[d], double coeficientes[n]);

int main(int argc, char const *argv[])
{
    double x[d], y[d], matriz[n][n], vector[n], incognitas[n];
    
    cargarVector(x,y);
    armarMatriz(x,y,matriz,vector);
    gauss(matriz,vector,incognitas);
    
    // Verificar exactitud en puntos conocidos
    verificarExactitud(x, y, incognitas);
    
    // Aproximar valores como en el programa original
    aproximarSpline(x, y, incognitas);

    return 0;
}

void cargarVector(double x[d], double y[d]){
    printf("=== CARGA DE DATOS PARA SPLINES CUBICOS ===\n");
    printf("Se cargarán %d puntos de datos\n\n", d);

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

    // 4) CONDICIONES DE FRONTERA MEJORADAS
    // Preguntar al usuario qué tipo de condiciones usar
    int opcion;
    printf("\n=== CONDICIONES DE FRONTERA ===\n");
    printf("1. Splines Naturales (S''=0 en extremos)\n");
    printf("2. Splines Completos (con derivadas exactas)\n");
    printf("Seleccione opcion (1 o 2): ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        // Splines naturales (S''=0 en extremos)
        matriz[row][0] = 6 * x[0];
        matriz[row][1] = 2.0;
        vector[row] = 0.0;
        row++;

        matriz[row][4*(m-1)]   = 6 * x[m];
        matriz[row][4*(m-1)+1] = 2.0;
        vector[row] = 0.0;
        printf("Usando condiciones naturales (S''=0 en extremos)\n");
    } else {
        // Splines completos (con derivadas exactas)
        // Calcular derivadas segundas numéricamente
        double derivada_inicio, derivada_fin;
        
        // Para el inicio: usar diferencia hacia adelante
        derivada_inicio = (y[2] - 2*y[1] + y[0]) / ((x[1]-x[0])*(x[2]-x[1]));
        
        // Para el fin: usar diferencia hacia atrás  
        derivada_fin = (y[m] - 2*y[m-1] + y[m-2]) / ((x[m]-x[m-1])*(x[m-1]-x[m-2]));
        
        matriz[row][0] = 6 * x[0];
        matriz[row][1] = 2.0;
        vector[row] = derivada_inicio;
        row++;

        matriz[row][4*(m-1)]   = 6 * x[m];
        matriz[row][4*(m-1)+1] = 2.0;
        vector[row] = derivada_fin;
        printf("Usando condiciones completas con derivadas aproximadas\n");
    }

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

void gauss(double A[n][n], double B[n], double x[n]){
    double prod = 1.0;
    double ceroDef = 1e-12; // Mejor tolerancia
    double sum = 0.0;

    // Eliminación gaussiana con pivoteo
    for (int i = 0; i < n; i++)
    {
        // Pivoteo parcial para evitar división por cero
        if (fabs(A[i][i]) < ceroDef)
        {
            int p = i;
            double aux;
            for (int l = i + 1; l < n; l++)
            {
                if (fabs(A[l][i]) > fabs(A[p][i])) {
                    p = l;
                }
            }

            // Intercambiar filas
            for (int u = 0; u < n; u++)
            {
                aux = A[p][u];
                A[p][u] = A[i][u];
                A[i][u] = aux;
            }
            aux = B[p];
            B[p] = B[i];
            B[i] = aux;
        }
        
        // Eliminación hacia adelante
        for (int j = i + 1; j < n; j++)
        {
            double factor = -A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
            {
                A[j][k] += A[i][k] * factor;
            }
            B[j] += B[i] * factor;
        }
    }

    printf("=== MATRIZ TRIANGULAR SUPERIOR ===\n");
    leerMatriz(A, B);
    
    // Verificar que la matriz sea invertible
    for (int i = 0; i < n; i++)
    {
        prod *= A[i][i];
    }
    if (fabs(prod) < ceroDef)
    {
        printf("Error: la matriz tiene determinante cero\n");
        exit(1);
    }

    // Sustitución hacia atrás
    x[n-1] = B[n-1] / A[n-1][n-1];
    for (int i = n-2; i >= 0; i--)
    {
        sum = B[i];
        for (int j = i + 1; j < n; j++)
        {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
}

void verificarExactitud(double x[d], double y[d], double coeficientes[n]) {
    printf("\n=== VERIFICACION EN PUNTOS DE DATOS ===\n");
    int exactos = 0;
    
    for (int i = 0; i < d; i++) {
        int spline_idx = (i == d-1) ? m-1 : i;
        int base = 4 * spline_idx;
        double a = coeficientes[base];
        double b = coeficientes[base+1];
        double c = coeficientes[base+2];
        double d_val = coeficientes[base+3];
        
        double resultado = a*x[i]*x[i]*x[i] + b*x[i]*x[i] + c*x[i] + d_val;
        double error = fabs(resultado - y[i]);
        
        printf("x[%d]=%.1f: Calculado=%.6f, Esperado=%.1f, Error=%e %s\n",
               i, x[i], resultado, y[i], error, 
               (error < 1e-10) ? "✓" : "✗");
               
        if (error < 1e-10) exactos++;
    }
    printf("Puntos exactos: %d/%d\n\n", exactos, d);
}

void aproximarSpline(double x[d], double y[d], double coeficientes[n]) {
    printf("\n=== RESULTADOS - COEFICIENTES DE LOS SPLINES ===\n");
    
    // Mostrar coeficientes de cada spline
    for (int k = 0; k < m; k++) {
        int base = 4*k;
        
        printf("\n--- Spline S%d (intervalo [%.2f, %.2f]) ---\n", 
               k, x[k], x[k+1]);
        printf("a = %12.6f, b = %12.6f, c = %12.6f, d = %12.6f\n",
               coeficientes[base], coeficientes[base+1], 
               coeficientes[base+2], coeficientes[base+3]);
    }

    // APROXIMACIÓN DE VALORES
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
            intervalo = (xr < x[0]) ? 0 : m-1;
        }
        
        // Calcular valor aproximado
        int base = 4 * intervalo;
        double a = coeficientes[base];
        double b = coeficientes[base+1];
        double c = coeficientes[base+2];
        double dr = coeficientes[base+3];
        
        double resultado = a*xr*xr*xr + b*xr*xr + c*xr + dr;
        
        printf("\n--- RESULTADO ---\n");
        printf("xr = %.6f\n", xr);
        printf("Spline utilizado: S%d ([%.2f, %.2f])\n", 
               intervalo, x[intervalo], x[intervalo+1]);
        printf("y = %.8f\n", resultado);
        
        // Preguntar si desea continuar
        printf("\n¿Desea aproximar otro valor? (s/n): ");
        scanf(" %c", &continuar);
    }
    
    printf("\n=== FIN DE LAS APROXIMACIONES ===\n");
}