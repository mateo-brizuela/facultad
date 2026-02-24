#include <stdio.h>
#include <cmath>

#define D 5 // cantidad fija de puntos que se cargan en la tabla
#define MAX_PUNTOS_PROGRAMA D // la librería usa este valor

#include "../../librerias/splineCubica/spline_cubica.h"

// función de ejemplo para la opción con función
double func(double x){
    return (x*x) + 1.0;
}

void trapecioFunc(double &res);
void trapecioTabla(double &res, double x[D], double y[D]); // versión v3 con detección de equiespaciado
void cargarVector(double x[D], double y[D]);
void mostrarTabla(double x[D], double y[D]);

int main(int argc, char const *argv[])
{
    double res = 0.0, x[D], y[D];
    int opcion;
    printf("Bienvenido al programa para calcular integrales (trapecio compuesto) - v3\n");
    printf("¿Cómo desea calcular la integral?\n");
    printf("1) Usar función matemática\n");
    printf("2) Ingresar tabla de datos\n");
    printf("Opción: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        trapecioFunc(res);
    } else if (opcion == 2) {
        cargarVector(x, y);
        mostrarTabla(x, y);
        trapecioTabla(res, x, y); 
    } else {
        printf("Opción no válida.\n");
    }

    return 0;
}

void trapecioFunc(double &res){
    double a = 0.0, b = 0.0, h = 0.0, n = 0.0, sum = 0.0;
    printf("Ingrese el limite inferior de la integral: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior de la integral: ");
    scanf("%lf", &b);
    printf("Ingrese la cantidad de subintervalos (n): ");
    scanf("%lf", &n);
    h = (b - a) / n;
    sum = func(a) + func(b);
    for (int i = 1; i < (int)n; i++) {
        sum += 2 * func(a + i*h);
    }
    res = (h / 2) * sum;

    printf("El resultado de la integral(dec): %.6lf\n", res);
    printf("El resultado de la integral(cient): %.6e\n", res);
}

// Devuelve true si el vector x[] es equiespaciado (tolerancia), false si no lo es
bool esEquiespaciada(double x[D]) {
    double h = x[1] - x[0];
    const double EPS = 1e-8; // tolerancia para errores de redondeo
    if (fabs(h) < EPS) return false;
    for (int i = 2; i < D; i++) {
        if (fabs((x[i] - x[i-1]) - h) > EPS) {
            return false;
        }
    }
    return true;
}

/*
  trapecioTabla v3:
  - Si la tabla original es equiespaciada ofrece usar directamente esa tabla
    (no pide subintervalos) o bien generar una tabla nueva por interpolación.
  - Si la tabla NO es equiespaciada obliga a interpolar a 'n' subintervalos
    (se le solicita al usuario).
*/
void trapecioTabla(double &res, double x[D], double y[D]) {
    // comprobar si la tabla original es equiespaciada
    bool equi = esEquiespaciada(x);

    if (equi) {
        printf("\nLa tabla proporcionada es equiespaciada.\n");
        printf("Opciones:\n");
        printf(" 1) Usar directamente la tabla original para integrar (no pedir subintervalos).\n");
        printf(" 2) Generar por interpolacion una nueva tabla con n subintervalos (pedir n).\n");
        printf("Seleccione opcion (1 o 2): ");
        int opt = 0;
        if (scanf("%d", &opt) != 1) { printf("Entrada invalida.\n"); return; }

        if (opt == 1) {
            // usar la tabla tal cual: hay D puntos => Nsub = D-1 subintervalos y paso h = x[1]-x[0]
            int Nsub = D - 1;
            double h = x[1] - x[0];
            double sum = y[0] + y[Nsub];
            for (int i = 1; i < Nsub; ++i) sum += 2.0 * y[i];
            res = (h / 2.0) * sum;
            printf("Resultado usando tabla original (h = %.12g, subintervalos = %d): %.6lf\n", h, Nsub, res);
            return;
        }
        // si opt == 2 caemos a la sección de interpolación pidiendo n más abajo
    } else {
        printf("\nLa tabla NO es equiespaciada -> se debe interpolar a una malla equiespaciada.\n");
    }

    // petición de subintervalos cuando se necesita/interpone
    int n;
    printf("Ingrese la cantidad de subintervalos que desea (n > 0): ");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("Numero de subintervalos invalido.\n"); return; }

    double a = x[0]; // primer punto de la tabla original
    double b = x[D-1]; // último punto de la tabla original
    if (b <= a) { printf("Error: rango inválido.\n"); return; }

    double h = (b - a) / n; // paso para la nueva tabla equiespaciada
    double matriz_coeficientes[MAX_SEGMENTOS][4]; // para almacenar coeficientes del spline (D puntos => D-1 segmentos)

    // puntos equiespaciados nuevos
    double *x_new = new double[n+1]; // n subintervalos => n+1 puntos, desde a hasta b con paso h
    double *y_new = new double[n+1]; // valores del spline evaluados en x_new (se llenan por interpolación o se copian de y[] si coinciden con x[])
    for (int i = 0; i <= n; i++) x_new[i] = a + i * h;

    // si el usuario pidió exactamente D puntos y los x_new coinciden con x[] (por si eligió opt==2)
    const double EPS = 1e-8;
    bool coincide = false;
    if (n + 1 == D) {
        coincide = true;
        for (int i = 0; i < D; ++i) {
            if (fabs(x_new[i] - x[i]) > EPS) { coincide = false; break; }
        }
    }
    if (coincide) {
        // copiar y tal cual (evita llamar al spline innecesariamente)
        for (int i = 0; i <= n; ++i) y_new[i] = y[i];
    } else {
        // calcular coeficientes del spline con la tabla original y evaluar en x_new
        int resultado = spline_calcular_coeficientes(x, y, D, matriz_coeficientes);
        if (resultado == -1) {
            printf("ERROR: fallo al calcular coeficientes del spline.\n");
            delete[] x_new; delete[] y_new;
            return;
        }
        resultado = spline_evaluar_multiples_puntos(x, D, matriz_coeficientes, x_new, n+1, y_new);
        if (resultado != 0) {
            printf("ERROR: fallo al evaluar spline en puntos nuevos.\n");
            delete[] x_new; delete[] y_new;
            return;
        }
    }

    // aplicar regla del trapecio compuesto sobre x_new,y_new
    double sum = y_new[0] + y_new[n];
    for (int i = 1; i < n; i++) sum += 2.0 * y_new[i];
    res = (h / 2.0) * sum;

    printf("El resultado de la integral (por tabla/interpolacion): %.6lf\n", res);

    delete[] x_new; delete[] y_new;
}

void cargarVector(double x[D], double y[D]) {
    printf("Cargando %d puntos (x_i, y_i):\n", D);
    for (int i = 0; i < D; i++) {
        printf("Ingrese x[%d]: ", i);
        scanf("%lf", &x[i]);
        printf("Ingrese y[%d]: ", i);
        scanf("%lf", &y[i]);
    }
}

void mostrarTabla(double x[D], double y[D]) {
    printf("\n=== TABLA DE DATOS ===\n");
    printf("Indice\tx\t\ty\n");
    for (int i = 0; i < D; i++) {
        printf("%d\t%.6f\t%.6f\n", i, x[i], y[i]);
    }
}