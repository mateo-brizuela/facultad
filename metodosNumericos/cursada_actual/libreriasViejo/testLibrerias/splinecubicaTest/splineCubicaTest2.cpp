#include <stdio.h>
#include "../../splineCubica.h"

int main() {
    // Datos más exigentes: función con cambios bruscos, no equiespaciados
    double x[] = {0.1, 0.5, 1.2, 2.8, 4.1, 5.5, 7.0, 8.5};
    double y[] = {0.875, 2.528, 13.432, 48.171, 127.625, 250.000, 350.000, 420.000};
    int d = 8;  // Ahora tenemos 8 puntos para mayor precisión

    // Puntos de interpolación MUY exigentes: 
    // - Muy cercanos entre sí
    // - En regiones con alta curvatura
    // - Incluyendo extrapolación suave
    double x_interp[] = {
        0.05,   // Extrapolación a la izquierda
        0.1,    // Punto conocido (debería dar exacto)
        0.3,    // Entre 0.1 y 0.5
        0.5,    // Punto conocido
        0.8,    // Entre 0.5 y 1.2
        1.2,    // Punto conocido
        2.0,    // Entre 1.2 y 2.8 (región de alta curvatura)
        2.8,    // Punto conocido
        3.5,    // Entre 2.8 y 4.1
        4.1,    // Punto conocido
        4.8,    // Entre 4.1 y 5.5
        5.5,    // Punto conocido
        6.2,    // Entre 5.5 y 7.0
        7.0,    // Punto conocido
        7.8,    // Entre 7.0 y 8.5
        8.5,    // Punto conocido
        9.0     // Extrapolación a la derecha
    };
    
    int n_interp = sizeof(x_interp) / sizeof(x_interp[0]); 
    double y_interp[n_interp];

    // Usar la librería propia
    splineCubicaAproximar(x, y, d, x_interp, y_interp, n_interp);

    printf("=== INTERPOLACIÓN SPLINE CÚBICA - PRUEBA EXIGENTE ===\n");
    printf("Puntos conocidos (%d puntos):\n", d);
    for (int i = 0; i < d; i++) {
        printf("  (%.1f, %.3f)\n", x[i], y[i]);
    }
    
    printf("\nResultados de la interpolación (%d puntos):\n", n_interp);
    printf("x_interp\t\ty_interp\t\tTipo\n");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < n_interp; ++i) {
        // Identificar si es punto conocido, interpolación o extrapolación
        const char* tipo = "Interpolación";
        for (int j = 0; j < d; j++) {
            if (x_interp[i] == x[j]) {
                tipo = "Punto conocido";
                break;
            }
        }
        if (x_interp[i] < x[0]) tipo = "Extrapolación izquierda";
        if (x_interp[i] > x[d-1]) tipo = "Extrapolación derecha";
        
        printf("%.6f\t\t%.6f\t\t%s\n", x_interp[i], y_interp[i], tipo);
    }

    return 0;
}