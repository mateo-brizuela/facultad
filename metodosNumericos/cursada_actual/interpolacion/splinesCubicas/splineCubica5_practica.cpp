#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "../../librerias/eliminacionGaussiana/gauss_solver.h"

// Número de puntos de datos (d), número de incógnitas del sistema n = 4*(d-1)
// y número de intervalos m = d-1.
// Cambiar d aquí actualiza automáticamente n y m.
#define d 5 // d es la cantidad de datos
#define n 4*(d-1) // n es la dimension de la matriz n*n (4 coef por intervalo)
#define m d-1 // es la cantidad de intervalos que hay 

// Funciones para cargar y leer los datos
void cargarVector(double x[d], double y[d]);
void leerVector(double x[d], double y[d]);

// Funciones para armar, leer y resolver la matriz
void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]);
void leerMatriz(double A[n][n], double B[n]);

// NUEVA: Función para aproximar valores usando los splines (muestra coef y tabla)
void aproximarSpline(double x[d], double y[d], double coeficientes[n]);

// prototipos nuevos (separación de responsabilidades)
double f_exact(double xi); // función exacta del enunciado
void generarTablaEquiespaciada(const double x[d], const double coeficientes[n], int puntos);

int main(int argc, char const *argv[])
{
    double x[d], y[d], matriz[n][n], vector[n], incognitas[n], det = 1.0;
    
    cargarVector(x,y);
    armarMatriz(x,y,matriz,vector);
    // Convertir matriz[n][n] a double** si el solver lo requiere
    double **A = new double*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new double[n];
        for (int j = 0; j < n; ++j) A[i][j] = matriz[i][j];
    }
    // Llamar al solver correcto; ajustá el nombre/firmas según el header real
    int status = gauss_solve_dynamic(n, A, vector, incognitas, det);
    if (status != 0) {
        printf("gauss_solve_dynamic devolvió error %d\n", status);
    }
    // liberar memoria A
    for (int i = 0; i < n; ++i) delete[] A[i];
    delete[] A;
    
    // NUEVO: Llamar a la función de aproximación (versión práctica)
    aproximarSpline(x, y, incognitas);

    return 0;
}

void cargarVector(double x[d], double y[d]){
    // Lectura interactiva de los d puntos (x_i, y_i)
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
    // Muestra los pares cargados (útil para verificar entrada)
    printf("x\t|\ty\n");
    for (int i = 0; i < d; i++)
    {
        printf("%.2f\t|\t%.2f | indice: %d \n", x[i], y[i], i);
    }
    printf("\n");
}

void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]) {
    // Construye el sistema lineal para coeficientes de splines cúbicos naturales.
    // Orden de incógnitas: [a0,b0,c0,d0, a1,b1,c1,d1, ..., a_{m-1},b_{m-1},c_{m-1},d_{m-1}]
    // Cada bloque de 4 coeficientes corresponde a un intervalo.

    // Inicializar matriz y vector a cero
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) matriz[r][c] = 0.0;
        vector[r] = 0.0;
    }

    int row = 0; // Contador de filas del sistema

    // 1) Condiciones de interpolación: S_k(x_k)=y_k y S_k(x_{k+1})=y_{k+1} (2 ecuaciones por tramo)
    for (int k = 0; k < m; ++k) {
        int c = 4*k; // índice base de coeficientes para el tramo k
        double xk = x[k], xk1 = x[k+1];

        // S_k(x_k) = y_k
        matriz[row][c]   = xk*xk*xk;    // a * x_k^3
        matriz[row][c+1] = xk*xk;       // b * x_k^2
        matriz[row][c+2] = xk;          // c * x_k
        matriz[row][c+3] = 1.0;         // d
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

    // 2) Continuidad de primeras derivadas en nodos interiores: S_k'(x_{k+1}) = S_{k+1}'(x_{k+1})
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1]; // nodo interior
        int cL = 4*k;     // bloque izquierdo
        int cR = 4*(k+1); // bloque derecho

        // derivada: 3a*x^2 + 2b*x + c
        matriz[row][cL]   = 3 * xi * xi;   // 3a_k
        matriz[row][cL+1] = 2 * xi;        // 2b_k
        matriz[row][cL+2] = 1.0;           // c_k
        
        matriz[row][cR]   = -3 * xi * xi;  // -3a_{k+1}
        matriz[row][cR+1] = -2 * xi;       // -2b_{k+1}
        matriz[row][cR+2] = -1.0;          // -c_{k+1}

        vector[row] = 0.0;
        row++;
    }

    // 3) Continuidad de segundas derivadas en nodos interiores: S_k''(xi) = S_{k+1}''(xi)
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);

        // segunda derivada: 6a*x + 2b
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
    int lastBlock = 4*(m-1); // índice del último bloque de coeficientes
    matriz[row][lastBlock]   = 6 * x[m];  // 6a_{m-1}
    matriz[row][lastBlock+1] = 2.0;       // 2b_{m-1}
    vector[row] = 0.0;

    printf("=== SISTEMA LINEAL CONSTRUIDO ===\n");
    leerMatriz(matriz, vector);
}

void leerMatriz(double A[n][n], double B[n]){
    // Impresión por pantalla del sistema (útil para depurar)
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

// NUEVA FUNCIÓN: Mostrar splines y aproximar valores (versión práctica)
// Incluye además generación de tabla en puntos equiespaciados (inciso b)
void aproximarSpline(double x[d], double y[d], double coeficientes[n]) {
    // Muestra coeficientes y ecuaciones de cada spline
    printf("\n=== RESULTADOS - COEFICIENTES DE LOS SPLINES ===\n");
    
    // Recorrer cada spline (m intervalos)
    for (int k = 0; k < m; k++) {
        int base = 4*k; // posición base para los 4 coeficientes del spline k
        
        printf("\n--- Spline S%d (intervalo [%.2f, %.2f]) ---\n", 
               k, x[k], x[k+1]);
        printf("S%d(x) = a*x³ + b*x² + c*x + d\n", k);
        
        // Mostrar coeficientes en formato legible
        printf("a = %12.6f  (%10.2e)\n", coeficientes[base], coeficientes[base]);
        printf("b = %12.6f  (%10.2e)\n", coeficientes[base+1], coeficientes[base+1]);
        printf("c = %12.6f  (%10.2e)\n", coeficientes[base+2], coeficientes[base+2]);
        printf("d = %12.6f  (%10.2e)\n", coeficientes[base+3], coeficientes[base+3]);
        
        printf("Ecuacion: S%d(x) = ", k);
        printf("(%.6f)x³ + (%.6f)x² + (%.6f)x + (%.6f)\n", 
               coeficientes[base], coeficientes[base+1], 
               coeficientes[base+2], coeficientes[base+3]);
    }

    // INCISO b) generar tabla con puntos equiespaciados (conservar d puntos)
    generarTablaEquiespaciada(x, coeficientes, d);

    // APROXIMACIÓN INTERACTIVA: permite evaluar cualquier xr usando los splines calculados
    printf("\n=== APROXIMACION INTERACTIVA ===\n");
    
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        double xr;
        
        printf("\nIngrese el valor xr que desea aproximar: ");
        scanf("%lf", &xr);
        
        // Buscar intervalo donde cae xr (si está fuera se usa el último spline)
        int intervalo = -1;
        for (int k = 0; k < m; k++) {
            if (xr >= x[k] && xr <= x[k+1]) {
                intervalo = k;
                break;
            }
        }
        
        if (intervalo == -1) {
            printf("ADVERTENCIA: xr = %.6f está fuera del rango [%.6f, %.6f]\n", 
                   xr, x[0], x[d-1]);
            printf("Se usará el spline más cercano.\n");
            intervalo = m-1;
        }
        
        // Evaluar el polinomio del spline correspondiente
        int base = 4 * intervalo;
        double a = coeficientes[base];
        double b = coeficientes[base+1];
        double c = coeficientes[base+2];
        double dr = coeficientes[base+3];
        
        double resultado = a*xr*xr*xr + b*xr*xr + c*xr + dr;
        
        printf("\n--- RESULTADO DE LA APROXIMACION ---\n");
        printf("Valor a aproximar: xr = %.6f\n", xr);
        printf("Spline utilizado: S%d (intervalo [%.6f, %.6f])\n", 
               intervalo, x[intervalo], x[intervalo+1]);
        printf("Resultado:\n");
        printf("  Notacion decimal:    %12.8f\n", resultado);
        printf("  Notacion cientifica: %12.6e\n", resultado);
        
        // Desglose del cálculo (útil para verificar paso a paso)
        printf("\nCalculo detallado:\n");
        printf("S%d(%.6f) = ", intervalo, xr);
        printf("(%.6f)*(%.6f)³ + ", a, xr);
        printf("(%.6f)*(%.6f)² + ", b, xr);
        printf("(%.6f)*(%.6f) + ", c, xr);
        printf("(%.6f) = %.8f\n", dr, resultado);
        
        // Preguntar si desea continuar
        printf("\n¿Desea aproximar otro valor? (s/n): ");
        scanf(" %c", &continuar); // espacio para consumir salto de línea
    }
    
    printf("\n=== FIN DE LAS APROXIMACIONES ===\n");
}

// Implementaciones nuevas

// Retorna el valor exacto de la función del enunciado f(x) = ln(x^2 + 1) - sin(x)
// Separada para facilitar pruebas y reutilización.
double f_exact(double xi) {
    return log(xi*xi + 1.0) - sin(xi);
}

// Genera e imprime la tabla pedida en el inciso b:
// - puntos: número de puntos equiespaciados a generar (se pide conservar d)
void generarTablaEquiespaciada(const double x[d], const double coeficientes[n], int puntos) {
    if (puntos < 2) puntos = 2;
    double xe[puntos], ye_exact[puntos], ye_interp[puntos], err[puntos];

    // paso equiespaciado en el intervalo [x0, x_{d-1}]
    double h_eq = (x[d-1] - x[0]) / (double)(puntos - 1);

    for (int i = 0; i < puntos; ++i) {
        xe[i] = x[0] + i * h_eq;
        ye_exact[i] = f_exact(xe[i]);

        // localizar intervalo correspondiente (si cae justo en nodo interior, se asigna al intervalo izquierdo)
        int intervalo = -1;
        if (xe[i] <= x[0]) intervalo = 0;
        else if (xe[i] >= x[d-1]) intervalo = m - 1;
        else {
            for (int k = 0; k < m; ++k) {
                if (xe[i] >= x[k] && xe[i] <= x[k+1]) { intervalo = k; break; }
            }
            if (intervalo == -1) intervalo = m - 1; // seguridad
        }

        // obtener coeficientes del spline del intervalo encontrado
        int base = 4 * intervalo;
        double a = coeficientes[base];
        double b = coeficientes[base+1];
        double c = coeficientes[base+2];
        double dd = coeficientes[base+3];

        double xr = xe[i];
        ye_interp[i] = a*xr*xr*xr + b*xr*xr + c*xr + dd;
        err[i] = fabs(ye_exact[i] - ye_interp[i]);
    }

    // imprimir tabla equiespaciada con error absoluto
    printf("\n=== INCISO b) TABLA EN PUNTOS EQUIDISTANTES (puntos = %d) ===\n", puntos);
    printf("\n i\t    x_i\t      y_exact\t   y_interp\t   |error|\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < puntos; ++i) {
        printf("%2d\t%8.5f\t%12.6f\t%12.6f\t%12.6f\n",
               i, xe[i], ye_exact[i], ye_interp[i], err[i]);
    }

    // (Opcional) exportar resultados a archivos si se desea (activar exportarResultados)
    // exportarTabla("spline_equi_exact_pract", xe, ye_exact, puntos);
    // exportarTabla("spline_equi_interp_pract", xe, ye_interp, puntos);
}