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

int main(int argc, char const *argv[])
{
    printf("Bienvenido al programa para calcular la diferenciación numérica\n");
    diferenciacion_numerica();
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

    xi[0] = a;        // extremo izquierdo
    xi[n] = b;        // extremo derecho

    fp[0] = (func(a + h) - func(a)) / h; // derivada en a
    fp[n] = (func(b) - func(b - h)) / h; // derivada en b

    for (int i = 1; i < n; i++) {
        xi[i] = a + i * h;
        fp[i] = (func(xi[i] + h) - func(xi[i] - h)) / (2 * h);
    }

    // Imprimir resultados
    printf("Resultados de la diferenciación numérica:\n");
    for (int i = 0; i <= n; i++) {
        printf("f'(%lf) = %lf\n", xi[i], fp[i]);
    }

    // Exportar resultados a archivos
    exportarTabla("resultados_diferenciacion", xi, fp, n + 1);

}
