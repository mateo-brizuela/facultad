#include <stdio.h>
#include "../../splineCubica.h"

/**
 * Programa principal para probar la función de interpolación por spline cúbico.
 *
 * Parámetros utilizados:
 * - x: arreglo de valores de abscisas (puntos conocidos en el eje X).
 * - y: arreglo de valores de ordenadas (valores de la función en los puntos x).
 * - d: cantidad de puntos conocidos (tamaño de los arreglos x e y).
 * - x_interp: arreglo de puntos donde se desea evaluar/interpolar el spline cúbico.
 * - n_interp: cantidad de puntos a interpolar (tamaño de x_interp).
 * - y_interp: arreglo donde se almacenarán los resultados de la interpolación.
 *
 * El programa utiliza la función splineCubicaAproximar para calcular los valores interpolados
 * y luego imprime los resultados por pantalla.
 */
int main() {
    // Datos de ejemplo
    double x[] = {0.0, 1.0, 2.0, 3.0, 4.0};
    double y[] = {0.0, 0.5, 2.0, 1.5, 0.0};
    int d = 5;

    // Puntos donde se desea interpolar (puedes modificar este vector desde el código)
    double x_interp[] = {0.0, 0.5, 1.5, 2.5, 3.5, 4.0};
    int n_interp = sizeof(x_interp) / sizeof(x_interp[0]); 
    double y_interp[n_interp];

    // Usar la librería propia
    splineCubicaAproximar(x, y, d, x_interp, y_interp, n_interp);

    printf("Evaluación del spline cúbico en los puntos definidos en x_interp:\n");
    for (int i = 0; i < n_interp; ++i) {
        printf("s(%.6f) = %.6f\n", x_interp[i], y_interp[i]);
    }

    return 0;
}