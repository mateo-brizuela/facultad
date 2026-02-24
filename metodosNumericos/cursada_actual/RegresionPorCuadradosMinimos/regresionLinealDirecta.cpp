// regresion_lineal_directa.cpp
// Ajuste por minimos cuadrados: y = a*x + b
// Calcula a y b directamente con sumatorias (sin Gauss)

#include <stdio.h>
#include <math.h>

int main() {
    int n;
    printf("REGRESION LINEAL (forma directa por sumatorias)\n");
    printf("Modelo: y = a*x + b\n\n");

    printf("Ingrese cantidad de puntos n: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Error: se necesitan al menos 2 puntos.\n");
        return 1;
    }

    // Variables para acumular las sumatorias necesarias
    double Sx = 0.0, Sy = 0.0, Sxx = 0.0, Sxy = 0.0;

    // Lectura de puntos (x, y)
    for (int i = 0; i < n; i++) {
        double x, y;
        printf("Punto %d:\n", i + 1);
        printf("  Ingrese x[%d]: ", i + 1);
        scanf("%lf", &x);
        printf("  Ingrese y[%d]: ", i + 1);
        scanf("%lf", &y);

        // Acumular sumatorias: sum(x), sum(y), sum(x^2), sum(xy)
        Sx  += x;
        Sy  += y;
        Sxx += x * x;
        Sxy += x * y;
    }

    // Verificar que el denominador no sea ~0 (evita división por cero)
    // Si lo es, significa que todos los valores x son iguales
    double denom = (double)n * Sxx - (Sx * Sx);
    if (fabs(denom) < 1e-12) {
        printf("Error: denominador ~ 0 (probablemente todos los x son iguales).\n");
        return 1;
    }

    // Fórmulas para calcular los coeficientes por mínimos cuadrados
    // a = (n*sum(xy) - sum(x)*sum(y)) / (n*sum(x^2) - (sum(x))^2)
    // b = (sum(y) - a*sum(x)) / n
    double a = ((double)n * Sxy - Sx * Sy) / denom;
    double b = (Sy - a * Sx) / (double)n;

    printf("\n=== SUMATORIAS ===\n");
    printf("sum(x)   = %.10f\n", Sx);
    printf("sum(y)   = %.10f\n", Sy);
    printf("sum(x^2) = %.10f\n", Sxx);
    printf("sum(xy)  = %.10f\n", Sxy);

    printf("\n=== RESULTADO ===\n");
    printf("a (pendiente)   = %.10f\n", a);
    printf("b (ordenada)    = %.10f\n", b);
    printf("Recta ajustada: y = %.10f * x + %.10f\n", a, b);

    return 0;
}
