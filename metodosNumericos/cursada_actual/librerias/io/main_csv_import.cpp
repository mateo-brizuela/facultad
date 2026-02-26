#include <stdio.h>
#include <cmath>
#include "exportarResultados.h"

/*
   Ejemplo práctico: 
   - main_csv_export.cpp: genera datos y los exporta a CSV
   - main_csv_import.cpp: lee esos datos y hace algo con ellos
*/

int main() {
    printf("=== PROGRAMA B: IMPORTA DATOS Y LOS PROCESA ===\n\n");

    // Leer datos previamente exportados por otro programa
    printf("Leyendo datos del programa anterior...\n");
    double x[100];
    double y[100];
    
    int n = leerTablaCSV("outputs/csv/datos_ejemplo.csv", x, y, 100);
    
    if (n <= 0) {
        printf("Error: no se pudieron leer los datos\n");
        return 1;
    }

    printf("Datos leídos exitosamente: %d puntos\n\n", n);

    // Procesamiento ejemplo 1: Calcular estadísticas
    printf("--- Estadísticas de los datos ---\n");
    double suma_x = 0, suma_y = 0;
    double min_x = x[0], max_x = x[0];
    double min_y = y[0], max_y = y[0];

    for (int i = 0; i < n; ++i) {
        suma_x += x[i];
        suma_y += y[i];
        if (x[i] < min_x) min_x = x[i];
        if (x[i] > max_x) max_x = x[i];
        if (y[i] < min_y) min_y = y[i];
        if (y[i] > max_y) max_y = y[i];
    }

    printf("X - Media: %.6f, Rango: [%.6f, %.6f]\n", suma_x/n, min_x, max_x);
    printf("Y - Media: %.6f, Rango: [%.6f, %.6f]\n", suma_y/n, min_y, max_y);

    // Procesamiento ejemplo 2: Calcular integral numérica (trapecios)
    printf("\n--- Integral numérica (método trapecio) ---\n");
    double integral = 0.0;
    for (int i = 0; i < n-1; ++i) {
        double h = x[i+1] - x[i];
        integral += h * (y[i] + y[i+1]) / 2.0;
    }
    printf("Integral aproximada: %.8f\n", integral);

    // Procesamiento ejemplo 3: Derivada numérica
    printf("\n--- Derivada numérica (diferencia central) ---\n");
    printf("Derivadas en puntos intermedios:\n");
    printf("x\t\t\t dy/dx\n");
    for (int i = 1; i < n-1; ++i) {
        double h = x[i+1] - x[i];
        double derivada = (y[i+1] - y[i-1]) / (2*h);
        printf("%.6f\t\t%.8f\n", x[i], derivada);
    }

    // Exportar los resultados procesados
    printf("\n--- Exportando resultados a nuevo CSV ---\n");
    double y_procesado[10];
    for (int i = 0; i < n; ++i) {
        // Por ejemplo: escalar los valores
        y_procesado[i] = y[i] * 2.0;
    }
    exportarTablaCSV("datos_procesados", x, y_procesado, n);

    // Liberar memoria
    // (No es necesario porque están en el stack, no en heap)

    printf("\n=== PROGRAMA B COMPLETADO ===\n");
    return 0;
}
