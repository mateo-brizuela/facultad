#include <stdio.h>
#include <cmath>

#define SUB_INTERVALOS 10 // cantidad de subintervalos para la diferenciacion numerica

//librerias propias
#include "../librerias/io/exportarResultados.h"

// prototipo de funciones
double func(double x){
    return pow(1.0 + x*x, 0.5);
}

void diferenciacion_numerica();

// NUEVO: calcular derivada en un punto (interactivo, repite hasta que el usuario decida salir)
void derivada_punto_interactiva();

int main(int argc, char const *argv[])
{
    int opcion = -1;
    printf("Bienvenido al programa para calcular la diferenciación numérica\n");
    do {
        printf("\nMenu opciones:\n");
        printf(" 1) Diferenciación en tabla (intervalo y %d subintervalos)\n", SUB_INTERVALOS);
        printf(" 2) Aproximar derivada en puntos individuales (x0, h)\n");
        printf(" 0) Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) { opcion = 0; }

        switch (opcion) {
            case 1: diferenciacion_numerica(); break;
            case 2: derivada_punto_interactiva(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n"); break;
        }
    } while (opcion != 0);

    return 0;
}

void diferenciacion_numerica(){
    double a = 0.0, b = 0.0, h = 0.0;
    double fp[SUB_INTERVALOS + 1] = {0.0}; // vector para almacenar las derivadas
    double xi[SUB_INTERVALOS + 1] = {0.0}; // vector para almacenar los puntos xi
    int n = SUB_INTERVALOS; // cantidad de subintervalos

    printf("constante definida de subintervalos: %d\n", n);
    printf("ingrese los extremos del intervalo [a, b]:\n");
    printf("a: ");
    scanf("%lf", &a);
    printf("b: ");
    scanf("%lf", &b);
    h = (b - a) / n; // tamaño del paso

    // puntos del mallado (N subintervalos => N+1 puntos)
    xi[0] = a;        // extremo izquierdo
    for (int i = 1; i < n; i++) {
        xi[i] = a + i * h;
    }
    xi[n] = b;        // asegurar el extremo derecho exacto

    // derivadas: forward en a, central en interiores, backward en b
    fp[0] = (-3.0 * func(xi[0]) + 4.0 * func(xi[1]) - func(xi[2])) / (2.0 * h);
    for (int i = 1; i < n; i++) {
        fp[i] = (func(xi[i] + h) - func(xi[i] - h)) / (2.0 * h);
    }
    fp[n] = (3.0 * func(xi[n]) - 4.0 * func(xi[n - 1]) + func(xi[n - 2])) / (2.0 * h);

    // Imprimir resultados
    printf("Resultados de la diferenciación numérica:\n");
    for (int i = 0; i <= n; i++) {
        printf("f'(%.6f) = %.6f\n", xi[i], fp[i]);
    }

    // Exportar resultados a archivos (se guardan en ./outputs/)
    exportarTabla("resultados_diferenciacion", xi, fp, n + 1);
}

// NUEVO: modo interactivo para derivada en un punto
void derivada_punto_interactiva() {
    char seguir = 's';
    while (seguir == 's' || seguir == 'S') {
        double x0 = 0.0, h = 0.0;

        printf("\nAproximar derivada en un punto (esquema central):\n");
        printf("Ingrese x0: ");
        scanf("%lf", &x0);

        do {
            printf("Ingrese h (> 0): ");
            scanf("%lf", &h);
            if (h <= 0.0) printf("h debe ser mayor que 0.\n");
        } while (h <= 0.0);

        // derivada central: f'(x0) ≈ (f(x0+h) - f(x0-h)) / (2h)
        double deriv = (func(x0 + h) - func(x0 - h)) / (2.0 * h);

        printf("f'(%.6f) ≈ %.12f\n", x0, deriv);
        printf("f'(%.6f) ≈ %.6e (notacion cientifica)\n", x0, deriv);

        printf("¿Desea aproximar otra derivada? (s/n): ");
        scanf(" %c", &seguir); // espacio inicial para consumir saltos de línea
    }
}
