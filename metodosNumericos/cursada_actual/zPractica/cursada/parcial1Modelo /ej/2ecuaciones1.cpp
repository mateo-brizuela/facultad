#include <stdio.h>
#include <cmath>

//librerias 
#include "./libreria/io/exportarResultados.h"

// Ejemplos de funciones para sistema acoplado:
// y1' = f1(x,y1,y2), y2' = f2(x,y1,y2)
// Podés reemplazar por el sistema que necesites.
double f1(double x, double y1, double y2) {
    // ejemplo acoplado simple: y1' = y2 - (2x+1)*sqrt(fmax(y1,0))
    //return y2 - ((2*x) + 1.0) * sqrt(fmax(y1, 0.0));
    return y2;
}

double f2(double x, double y1, double y2) {
    // ejemplo acoplado: y2' = -y1 - (2*x+1)*sqrt(fmax(y2,0))
    //return -y1 - ((2*x) + 1.0) * sqrt(fmax(y2, 0.0));
    return -y1 + 4.0*cos(x);
}

//prototipo de funciones (ahora reciben la configuracion de discretizacion)
// modo: 1 -> por N (subintervalos), 2 -> por h
// - modo: 1 = usar N subintervalos (h = (b-a)/N), 2 = usar paso h (se corta cuando supera b)
// - N: número de subintervalos (si modo==1)
// - h: paso (si modo==2)
void euler(int modo, int N, double h, double a, double b, double x0, double y10, double y20);
void rk4  (int modo, int N, double h, double a, double b, double x0, double y10, double y20);
void heun (int modo, int N, double h, double a, double b, double x0, double y10, double y20);

// Función auxiliar para calcular N,h,P según modo
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
    double y10 = 1.0, y20 = 0.0; // condiciones iniciales
    int modo = 1, N = 0;
    double h = 0.0;

    printf("Sistema de EDO de primer orden (2 ecuaciones)\n");
    printf("Ingrese extremos [a,b]\n");
    printf("a: "); scanf("%lf", &a);
    printf("b: "); scanf("%lf", &b);
    while (b <= a) { printf("b > a requerido. Reingrese b: "); scanf("%lf", &b); }

    printf("x0 (ideal x0=a): "); scanf("%lf", &x0);
    printf("y1(x0): "); scanf("%lf", &y10);
    printf("y2(x0): "); scanf("%lf", &y20);

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
        N = 0;
    }

    printf("\nEjecutando métodos...\n");
    euler(modo, N, h, a, b, x0, y10, y20);
    rk4  (modo, N, h, a, b, x0, y10, y20);
    heun (modo, N, h, a, b, x0, y10, y20);
    return 0;
}

// Euler acoplado
void euler(int modo, int N, double h, double a, double b, double x0, double y10, double y20) {
    const double eps = 1e-12;
    int P;
    calcularMallado(modo, N, h, a, b, &N, &h, &P);

    if (fabs(x0 - a) > eps) { printf("[Euler] x0!=a -> ajustado\n"); x0 = a; }

    double *x = new double[P];
    double *y1 = new double[P];
    double *y2 = new double[P];

    x[0]=x0; y1[0]=y10; y2[0]=y20;

    for (int i=1; i<P; ++i) {
        double xn = x[i-1];
        double y1n = y1[i-1];
        double y2n = y2[i-1];

        x[i] = xn + h;
        // usar estado completo (y1,y2) en cada derivada
        y1[i] = y1n + h * f1(xn, y1n, y2n);
        y2[i] = y2n + h * f2(xn, y1n, y2n);
    }
    if (modo==1) x[P-1]=b;

    printf("[Euler] modo=%d N=%d P=%d h=%.6f\n", modo, N, P, h);
    printf("i\t x\t\t y1\t\t y2\n");
    for (int i=0;i<P;++i)
        printf("%d\t%.8f\t%.8f\t%.8f\n", i, x[i], y1[i], y2[i]);

    exportarDerivadas("euler_y1", x, y1, P);
    exportarDerivadas("euler_y2", x, y2, P);

    delete[] x; delete[] y1; delete[] y2;
}

// RK4 acoplado
void rk4(int modo, int N, double h, double a, double b, double x0, double y10, double y20) {
    const double eps = 1e-12;
    int P;
    calcularMallado(modo, N, h, a, b, &N, &h, &P);

    if (fabs(x0 - a) > eps) { printf("[RK4] x0!=a -> ajustado\n"); x0 = a; }

    double *x = new double[P];
    double *y1 = new double[P];
    double *y2 = new double[P];

    x[0]=x0; y1[0]=y10; y2[0]=y20;

    for (int i=1; i<P; ++i) {
        double xn  = x[i-1];
        double y1n = y1[i-1];
        double y2n = y2[i-1];

        x[i] = xn + h;

        // k1
        double k1_1 = f1(xn, y1n, y2n);
        double k1_2 = f2(xn, y1n, y2n);
        // k2
        double k2_1 = f1(xn + h/2.0, y1n + (h/2.0)*k1_1, y2n + (h/2.0)*k1_2);
        double k2_2 = f2(xn + h/2.0, y1n + (h/2.0)*k1_1, y2n + (h/2.0)*k1_2);
        // k3
        double k3_1 = f1(xn + h/2.0, y1n + (h/2.0)*k2_1, y2n + (h/2.0)*k2_2);
        double k3_2 = f2(xn + h/2.0, y1n + (h/2.0)*k2_1, y2n + (h/2.0)*k2_2);
        // k4
        double k4_1 = f1(xn + h, y1n + h*k3_1, y2n + h*k3_2);
        double k4_2 = f2(xn + h, y1n + h*k3_1, y2n + h*k3_2);

        y1[i] = y1n + (h/6.0) * (k1_1 + 2*k2_1 + 2*k3_1 + k4_1);
        y2[i] = y2n + (h/6.0) * (k1_2 + 2*k2_2 + 2*k3_2 + k4_2);
    }
    if (modo==1) x[P-1]=b;

    printf("[RK4] modo=%d N=%d P=%d h=%.6f\n", modo, N, P, h);
    printf("i\t x\t\t y1\t\t y2\n");
    for (int i=0;i<P;++i)
        printf("%d\t%.8f\t%.8f\t%.8f\n", i, x[i], y1[i], y2[i]);

    exportarDerivadas("rk4_y1", x, y1, P);
    exportarDerivadas("rk4_y2", x, y2, P);

    delete[] x; delete[] y1; delete[] y2;
}

// Heun (trapecio explícito) acoplado
void heun(int modo, int N, double h, double a, double b, double x0, double y10, double y20) {
    const double eps = 1e-12;
    int P;
    calcularMallado(modo, N, h, a, b, &N, &h, &P);

    if (fabs(x0 - a) > eps) { printf("[Heun] x0!=a -> ajustado\n"); x0 = a; }

    double *x = new double[P];
    double *y1 = new double[P];
    double *y2 = new double[P];

    x[0]=x0; y1[0]=y10; y2[0]=y20;

    for (int i=1; i<P; ++i) {
        double xn  = x[i-1];
        double y1n = y1[i-1];
        double y2n = y2[i-1];

        x[i] = xn + h;

        // Predictor (Euler) con estado completo
        double y1_tilde = y1n + h * f1(xn, y1n, y2n);
        double y2_tilde = y2n + h * f2(xn, y1n, y2n);

        // Corrector (promedio de pendientes)
        y1[i] = y1n + 0.5*h * ( f1(xn, y1n, y2n) + f1(x[i], y1_tilde, y2_tilde) );
        y2[i] = y2n + 0.5*h * ( f2(xn, y1n, y2n) + f2(x[i], y1_tilde, y2_tilde) );
    }
    if (modo==1) x[P-1]=b;

    printf("[Heun] modo=%d N=%d P=%d h=%.6f\n", modo, N, P, h);
    printf("i\t x\t\t y1\t\t y2\n");
    for (int i=0;i<P;++i)
        printf("%d\t%.8f\t%.8f\t%.8f\n", i, x[i], y1[i], y2[i]);

    exportarDerivadas("heun_y1", x, y1, P);
    exportarDerivadas("heun_y2", x, y2, P);

    delete[] x; delete[] y1; delete[] y2;
}

/* 
  Guía práctica (patrón) para AUMENTAR el número de ecuaciones en este programa
  (ej.: de 2 → 3 → 4 ecuaciones). Enfocada en el patrón repetitivo a aplicar,
  útil para extender a órdenes superiores transformándolos primero en un
  sistema de primer orden.

  Idea general (patrón repetitivo)
  - Por cada nueva variable y_k:
    1) declarar la función f_k(x, y1, y2, ..., yk) que devuelva su derivada;
    2) añadir la condición inicial yk(x0) en la entrada principal;
    3) ampliar las firmas/prototipos de los métodos (Euler, RK4, Heun) para
       aceptar la nueva condición inicial (o leerla dentro);
    4) dentro de cada método:
       - reservar un nuevo array yk[P] junto a los ya existentes;
       - en el bucle de pasos, actualizar yk usando la misma fórmula que para
         y1,y2 (estado completo en la evaluación de f_k);
       - en RK4/Heun crear/usar los k?_k temporales correspondientes a la nueva
         componente y combinarlos exactamente igual que para las anteriores;
    5) exportar/imprimir la componente adicional (como se hace con y1,y2).

  Ejemplo mínimo: ADAPTAR de 2→3 ecuaciones
  - Añadir función:
      double f3(double x, double y1, double y2, double y3) { ... }
  - En main(): pedir y3(x0) igual que y1,y2.
  - Prototipos:
      void euler(int modo, int N, double h, double a, double b, double x0,
                 double y10, double y20, double y30);
      // idem para rk4, heun
  - En euler(): reservar double *y3 = new double[P]; inicializar y3[0]=y30;
    dentro del bucle:
      y3[i] = y3n + h * f3(xn, y1n, y2n, y3n);
    y luego imprimir/exportar y3 igual que y1,y2.
  - En rk4(): crear k1_3,k2_3,k3_3,k4_3 y usarlos igual que para k?_1,k?_2,
    p.e.:
      k1_3 = f3(xn, y1n, y2n, y3n);
      k2_3 = f3(xn+h/2, y1n+(h/2)*k1_1, y2n+(h/2)*k1_2, y3n+(h/2)*k1_3);
    y combinación final:
      y3[i] = y3n + (h/6)*(k1_3 + 2*k2_3 + 2*k3_3 + k4_3);

  Analogía para 3→4 ecuaciones
  - Repetir exactamente el mismo patrón: definir f4, pedir y40, añadir y4 array,
    crear k?_4 temporales en RK4/Heun, actualizar e imprimir/exportar.

  Nota sobre EDOs de orden superior
  - Un EDO de orden r se transforma en r ecuaciones de primer orden:
      u1 = y
      u2 = y'
      ...
      ur = y^{(r-1)}
    Entonces:
      u1' = u2
      u2' = u3
      ...
      u_{r-1}' = ur
      ur' = F(x, u1, u2, ..., ur)
    - Para elevar de orden (por ejemplo pasar de 1 a 2 o 3) aplicá el patrón
      anterior: cada nueva u_k es una nueva "ecuación" con su f_k.
    - En implementación práctica, las primeras r-1 ecuaciones suelen ser
      triviales (u_{k}' = u_{k+1}) y sólo la última contiene la función F.

  Recomendaciones para mantener el código manejable
  - Mantener el mismo orden de variables y parámetros en todas las funciones.
  - Nombrar k temporales con sufijos (k1_1, k1_2, ... k1_m) y agrupar por componente.
  - Si añadís muchas ecuaciones, considerar refactorizar a vectores/funciones
    que trabajen por componentes (pero eso ya sale del patrón repetitivo).
  - Probar incrementos pequeños (2→3, luego 3→4) y comprobar resultados
    con ejemplos conocidos antes de escalar más.

  Ejemplo compacto (esqueleto dentro de RK4 para añadir componente 3):
    // k1
    k1_1 = f1(xn, y1n, y2n, y3n);
    k1_2 = f2(xn, y1n, y2n, y3n);
    k1_3 = f3(xn, y1n, y2n, y3n);
    // k2 (usar todos los k1)
    k2_1 = f1(xn+h/2, y1n+(h/2)*k1_1, y2n+(h/2)*k1_2, y3n+(h/2)*k1_3);
    ...
    // combinación final por componente:
    y1[i] = y1n + (h/6)*(k1_1 + 2*k2_1 + 2*k3_1 + k4_1);
    y2[i] = y2n + (h/6)*(k1_2 + 2*k2_2 + 2*k3_2 + k4_2);
    y3[i] = y3n + (h/6)*(k1_3 + 2*k2_3 + 2*k3_3 + k4_3);

  Con este patrón repetitivo podés añadir una o dos ecuaciones más sin
  reestructurar todo el código: definir la nueva f_k, condiciones iniciales,
  reservar el array yk[], añadir las fórmulas de actualización y exportar.
*/

