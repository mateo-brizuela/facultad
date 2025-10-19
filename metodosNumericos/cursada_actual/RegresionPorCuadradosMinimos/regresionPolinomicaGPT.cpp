#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N      5          // cantidad de datos
#define GRADO  3          // grado del polinomio
#define K     (GRADO+1)   // tamaño del sistema (coeficientes a0..a_GRADO)
#define EPS    1e-12

// I/O de datos
void cargarVector(double x[N], double y[N]);
void leerVector(const double x[N], const double y[N]);

// Normales: A (KxK) y b (K)
void armarMatriz(const double x[N], const double y[N], double A[K][K], double b[K]);
void leerMatriz(const double A[K][K], const double b[K]);

// Gauss con pivoteo parcial: resuelve A x = b
int  gauss(double A[K][K], double b[K], double sol[K]);

int main(void) {
    double x[N], y[N];
    double A[K][K], b[K], a[K] = {0};

    if (N < K) {
        printf("Error: no hay datos suficientes (N=%d) para grado %d (K=%d)\n", N, GRADO, K);
        return 1;
    }

    cargarVector(x, y);
    printf("\nDatos cargados:\n");
    leerVector(x, y);

    armarMatriz(x, y, A, b);
    printf("\nSistema normal (A | b):\n");
    leerMatriz(A, b);

    if (!gauss(A, b, a)) {
        fprintf(stderr, "Sistema singular o muy mal condicionado.\n");
        return 1;
    }

    printf("\nCoeficientes (a0..a%d):\n", GRADO);
    for (int i = 0; i < K; ++i)
        printf("a[%d] = %.10f\n", i, a[i]);

    return 0;
}

/* ---------- I/O ---------- */
void cargarVector(double x[N], double y[N]) {
    printf("Vamos a cargar %d puntos (x[i], y[i])\n", N);
    for (int i = 0; i < N; ++i) {
        printf("x[%d] = ", i);  if (scanf("%lf", &x[i]) != 1) exit(1);
        printf("y[%d] = ", i);  if (scanf("%lf", &y[i]) != 1) exit(1);
    }
}
void leerVector(const double x[N], const double y[N]) {
    printf("   i\t       x_i\t\t       y_i\n");
    for (int i = 0; i < N; ++i)
        printf("  %2d\t% .10f\t% .10f\n", i, x[i], y[i]);
}

/* ---------- Normales (X^T X y X^T y) con base monomial ---------- */
void armarMatriz(const double x[N], const double y[N], double A[K][K], double b[K]) {
    // b[l] = sum x_i^l * y_i
    for (int l = 0; l < K; ++l) {
        double sxy = 0.0;
        for (int i = 0; i < N; ++i) sxy += pow(x[i], l) * y[i];
        b[l] = sxy;
    }
    // A[l][m] = sum x_i^(l+m)
    for (int l = 0; l < K; ++l) {
        for (int m = 0; m < K; ++m) {
            double sx = 0.0;
            for (int i = 0; i < N; ++i) sx += pow(x[i], l + m);
            A[l][m] = sx;
        }
    }
}
void leerMatriz(const double A[K][K], const double b[K]) {
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j)
            printf("%12.6f ", A[i][j]);
        printf("| %12.6f\n", b[i]);
    }
}

/* ---------- Gauss con pivoteo parcial ---------- */
int gauss(double A[K][K], double b[K], double x[K]) {
    // forward elimination + pivoteo parcial
    for (int i = 0; i < K; ++i) {
        // elegir mejor pivote en columna i
        int piv = i;
        double maxabs = fabs(A[i][i]);
        for (int r = i + 1; r < K; ++r) {
            double v = fabs(A[r][i]);
            if (v > maxabs) { maxabs = v; piv = r; }
        }
        if (maxabs < EPS) return 0; // columna ~0 => singular

        // swap filas en A y b
        if (piv != i) {
            for (int j = 0; j < K; ++j) {
                double tmp = A[piv][j];
                A[piv][j] = A[i][j];
                A[i][j]   = tmp;
            }
            double tb = b[piv]; b[piv] = b[i]; b[i] = tb;
        }

        // eliminar debajo
        double aii = A[i][i];
        for (int r = i + 1; r < K; ++r) {
            double f = A[r][i] / aii;
            A[r][i] = 0.0;
            for (int j = i + 1; j < K; ++j)
                A[r][j] -= f * A[i][j];
            b[r] -= f * b[i];
        }
    }

    // back substitution
    for (int i = K - 1; i >= 0; --i) {
        double s = b[i];
        for (int j = i + 1; j < K; ++j)
            s -= A[i][j] * x[j];
        double piv = A[i][i];
        if (fabs(piv) < EPS) return 0;
        x[i] = s / piv;
    }
    return 1;
}
