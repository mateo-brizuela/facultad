#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-12

/* Cambiá esta f(x) si querés otro caso cuando elijas modo función */
static double f(double x) {
    return x + 2.0/x;
}

/* ---------- Utilidades simples ---------- */
static int x_repetido(int n, const double *x, double xnew, int hasta) {
    for (int i = 0; i < hasta; ++i)
        if (fabs(x[i] - xnew) < EPS) return 1;
    return 0;
}

static void mostrar_puntos(int n, const double *x, const double *y) {
    printf("\nPuntos cargados:\n");
    printf("  i\t        x_i\t\t        y_i\n");
    for (int i = 0; i < n; ++i)
        printf("  %d\t% .10f\t% .10f\n", i, x[i], y[i]);
}

/* ---------- Lagrange clásico (productos) ---------- */
/* P(xr) = sum_k y[k] * prod_{i!=k} (xr - x[i]) / (x[k] - x[i]) */
static double lagrange_eval(int n, const double *x, const double *y, double xr) {
    /* Si xr coincide con un nodo, devolver exactamente y_k */
    for (int k = 0; k < n; ++k)
        if (fabs(xr - x[k]) < EPS) return y[k];

    double suma = 0.0;
    for (int k = 0; k < n; ++k) {
        double Lk = 1.0;
        for (int i = 0; i < n; ++i) {
            if (i == k) continue;
            double denom = x[k] - x[i];
            if (fabs(denom) < EPS) {
                fprintf(stderr, "Error: hay xi repetidos (x[%d] == x[%d]).\n", k, i);
                exit(1);
            }
            Lk *= (xr - x[i]) / denom;
        }
        suma += y[k] * Lk;
    }
    return suma;
}

/* ----------------- Programa principal ----------------- */
int main(void) {
    printf("=== Interpolacion de Lagrange (forma clasica) ===\n");

    int n;
    do {
        printf("¿Cuantos puntos vas a cargar? (>=2): ");
        if (scanf("%d", &n) != 1) return 1;
    } while (n < 2);

    double *x = (double*)malloc(n * sizeof(double));
    double *y = (double*)malloc(n * sizeof(double));
    if (!x || !y) { fprintf(stderr, "No hay memoria.\n"); return 1; }

    int modo = 0;
    printf("\n¿Cómo queres cargar y?\n");
    printf("  1) y = f(x)  (por defecto f(x)=x+2/x)\n");
    printf("  2) y manual\n");
    printf("Elegí opcion [1/2]: ");
    if (scanf("%d", &modo) != 1) return 1;
    int usar_funcion = (modo == 1);

    /* Carga de puntos */
    printf("\n--- Carga de %d puntos (x_i, y_i) ---\n", n);
    for (int i = 0; i < n; ++i) {
        for (;;) {
            printf("x[%d] = ", i);
            if (scanf("%lf", &x[i]) != 1) return 1;
            if (!x_repetido(n, x, x[i], i)) break;
            printf("  Ese x ya fue ingresado. Todos los xi deben ser distintos.\n");
        }
        if (usar_funcion) {
            y[i] = f(x[i]);
            printf("  y[%d] = f(x[%d]) = %.10f\n", i, i, y[i]);
        } else {
            printf("y[%d] = ", i);
            if (scanf("%lf", &y[i]) != 1) return 1;
        }
    }

    mostrar_puntos(n, x, y);

    /* Evaluaciones */
    printf("\nAhora podés evaluar P(x*). Escribí 'q' para salir.\n");
    int c; while ((c = getchar()) != '\n' && c != EOF) {} /* limpiar buffer */

    char buf[64];
    for (;;) {
        printf("\nx* = ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        if (buf[0] == 'q' || buf[0] == 'Q') break;

        double xr;
        if (sscanf(buf, "%lf", &xr) != 1) {
            printf("Entrada invalida.\n");
            continue;
        }

        double px = lagrange_eval(n, x, y, xr);
        printf("P(%.10f) = %.10f\n", xr, px);

        if (usar_funcion) {
            double fx = f(xr);
            printf("f(%.10f) = %.10f | error abs = %.3e\n", xr, fx, fabs(fx - px));
        }
    }

    free(x); free(y);
    printf("\nListo. ¡Aprobadísimo ese Lagrange! :)\n");
    return 0;
}
