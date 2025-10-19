#include <stdio.h>
#include "spline_cubica.h"

// Configuración del problema
#define CANT_PUNTOS 5
#define MAX_PUNTOS_PROGRAMA CANT_PUNTOS

#include "../eliminacionGaussiana/gauss_solver.h"

#define CANT_APROXIMACIONES 4

int main() {
    printf("==================================================\n");
    printf("    EJEMPLO PRÁCTICO: USO DE LIBRERÍA SPLINES\n");
    printf("==================================================\n\n");
    
    double x[CANT_PUNTOS] = {0.0, 1.0, 2.0, 3.0, 4.0};
    double y[CANT_PUNTOS] = {1.0, 1.0, 3.0, 13.0, 37.0};
    
    printf("📊 DATOS DE ENTRADA:\n");
    printf("   Se utilizarán %d puntos para la interpolación:\n", CANT_PUNTOS);
    for (int i = 0; i < CANT_PUNTOS; i++) {
        printf("   Punto %d: (%.1f, %.1f)\n", i, x[i], y[i]);
    }
    printf("\n");
    
    double coeficientes[MAX_SEGMENTOS][4];
    
    printf("🔄 CALCULANDO SPLINES CÚBICOS...\n");
    printf("   - Sistema a resolver: %dx%d\n", 4*(CANT_PUNTOS-1), 4*(CANT_PUNTOS-1));
    printf("   - Segmentos de spline: %d\n", CANT_PUNTOS-1);
    
    // VERSIÓN ORIGINAL: Pasamos el parámetro d
    int resultado = spline_calcular_coeficientes(x, y, CANT_PUNTOS, coeficientes);
    
    if (resultado != 0) {
        printf("❌ ERROR: No se pudieron calcular los splines\n");
        return -1;
    }
    
    printf("✅ SPLINES CALCULADOS EXITOSAMENTE\n\n");
    
    // Resto del código igual...
    return 0;
}