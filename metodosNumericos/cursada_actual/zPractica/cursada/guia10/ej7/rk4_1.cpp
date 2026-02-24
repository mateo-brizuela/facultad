#include <stdio.h>
#include <cmath>

#include "../../../librerias/io/exportarResultados.h"

// y' = f(x,y)
double f(double x, double y) {
    //return 2*x; // ejemplo
    return (3.0*y) - 4.0*exp(-x);
}

void rk4();

int main() {
    rk4();
    return 0;
}

void rk4() {
    // Entradas
    double a = 0.0, b = 0.0;
    double x0 = 0.0, y0 = 1.0;
    int modo = 1; // 1: definir N; 2: definir h
    const double eps = 1e-12;

    printf("Metodo de rk4 para EDO y' = f(x,y)\n");
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

    printf("\nElija modo de discretizacion:\n");
    printf(" 1) Definir cantidad de subintervalos N\n");
    printf(" 2) Definir distancia de paso h (sin ajustar a b)\n");
    printf("Opcion: ");
    if (scanf("%d", &modo) != 1) modo = 1;

    int N = 0;       // subintervalos
    double h = 0.0;  // paso
    int P = 0;       // puntos

    if (modo == 2) {
        // Usuario define h, no se ajusta para “encajar” en [a,b]
        double h_user = 0.0;
        do {
            printf("Ingrese h (0 < h <= b-a): ");
            scanf("%lf", &h_user);
            if (h_user <= 0.0 || h_user > (b - a)) {
                printf("h debe ser > 0 y <= (b-a) = %.12f\n", (b - a));
            }
        } while (h_user <= 0.0 || h_user > (b - a));

        h = h_user;

        // contar cuántos puntos entran empezando en a con paso h, sin pasar b
        double xtmp = a;
        while (xtmp <= b + eps) {
            ++P;
            xtmp += h;
        }
        N = P - 1; // subintervalos efectivos
    } else {
        // Usuario define N, como en el programa original
        do {
            printf("Ingrese N (subintervalos, N >= 1): ");
            scanf("%d", &N);
            if (N < 1) printf("N debe ser >= 1.\n");
        } while (N < 1);
        h = (b - a) / (double)N;
        P = N + 1;
    }

    // Alinear x0 con a (rk4 explícito desde el extremo izquierdo)
    if (fabs(x0 - a) > eps) {
        printf("Aviso: x0 != a (%.6f != %.6f). Se ajusta x0 = a.\n", x0, a);
        x0 = a;
    }

    // Arreglos dinámicos
    double* x = new double[P];
    double* y = new double[P];

    // Mallado y rk4 explícito
    x[0] = x0;   // = a
    y[0] = y0;

    // definicion de k1 a k4
    double k1, k2, k3, k4;
    for (int i = 1; i < P; ++i) {
        
        k1 =f(x[i - 1], y[i - 1]);
        k2 =f(x[i - 1] + h / 2.0, y[i - 1] + (k1 / 2.0)*h);
        k3 =f(x[i - 1] + h / 2.0, y[i - 1] + (k2 / 2.0)*h);
        k4 =f(x[i - 1] + h, y[i - 1] + k3*h);

        x[i] = x[i - 1] + h;
        y[i] = y[i - 1] + (h / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
    }

    // Si el modo es por N, garantizamos que el último punto sea exactamente b (como en el original)
    if (modo == 1) x[P - 1] = b;

    // Resultados
    printf("\nResultados de la aproximacion por el metodo de RK4:\n");
    printf("Modo = %s | N = %d | P = %d | h = %.12f\n",
           (modo == 2 ? "por h (sin ajustar a b, se corta al superar b)" : "por N"),
           N, P, h);
    printf("i\t        x_i\t\t        y_i\n");
    for (int i = 0; i < P; ++i) {
        printf("%d\t%14.8f\t%14.8f\n", i, x[i], y[i]);
    }

    // Exportar (./outputs/)
    exportarDerivadas("rk4_resultados", x, y, P);

    delete[] x;
    delete[] y;
}