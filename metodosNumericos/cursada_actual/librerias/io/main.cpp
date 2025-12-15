#include <stdio.h>
#include "exportarResultados.h"

int main(void) {
    // Puntos de ejemplo (modificalos en el código si queres)
    double xi[] = {0.05, 0.1, 0.3, 0.5, 0.8, 1.2, 2.0, 2.8, 3.5, 4.1, 4.8, 5.5, 6.2, 7.0, 7.8, 8.5, 9.0};
    double yi[] = {0.10, 0.20, 0.55, 0.80, 1.25, 1.80, 3.60, 6.50, 9.10, 12.75, 15.30, 18.00, 20.40, 24.10, 27.80, 30.00, 32.50};
    int n = (int)(sizeof(xi) / sizeof(xi[0]));

    printf("Exportando %d puntos con base 'misResultados'\n", n);
    exportarDerivadas("misResultados", xi, yi, n);
    printf("Archivos generados en el directorio de ejecución:\n");
    printf(" - misResultados_tabla.txt\n");
    printf(" - misResultados_geogebra.txt\n");
    return 0;
}