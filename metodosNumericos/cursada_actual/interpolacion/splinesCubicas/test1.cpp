#include <stdio.h>
#include <stdlib.h>
#include <cmath>

// Cambiamos la cantidad de datos y los datos a los del test exigente
#define d 8 // cantidad de datos
#define n 4*(d-1) // dimension de la matriz n*n
#define m d-1 // cantidad de intervalos

// Funciones para leer los datos
void leerVector(double x[d], double y[d]);

// Funciones para armar, leer y resolver la matriz
void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]);
void leerMatriz(double A[n][n], double B[n]);
void gauss(double A[n][n], double B[n], double x[n]);

// NUEVA: Función para aproximar valores usando los splines
void aproximarSpline(double x[d], double y[d], double coeficientes[n]);

int main(int argc, char const *argv[])
{
    // Datos del test exigente
    double x[d] = {0.1, 0.5, 1.2, 2.8, 4.1, 5.5, 7.0, 8.5};
    double y[d] = {0.875, 2.528, 13.432, 48.171, 127.625, 250.000, 350.000, 420.000};
    double matriz[n][n], vector[n], incognitas[n];

    printf("=== DATOS CARGADOS AUTOMATICAMENTE ===\n");
    leerVector(x, y);

    armarMatriz(x, y, matriz, vector);
    gauss(matriz, vector, incognitas);

    // NUEVO: Llamar a la función de aproximación
    aproximarSpline(x, y, incognitas);

    return 0;
}

void leerVector(double x[d], double y[d]){
    printf("x\t|\ty\n");
    for (int i = 0; i < d; i++)
    {
        printf("%.3f\t|\t%.3f | indice: %d \n", x[i], y[i], i);
    }
    printf("\n");
}

void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]) {
    // ...igual que antes...
    // (sin cambios respecto a tu versión original)
    // ...código omitido por brevedad...
    // Puedes copiar aquí la función armarMatriz de tu archivo original
}

void leerMatriz(double A[n][n], double B[n]){
    // ...igual que antes...
    // ...código omitido por brevedad...
}

void gauss(double A[n][n], double B[n], double x[n]){
    // ...igual que antes...
    // ...código omitido por brevedad...
}

void aproximarSpline(double x[d], double y[d], double coeficientes[n]) {
    // Puntos de interpolación exigentes del test
    double x_interp[] = {
        0.05, 0.1, 0.3, 0.5, 0.8, 1.2, 2.0, 2.8, 3.5, 4.1, 4.8, 5.5, 6.2, 7.0, 7.8, 8.5, 9.0
    };
    int n_interp = sizeof(x_interp) / sizeof(x_interp[0]);
    double y_interp[n_interp];

    printf("\n=== RESULTADOS - COEFICIENTES DE LOS SPLINES ===\n");
    for (int k = 0; k < m; k++) {
        int base = 4*k;
        printf("\n--- Spline S%d (intervalo [%.2f, %.2f]) ---\n", k, x[k], x[k+1]);
        printf("S%d(x) = a*x³ + b*x² + c*x + d\n", k);
        printf("a = %12.6f  (%10.2e)\n", coeficientes[base], coeficientes[base]);
        printf("b = %12.6f  (%10.2e)\n", coeficientes[base+1], coeficientes[base+1]);
        printf("c = %12.6f  (%10.2e)\n", coeficientes[base+2], coeficientes[base+2]);
        printf("d = %12.6f  (%10.2e)\n", coeficientes[base+3], coeficientes[base+3]);
        printf("Ecuacion: S%d(x) = (%.6f)x³ + (%.6f)x² + (%.6f)x + (%.6f)\n",
               k, coeficientes[base], coeficientes[base+1], coeficientes[base+2], coeficientes[base+3]);
    }

    // Aproximar todos los puntos del test
    printf("\n=== APROXIMACION DE VALORES (test exigente) ===\n");
    printf("x_interp\t\ty_interp\n");
    printf("-------------------------------\n");
    for (int i = 0; i < n_interp; i++) {
        double xr = x_interp[i];
        int intervalo = -1;
        for (int k = 0; k < m; k++) {
            if (xr >= x[k] && xr <= x[k+1]) {
                intervalo = k;
                break;
            }
        }
        if (intervalo == -1) intervalo = m-1;
        int base = 4 * intervalo;
        double a = coeficientes[base];
        double b = coeficientes[base+1];
        double c = coeficientes[base+2];
        double dr = coeficientes[base+3];
        y_interp[i] = a*xr*xr*xr + b*xr*xr + c*xr + dr;
        printf("%10.3f\t%12.6f\n", xr, y_interp[i]);
    }
}