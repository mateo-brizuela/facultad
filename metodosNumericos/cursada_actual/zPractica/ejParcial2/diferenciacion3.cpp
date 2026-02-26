#include <stdio.h>
#include <cmath>
#include <stdlib.h>

// librerías propias (misma exportación que en la versión anterior)
#include "librerias/io/exportarResultados.h"

// constante usada para la opción original (se mantiene para compatibilidad)
#define SUB_INTERVALOS 10 // cantidad de subintervalos por defecto

// prototipos de funciones (originales)
double func(double x){
    return (x*x) + 1.0; // función de ejemplo (no se usa en la nueva opción tabla)
}
void diferenciacion_numerica(); // opción original: diferenciación numérica en tabla usando func(x)
void derivada_punto_interactiva(); // opción original: aproximar derivada en puntos individuales (x0, h) usando func(x)

// NUEVA: diferenciación desde tabla (x,y) equiespaciada, usando diferencias de orden mínimo
void diferenciacion_desde_tabla(); // opción nueva: el usuario ingresa una tabla de puntos (x_i, y_i) equiespaciada, se calcula la derivada usando diferencias finitas

int main(int argc, char const *argv[])
{
    int opcion = -1;
    printf("Bienvenido al programa para calcular la diferenciación numérica (v3)\n");
    do {
        printf("\nMenu opciones:\n");
        printf(" 1) Diferenciación en tabla (intervalo y %d subintervalos) [uso de func(x)]\n", SUB_INTERVALOS);
        printf(" 2) Aproximar derivada en puntos individuales (x0, h)\n");
        printf(" 3) Diferenciación desde tabla (x_i, y_i) equiespaciada (ingresadas por usuario)\n");
        printf(" 0) Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) { opcion = 0; }

        switch (opcion) {
            case 1: diferenciacion_numerica(); break;
            case 2: derivada_punto_interactiva(); break;
            case 3: diferenciacion_desde_tabla(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n"); break;
        }
    } while (opcion != 0);

    return 0;
}

/* ------------------ implementaciones existentes (sin cambios) ------------------ */

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
    fp[0] = (-3.0 * func(xi[0]) + 4.0 * func(xi[1]) - func(xi[2])) / (2.0 * h); // forward 3-point
    for (int i = 1; i < n; i++) {
        fp[i] = (func(xi[i] + h) - func(xi[i] - h)) / (2.0 * h); // central 2-point
    }
    fp[n] = (3.0 * func(xi[n]) - 4.0 * func(xi[n - 1]) + func(xi[n - 2])) / (2.0 * h); // backward 3-point

    // Imprimir resultados
    printf("Resultados de la diferenciación numérica (usando func):\n");
    for (int i = 0; i <= n; i++) {
        printf("f'(%.6f) = %.6f\n", xi[i], fp[i]);
    }

    // Exportar resultados a archivos (se guardan en ./outputs/)
    exportarTabla("resultados_diferenciacion", xi, fp, n + 1);
}

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

/* ------------------ NUEVA función: diferenciación desde tabla (x,y) ------------------ */

// se puede modificar para que haga foward/backward de 3 puntos en los extremos si se desea
void diferenciacion_desde_tabla() {
    int N = 0;
    printf("\nDiferenciacion desde tabla (x_i, y_i) equiespaciada\n");
    printf("Ingrese la cantidad de puntos (N >= 2): ");
    if (scanf("%d", &N) != 1 || N < 2) {
        printf("Numero de puntos invalido.\n");
        return;
    }

    double *x = new double[N];
    double *y = new double[N];
    double *fp = new double[N];

    // Leer pares (x_i, y_i)
    printf("Ingrese los pares x_i y_i (uno por linea):\n");
    for (int i = 0; i < N; ++i) {
        printf("x[%d]: ", i);
        if (scanf("%lf", &x[i]) != 1) { printf("Entrada invalida.\n"); delete[] x; delete[] y; delete[] fp; return; }
        printf("y[%d]: ", i);
        if (scanf("%lf", &y[i]) != 1) { printf("Entrada invalida.\n"); delete[] x; delete[] y; delete[] fp; return; }
    }

    // Validar equiespaciado: calcular h = x1 - x0 y comprobar tolerancia
    double h = x[1] - x[0];
    const double TOL = 1e-8;
    bool equi = true;
    for (int i = 2; i < N; ++i) {
        double hi = x[i] - x[i-1];
        if (fabs(hi - h) > TOL) { equi = false; break; }
    }
    if (!equi || h == 0.0) {
        printf("Error: los nodos x_i no son equiespaciados o h == 0. Abortando.\n");
        delete[] x; delete[] y; delete[] fp;
        return;
    }

    // Diferencias de orden mínimo:
    // forward (2-point) en i=0: (y1 - y0)/h
    fp[0] = (y[1] - y[0]) / h;

    // centradas 2-point en interiores: (y_{i+1} - y_{i-1})/(2h)
    for (int i = 1; i < N - 1; ++i) {
        fp[i] = (y[i+1] - y[i-1]) / (2.0 * h);
    }

    // backward (2-point) en i = N-1: (y_n - y_{n-1})/h
    fp[N-1] = (y[N-1] - y[N-2]) / h;

    // Imprimir resultados
    printf("\nResultados de la diferenciación desde tabla (orden mínimo, paso h = %.12g):\n", h);
    for (int i = 0; i < N; ++i) {
        printf("f'(%.12g) ≈ %.12g\n", x[i], fp[i]);
    }

    // Exportar resultados (mismo formato que la versión original)
    exportarTabla("resultados_diferenciacion_tabla", x, fp, N);

    delete[] x; delete[] y; delete[] fp;
}