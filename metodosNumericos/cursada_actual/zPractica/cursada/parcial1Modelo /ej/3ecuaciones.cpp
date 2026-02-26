#include <stdio.h>
#include <cmath>

// librerias propias (misma exportación que en los ejemplos)
#include "./libreria/io/exportarResultados.h"

/*
  Programa: 3ecuaciones
  Objetivo: integrar un sistema acoplado de 3 EDOs de primer orden usando
            Euler explicito, RK4 y Heun (predictor-corrector).
  Notas:
   - Reemplazar f1,f2,f3 por el sistema que necesites.
   - El programa acepta dos modos de mallado:
       modo = 1: el usuario indica N (cantidad de subintervalos) -> h = (b-a)/N
       modo = 2: el usuario indica h (paso) -> se calcula P = numero de puntos
   - Exporta resultados con exportarTabla(nombre, x, y, P).
*/

/* -----------------------
   Definición del sistema
   -----------------------
   y1' = f1(x,y1,y2,y3)
   y2' = f2(x,y1,y2,y3)
   y3' = f3(x,y1,y2,y3)
   Reemplazá las expresiones por las de tu modelo.
*/
double f1(double x, double y1, double y2, double y3) {
    return y2;
}
double f2(double x, double y1, double y2, double y3) {
    return y3;
}
double f3(double x, double y1, double y2, double y3) {
    return 4.0*y3 - 24.0*y1 +24.0*x*x - 16;
}

/* Prototipos de los métodos implementados:
   - los parámetros comunes:
       modo: 1 -> entrada por N ; 2 -> entrada por h
       N   : número de subintervalos (si modo==1)
       h   : paso (si modo==2 se usa h como entrada)
       a,b : intervalo [a,b]
       x0  : punto inicial (idealmente = a)
       y10,y20,y30 : condiciones iniciales en x0
*/
void euler3(int modo, int N, double h, double a, double b, double x0,
            double y10, double y20, double y30);
void rk4_3(int modo, int N, double h, double a, double b, double x0,
           double y10, double y20, double y30);
void heun3(int modo, int N, double h, double a, double b, double x0,
           double y10, double y20, double y30);

/*
  Calcular mallado:
    - Si modo==2 (por h): cuenta cuántos puntos caben en [a,b] con paso h (incluye extremos)
    - Si modo==1 (por N): calcula h = (b-a)/N y P = N+1
  Salidas:
    N_out : número de subintervalos efectivo
    h_out : paso usado
    P_out : número de puntos en la malla (N_out + 1)
*/
static void calcularMallado(int modo, int N_in, double h_in, double a, double b,
                            int *N_out, double *h_out, int *P_out) {
    const double eps = 1e-12;
    int N = N_in;
    double h = h_in;
    int P = 0;
    if (modo == 2) { // por h
        if (h <= 0.0) h = b - a;
        double xt = a;
        while (xt <= b + eps) { ++P; xt += h; }
        if (P < 1) P = 1;
        N = P - 1;
    } else {         // por N
        if (N <= 0) N = 1;
        h = (b - a) / (double)N;
        P = N + 1;
    }
    *N_out = N; *h_out = h; *P_out = P;
}

int main() {
    double a = 0.0, b = 0.0;
    double x0 = 0.0;
    /* Condiciones iniciales: modificá si hace falta */
    double y10 = 1.0, y20 = 0.0, y30 = 0.0;
    int modo = 1, N = 0;
    double h = 0.0;

    printf("Sistema de EDO de primer orden (3 ecuaciones)\n");
    printf("Ingrese extremos [a,b]\n");
    printf("a: "); scanf("%lf", &a);
    printf("b: "); scanf("%lf", &b);
    while (b <= a) { printf("b > a requerido. Reingrese b: "); scanf("%lf", &b); }

    printf("x0 (ideal x0=a): "); scanf("%lf", &x0);
    printf("y1(x0): "); scanf("%lf", &y10);
    printf("y2(x0): "); scanf("%lf", &y20);
    printf("y3(x0): "); scanf("%lf", &y30);

    printf("Modo discretizacion (1=N, 2=h): ");
    if (scanf("%d", &modo) != 1) modo = 1;

    if (modo == 1) {
        do {
            printf("N (>=1): ");
            scanf("%d", &N);
            if (N < 1) printf("N debe ser >=1\n");
        } while (N < 1);
        h = (b - a) / (double)N;
    } else {
        do {
            printf("h (0 < h <= b-a): ");
            scanf("%lf", &h);
            if (h <= 0.0 || h > (b - a))
                printf("h invalido. b-a = %.6f\n", b - a);
        } while (h <= 0.0 || h > (b - a));
        N = 0; // se calculará en calcularMallado
    }

    printf("\nEjecutando métodos...\n");
    euler3(modo, N, h, a, b, x0, y10, y20, y30);
    rk4_3 (modo, N, h, a, b, x0, y10, y20, y30);
    heun3(modo, N, h, a, b, x0, y10, y20, y30);
    return 0;
}

/* ---------------------------
   Implementaciones de métodos
   ---------------------------
   Comentarios generales:
    - Cada método construye arrays x[], y1[], y2[], y3[] de longitud P (nº de puntos)
    - Se asume que x0 ≈ a; si no, se ajusta y se notifica.
    - Al finalizar se imprimen resultados y se exportan con exportarTabla.
*/

/* Euler explícito para el sistema de 3 ecuaciones */
void euler3(int modo, int N, double h, double a, double b, double x0,
            double y10, double y20, double y30) {
    const double eps = 1e-12;
    int P;
    calcularMallado(modo, N, h, a, b, &N, &h, &P);

    if (fabs(x0 - a) > eps) { printf("[Euler3] x0!=a -> ajustado\n"); x0 = a; }

    double *x = new double[P];
    double *y1 = new double[P];
    double *y2 = new double[P];
    double *y3 = new double[P];

    x[0]=x0; y1[0]=y10; y2[0]=y20; y3[0]=y30;

    for (int i=1; i<P; ++i) {
        double xn = x[i-1];
        double y1n = y1[i-1];
        double y2n = y2[i-1];
        double y3n = y3[i-1];

        x[i] = xn + h;
        /* Euler: y_{n+1} = y_n + h * f(x_n, y_n) */
        y1[i] = y1n + h * f1(xn, y1n, y2n, y3n);
        y2[i] = y2n + h * f2(xn, y1n, y2n, y3n);
        y3[i] = y3n + h * f3(xn, y1n, y2n, y3n);
    }
    if (modo==1) x[P-1]=b;

    printf("[Euler3] modo=%d N=%d P=%d h=%.6f\n", modo, N, P, h);
    printf("i\t x\t\t y1\t\t y2\t\t y3\n");
    for (int i=0;i<P;++i)
        printf("%d\t%.8f\t%.8f\t%.8f\t%.8f\n", i, x[i], y1[i], y2[i], y3[i]);

    exportarTabla("euler3_y1", x, y1, P);
    exportarTabla("euler3_y2", x, y2, P);
    exportarTabla("euler3_y3", x, y3, P);

    delete[] x; delete[] y1; delete[] y2; delete[] y3;
}

/* RK4 (Runge-Kutta clásico de orden 4) para el sistema */
void rk4_3(int modo, int N, double h, double a, double b, double x0,
           double y10, double y20, double y30) {
    const double eps = 1e-12;
    int P;
    calcularMallado(modo, N, h, a, b, &N, &h, &P);

    if (fabs(x0 - a) > eps) { printf("[RK4_3] x0!=a -> ajustado\n"); x0 = a; }

    double *x = new double[P];
    double *y1 = new double[P];
    double *y2 = new double[P];
    double *y3 = new double[P];

    x[0]=x0; y1[0]=y10; y2[0]=y20; y3[0]=y30;

    for (int i=1; i<P; ++i) {
        double xn  = x[i-1];
        double y1n = y1[i-1];
        double y2n = y2[i-1];
        double y3n = y3[i-1];

        x[i] = xn + h;

        // k1
        double k1_1 = f1(xn, y1n, y2n, y3n);
        double k1_2 = f2(xn, y1n, y2n, y3n);
        double k1_3 = f3(xn, y1n, y2n, y3n);

        // k2
        double k2_1 = f1(xn + h/2.0,
                         y1n + (h/2.0)*k1_1,
                         y2n + (h/2.0)*k1_2,
                         y3n + (h/2.0)*k1_3);
        double k2_2 = f2(xn + h/2.0,
                         y1n + (h/2.0)*k1_1,
                         y2n + (h/2.0)*k1_2,
                         y3n + (h/2.0)*k1_3);
        double k2_3 = f3(xn + h/2.0,
                         y1n + (h/2.0)*k1_1,
                         y2n + (h/2.0)*k1_2,
                         y3n + (h/2.0)*k1_3);

        // k3
        double k3_1 = f1(xn + h/2.0,
                         y1n + (h/2.0)*k2_1,
                         y2n + (h/2.0)*k2_2,
                         y3n + (h/2.0)*k2_3);
        double k3_2 = f2(xn + h/2.0,
                         y1n + (h/2.0)*k2_1,
                         y2n + (h/2.0)*k2_2,
                         y3n + (h/2.0)*k2_3);
        double k3_3 = f3(xn + h/2.0,
                         y1n + (h/2.0)*k2_1,
                         y2n + (h/2.0)*k2_2,
                         y3n + (h/2.0)*k2_3);

        // k4
        double k4_1 = f1(xn + h,
                         y1n + h*k3_1,
                         y2n + h*k3_2,
                         y3n + h*k3_3);
        double k4_2 = f2(xn + h,
                         y1n + h*k3_1,
                         y2n + h*k3_2,
                         y3n + h*k3_3);
        double k4_3 = f3(xn + h,
                         y1n + h*k3_1,
                         y2n + h*k3_2,
                         y3n + h*k3_3);

        y1[i] = y1n + (h/6.0) * (k1_1 + 2*k2_1 + 2*k3_1 + k4_1);
        y2[i] = y2n + (h/6.0) * (k1_2 + 2*k2_2 + 2*k3_2 + k4_2);
        y3[i] = y3n + (h/6.0) * (k1_3 + 2*k2_3 + 2*k3_3 + k4_3);
    }
    if (modo==1) x[P-1]=b;

    printf("[RK4_3] modo=%d N=%d P=%d h=%.6f\n", modo, N, P, h);
    printf("i\t x\t\t y1\t\t y2\t\t y3\n");
    for (int i=0;i<P;++i)
        printf("%d\t%.8f\t%.8f\t%.8f\t%.8f\n", i, x[i], y1[i], y2[i], y3[i]);

    exportarTabla("rk4_3_y1", x, y1, P);
    exportarTabla("rk4_3_y2", x, y2, P);
    exportarTabla("rk4_3_y3", x, y3, P);

    delete[] x; delete[] y1; delete[] y2; delete[] y3;
}

/* Heun (predictor-corrector, también llamado RK2 mejorado) */
void heun3(int modo, int N, double h, double a, double b, double x0,
           double y10, double y20, double y30) {
    const double eps = 1e-12;
    int P;
    calcularMallado(modo, N, h, a, b, &N, &h, &P);

    if (fabs(x0 - a) > eps) { printf("[Heun3] x0!=a -> ajustado\n"); x0 = a; }

    double *x = new double[P];
    double *y1 = new double[P];
    double *y2 = new double[P];
    double *y3 = new double[P];

    x[0]=x0; y1[0]=y10; y2[0]=y20; y3[0]=y30;

    for (int i=1; i<P; ++i) {
        double xn  = x[i-1];
        double y1n = y1[i-1];
        double y2n = y2[i-1];
        double y3n = y3[i-1];

        x[i] = xn + h;

        // Predictor (Euler)
        double y1_tilde = y1n + h * f1(xn, y1n, y2n, y3n);
        double y2_tilde = y2n + h * f2(xn, y1n, y2n, y3n);
        double y3_tilde = y3n + h * f3(xn, y1n, y2n, y3n);

        // Corrector (promedio de pendientes: trapezoidal)
        y1[i] = y1n + 0.5*h * ( f1(xn, y1n, y2n, y3n) + f1(x[i], y1_tilde, y2_tilde, y3_tilde) );
        y2[i] = y2n + 0.5*h * ( f2(xn, y1n, y2n, y3n) + f2(x[i], y1_tilde, y2_tilde, y3_tilde) );
        y3[i] = y3n + 0.5*h * ( f3(xn, y1n, y2n, y3n) + f3(x[i], y1_tilde, y2_tilde, y3_tilde) );
    }
    if (modo==1) x[P-1]=b;

    printf("[Heun3] modo=%d N=%d P=%d h=%.6f\n", modo, N, P, h);
    printf("i\t x\t\t y1\t\t y2\t\t y3\n");
    for (int i=0;i<P;++i)
        printf("%d\t%.8f\t%.8f\t%.8f\t%.8f\n", i, x[i], y1[i], y2[i], y3[i]);

    exportarTabla("heun3_y1", x, y1, P);
    exportarTabla("heun3_y2", x, y2, P);
    exportarTabla("heun3_y3", x, y3, P);

    delete[] x; delete[] y1; delete[] y2; delete[] y3;
}

/* -----------------------------------------------------------------------
   Cómo usar este programa para EDOs de orden superior a 1 (comentario breve)
   -----------------------------------------------------------------------
   Un EDO de orden m > 1 se puede reducir a un sistema de m EDOs de primer
   orden definiendo variables intermedias:
     Sea y^(m) = F(x, y, y', ..., y^{(m-1)}).
   Definir:
     u1 = y
     u2 = y'
     u3 = y''
     ...
     um = y^{(m-1)}
   Entonces:
     u1' = u2
     u2' = u3
     ...
     u_{m-1}' = u_m
     u_m' = F(x, u1, u2, ..., u_m)
   Para usar este programa:
    - Si m == 3, asigná f1 = u2, f2 = u3, f3 = F(x,u1,u2,u3).
    - Ajustá las condiciones iniciales (y(x0), y'(x0), y''(x0)).
    - Para m > 3 necesitás extender el código a más ecuaciones (agregar arrays y_k).
   Esta transformación es estándar y permite aplicar los mismos métodos
   (Euler, RK4, Heun) tal como están implementados aquí.
*/