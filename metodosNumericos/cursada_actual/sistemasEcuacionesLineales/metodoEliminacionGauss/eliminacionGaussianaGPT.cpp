#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n   2         // tamaño del sistema (3x3)
#define EPS 1e-12      // tolerancia para pivotes ~0

void cargar(double A[n][n], double b[n]);
void leer(const double A[n][n], const double b[n]);
int  gauss(double A[n][n], double b[n], double x[n]);  // <- ahora recibe x

/* utilitario: intercambio de filas en A y b */
static void swap_rows(double A[n][n], double b[n], int r1, int r2) {
    if (r1 == r2) return;
    for (int j = 0; j < n; ++j) {
        double tmp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = tmp;
    }
    double tb = b[r1]; b[r1] = b[r2]; b[r2] = tb;
}

int main(void)
{
    double A[n][n], b[n], x[n];

    cargar(A, b);
    puts("\nSistema ingresado (A | b):");
    leer(A, b);

    if (!gauss(A, b, x)) {
        fprintf(stderr, "\nERROR: sistema singular o mal condicionado (pivote ~ 0).\n");
        return 1;
    }

    puts("\nSistema tras eliminación (triangular superior | b):");
    leer(A, b);

    printf("\nSolución (x):\n");
    for (int i = 0; i < n; ++i)
        printf("x%d = %.10f\n", i+1, x[i]);

    return 0;
}

void cargar(double A[n][n], double b[n]){
    puts("Cargar matriz A:");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("A(%d,%d) = ", i+1, j+1);
            if (scanf("%lf", &A[i][j]) != 1) exit(1);
        }
    }
    puts("\nCargar vector b:");
    for (int i = 0; i < n; i++){
        printf("b(%d) = ", i+1);
        if (scanf("%lf", &b[i]) != 1) exit(1);
    }
}

void leer(const double A[n][n], const double b[n]){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            printf("%10.4f ", A[i][j]);
        printf(" | %10.4f\n", b[i]);
    }
}

/* Eliminación de Gauss con pivoteo parcial
   - Modifica A y b (in-place)
   - Escribe la solución en x
   - Retorna 1 si ok, 0 si singular/mal condicionado
*/
int gauss(double A[n][n], double b[n], double x[n]) {
    // ==========================
    // 1) Eliminación hacia adelante + PIVOTEO PARCIAL
    // ==========================
    for (int k = 0; k < n; ++k) {
        // (a) Elegir pivote: fila con mayor |A[r][k]| en r = k..n-1
        int piv = k;
        double maxabs = fabs(A[k][k]);
        for (int r = k + 1; r < n; ++r) {
            double v = fabs(A[r][k]);
            if (v > maxabs) { maxabs = v; piv = r; }
        }

        // (b) Si el mejor pivote es ~0, la columna es casi nula => sistema singular
        if (maxabs < EPS) {
            // No se puede continuar: A es singular o está mal condicionada
            return 0;  // ERROR
        }

        // (c) Llevar el mejor pivote a la fila k (swap de filas en A y en b)
        if (piv != k) {
            swap_rows(A, b, k, piv);
        }

        // (d) Eliminar por debajo del pivote para crear ceros en la columna k
        double akk = A[k][k];           // pivote actual (ya garantizamos |akk| >= EPS)
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / akk;   // cuánto de la fila k restamos a la fila i
            A[i][k] = 0.0;                   // forzamos el cero (por definición de eliminación)
            for (int j = k + 1; j < n; ++j) {
                A[i][j] -= factor * A[k][j]; // actualizar el resto de columnas
            }
            b[i] -= factor * b[k];           // actualizar el lado derecho también
        }
    }

    // A este punto, A quedó en forma TRIANGULAR SUPERIOR y b ajustado en consecuencia.

    // ==========================
    // 2) Retrosustitución: resolver U x = b (U = A triangular superior)
    // ==========================
    for (int i = n - 1; i >= 0; --i) {
        // s = b[i] - sum_{j=i+1..n-1} A[i][j] * x[j]
        double s = b[i];
        for (int j = i + 1; j < n; ++j) {
            s -= A[i][j] * x[j];
        }

        double piv = A[i][i];           // pivote diagonal
        if (fabs(piv) < EPS) {
            // Si un pivote diagonal es ~0, el sistema es singular (o casi)
            return 0;  // ERROR
        }

        x[i] = s / piv;                  // despeje de la incógnita i
    }

    return 1;  // OK: solución escrita en x[]
}
