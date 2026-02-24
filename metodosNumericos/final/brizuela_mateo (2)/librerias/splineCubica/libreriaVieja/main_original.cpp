#include <stdio.h>
#include "spline_cubica.h"

#define CANT_PUNTOS 3  // Empezar con 3 puntos (más simple)
#define CANT_APROXIMACIONES 2

int main() {
    printf("=========================================\n");
    printf("   PRUEBA SPLINES CUBICOS (DEBUG)\n");
    printf("=========================================\n");
    
    // Prueba con 3 puntos primero (sistema 8x8)
    double x[CANT_PUNTOS] = {0.0, 1.0, 3.0};
    double y[CANT_PUNTOS] = {1.0, 2.0, 4.0};
    
    printf("Puntos de datos:\n");
    for (int i = 0; i < CANT_PUNTOS; i++) {
        printf("  (%.1f, %.1f)\n", x[i], y[i]);
    }
    printf("\n");
    
    // Matriz para coeficientes
    double coeficientes[MAX_SEGMENTOS][4];
    
    // 1. Calcular coeficientes
    printf("=== CALCULANDO COEFICIENTES ===\n");
    int resultado = spline_calcular_coeficientes(x, y, CANT_PUNTOS, coeficientes);
    
    if (resultado != 0) {
        printf("Error: no se pudieron calcular los splines\n");
        return -1;
    }
    
    printf("✅ Coeficientes calculados exitosamente!\n\n");
    
    // 2. Imprimir ecuaciones
    spline_imprimir_ecuaciones(x, CANT_PUNTOS, coeficientes);
    
    // 3. Evaluar en puntos
    printf("=== EVALUANDO SPLINES ===\n");
    double x_aproximar[CANT_APROXIMACIONES] = {0.5, 2.0};
    double y_resultados[CANT_APROXIMACIONES];
    int segmentos_usados[CANT_APROXIMACIONES];
    
    int exitosas = spline_evaluar_multiples_puntos(x, CANT_PUNTOS, coeficientes,
                                                  x_aproximar, CANT_APROXIMACIONES,
                                                  y_resultados, segmentos_usados);
    
    printf("Aproximaciones exitosas: %d/%d\n", exitosas, CANT_APROXIMACIONES);
    
    for (int i = 0; i < CANT_APROXIMACIONES; i++) {
        if (segmentos_usados[i] >= 0) {
            printf("S(%.1f) = %.6f [S%d]\n", x_aproximar[i], y_resultados[i], segmentos_usados[i]);
        }
    }
    
    printf("\n=========================================\n");
    printf("   PRUEBA COMPLETADA\n");
    printf("=========================================\n");
    
    return 0;
}