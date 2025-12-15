#include <stdio.h>
#include <cmath>

// Librería propia para exportar (escribe en ./outputs/)
#include "../../librerias/io/exportarResultados.h"

// EDO del enunciado: y' = f(x,y) = (x * e^(x^2)) / y
static inline double f(double x, double y) {
    return (x * std::exp(x * x)) / y;
}

// Solución exacta: y(x) = e^(x^2 / 2)
static inline double y_exact(double x) {
    return std::exp(0.5 * x * x);
}

int main() {
    // Enunciado: intervalo [0,1], h = 0.1
    const double a = 0.0;
    const double b = 1.0;
    const double h = 0.1;
    const int    N = (int)((b - a) / h); // subintervalos = 10
    const int    P = N + 1;              // puntos = 11

    // Arreglos
    double *x = new double[P];
    double *y = new double[P];        // numérico (método 2 pasos)
    double *yex = new double[P];      // exacta (para comparar)
    double *err = new double[P];      // |y_num - y_exact|

    // Mallado y dato inicial
    for (int i = 0; i < P; ++i) x[i] = a + i * h;
    y[0] = 1.0;                // y(0) = 1
    yex[0] = y_exact(x[0]);
    err[0] = std::fabs(y[0] - yex[0]);

    // Paso de arranque (Euler) para obtener y1
    y[1] = y[0] + h * f(x[0], y[0]);

    // Método de dos pasos para i >= 1
    for (int i = 1; i < N; ++i) {
        y[i+1] = y[i] + h * ( 2.0 * f(x[i], y[i]) - f(x[i-1], y[i-1]) );
    }

    // Cargar exacta y error
    for (int i = 1; i < P; ++i) {
        yex[i] = y_exact(x[i]);
        err[i] = std::fabs(y[i] - yex[i]);
    }

    // Salida estilo “original”
    printf("Metodo de DOS PASOS (arranque con Euler) para y' = (x*e^(x^2))/y\n");
    printf("Intervalo [a,b] = [%.1f, %.1f] | h = %.1f | N = %d | P = %d\n", a, b, h, N, P);
    printf("i\t        x_i\t\t   y_i (num)\t\t y_exact\t\t   |error|\n");
    for (int i = 0; i < P; ++i) {
        printf("%2d\t%14.8f\t%16.10f\t%16.10f\t%16.6e\n", i, x[i], y[i], yex[i], err[i]);
    }

    // Pedidos puntuales del enunciado: y(0.5) y y(1.0)
    int i05 = (int)std::round((0.5 - a) / h); // 0.5 -> índice 5
    int i10 = (int)std::round((1.0 - a) / h); // 1.0 -> índice 10
    printf("\nResultados puntuales:\n");
    printf("y(0.5) num = %.10f | exacta = %.10f | err = %.6e\n",
           y[i05], yex[i05], err[i05]);
    printf("y(1.0) num = %.10f | exacta = %.10f | err = %.6e\n",
           y[i10], yex[i10], err[i10]);

    // Exportar (./outputs/) con tu helper
    // - Serie numérica (dos pasos)
    exportarDerivadas("edo_dos_pasos_num", x, y, P);
    // - Serie exacta
    exportarDerivadas("edo_dos_pasos_exacta", x, yex, P);
    // - Serie de error (mismo eje x)
    exportarDerivadas("edo_dos_pasos_error", x, err, P);

    delete[] x;
    delete[] y;
    delete[] yex;
    delete[] err;
    return 0;
}
