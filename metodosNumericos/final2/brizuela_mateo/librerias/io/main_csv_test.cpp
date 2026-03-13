#include <stdio.h>
#include <cmath>
#include "exportarResultados.h"

int main() {
    printf("=== TEST DE EXPORTACION E IMPORTACION CSV ===\n\n");

    // PARTE 1: Crear datos y exportar
    printf("1. Exportando datos de ejemplo...\n");
    int n_original = 10;
    double x_original[10];
    double y_original[10];

    for (int i = 0; i < n_original; ++i) {
        x_original[i] = 1.0 + i * 0.5;
        y_original[i] = sin(x_original[i]);
    }

    printf("   Datos originales:\n");
    printf("   i\tx\t\ty\n");
    for (int i = 0; i < n_original; ++i) {
        printf("   %d\t%.6f\t\t%.8f\n", i, x_original[i], y_original[i]);
    }

    // Exportar a CSV
    exportarTablaCSV("datos_ejemplo", x_original, y_original, n_original);
    printf("\n");

    // PARTE 2: Leer los datos desde CSV
    printf("2. Leyendo datos desde CSV...\n");
    double x_leido[100];
    double y_leido[100];
    
    int n_leido = leerTablaCSV("outputs/csv/datos_ejemplo.csv", x_leido, y_leido, 100);
    
    if (n_leido <= 0) {
        printf("Error al leer la tabla CSV\n");
        return 1;
    }

    printf("   Datos leídos:\n");
    printf("   i\tx\t\ty\n");
    for (int i = 0; i < n_leido; ++i) {
        printf("   %d\t%.6f\t\t%.8f\n", i, x_leido[i], y_leido[i]);
    }

    // PARTE 3: Verificar que los datos coincidan
    printf("\n3. Verificando integridad...\n");
    bool coinciden = true;
    const double tolerancia = 1e-10;
    
    if (n_leido != n_original) {
        printf("   ERROR: cantidad de puntos diferente (%d vs %d)\n", n_leido, n_original);
        coinciden = false;
    } else {
        for (int i = 0; i < n_original; ++i) {
            double diff_x = fabs(x_original[i] - x_leido[i]);
            double diff_y = fabs(y_original[i] - y_leido[i]);
            
            if (diff_x > tolerancia || diff_y > tolerancia) {
                printf("   ERROR en punto %d: x diferencia=%.2e, y diferencia=%.2e\n", 
                       i, diff_x, diff_y);
                coinciden = false;
            }
        }
    }

    if (coinciden) {
        printf("   ✓ ÉXITO: Todos los datos coinciden perfectamente\n");
    } else {
        printf("   ✗ FALLO: Hay discrepancias en los datos\n");
    }

    // Liberar memoria
    // (No es necesario porque están en el stack, no en heap)

    printf("\n=== TEST COMPLETADO ===\n");
    return coinciden ? 0 : 1;
}
