#include <stdio.h>
#include "../../splineCubicaSimple.h"

// Función original para comparar
double funcionOriginal(double x) {
    return 0.3 * x * x + 0.5 * x + 1.0;
}

int main() {
    // DATOS PARA 4 PUNTOS (d=4) - no equiespaciados
    double x[] = {0.0, 1.5, 3.2, 5.0};
    double y[] = {1.0, 2.575, 5.372, 8.5};
    int d = 4;
    int n = 4 * (d - 1);  // n = 12

    // Armar el sistema lineal (matriz 12x12)
    double matriz[12][12], vector[12], coef[12];
    armarMatrizSimple(x, y, d, matriz, vector);

    // Resolver el sistema
    gaussSimple(matriz, vector, coef, n);

    // Puntos donde interpolar (incluyendo los 4 originales)
    double x_interp[] = {0.0, 0.8, 1.5, 2.3, 3.2, 4.1, 5.0};
    int n_interp = sizeof(x_interp) / sizeof(x_interp[0]);
    double y_interp[n_interp];

    // Aproximar los valores
    aproximarSplineSimple(x, coef, d, x_interp, y_interp, n_interp);

    // OUTPUT DIRECTO
    printf("SPLINE CUBICA SIMPLE - 4 PUNTOS\n");
    printf("x_interp\ty_spline\n");
    for (int i = 0; i < n_interp; ++i) {
        printf("%.1f\t\t%.6f\n", x_interp[i], y_interp[i]);
    }

    return 0;
}