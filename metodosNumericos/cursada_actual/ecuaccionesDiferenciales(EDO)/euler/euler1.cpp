#include <stdio.h>
#include <cmath>

// definicion de constantes
#define INTERVALOS 100           // Numero de subintervalos (constante)
#define PUNTOS (INTERVALOS + 1)  // Numero de puntos a calcular (constante)

#include "../../librerias/io/exportarResultados.h"

// Definición de la función f(x,y) = dy/dx
double f(double x, double y) {
    //return 2*x; // Ejemplo: dy/dx = x + y
    return -((2*x) + 1.0)*sqrt(y);
}

// prototipo de funciones 
void euler();

int main(int argc, char const *argv[])
{
    euler();
    return 0;
}

void euler(){
    double a = 0.0, b = 0.0;  // intervalo
    double x0 = 0.0;          // Valor inicial de x (debe coincidir con a)
    double y0 = 1.0;          // Valor inicial de y
    double x[PUNTOS], y[PUNTOS]; // Arreglos estáticos
    double h = 0.0;           // Tamaño del paso

    // Entrada de datos
    printf("Metodo de Euler para EDO y' = f(x,y)\n");
    printf("Ingrese extremos del intervalo [a, b]\n");
    printf("a: "); scanf("%lf", &a);
    printf("b: "); scanf("%lf", &b);
    while (b <= a) {
        printf("b debe ser mayor que a. Reingrese b: ");
        scanf("%lf", &b);
    }

    printf("Condicion inicial y(x0) = y0\n");
    printf("x0 (idealmente x0 = a): "); scanf("%lf", &x0);
    printf("y0: "); scanf("%lf", &y0);

    // Paso según el intervalo y la cantidad fija de subintervalos
    h = (b - a) / (double)INTERVALOS;

    // Alinear x0 con a para que el mallado cubra exactamente [a,b]
    if (fabs(x0 - a) > 1e-12) {
        printf("Aviso: x0 != a (%.6f != %.6f). Se ajusta x0 = a.\n", x0, a);
        x0 = a;
    }

    // Mallado y condición inicial
    x[0] = x0;   // = a
    y[0] = y0;
    for (int i = 1; i < PUNTOS; i++) {
        x[i] = a + i * h;
        y[i] = y[i - 1] + h * f(x[i - 1], y[i - 1]); // Euler explícito
    }
    x[PUNTOS - 1] = b; // asegurar extremo derecho exacto

    // Resultados
    printf("\nResultados de la aproximacion por el metodo de Euler:\n");
    printf("INTERVALOS = %d, PUNTOS = %d, h = %.12f\n", INTERVALOS, PUNTOS, h);
    printf("i\t        x_i\t\t        y_i\n");
    for (int i = 0; i < PUNTOS; i++) {
        printf("%d\t%14.8f\t%14.8f\n", i, x[i], y[i]);
    }

    // Exportar resultados (se guardan en ./outputs/)
    exportarTabla("euler_resultados", x, y, PUNTOS);
}


