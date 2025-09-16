#include <cstdio>
#include <cstdlib>
#include <cmath>

#define n   3
#define EPS 1e-12

// I/O puntos
void cargarVector(double x[n], double y[n]);
void leerVector(const double x[n], const double y[n]);

// Vandermonde
void cargarMatriz(const double x[n], double V[n][n]);
void leerMatriz(const double V[n][n], const double y[n]);

// Gauss
int  gauss(double A[n][n], double b[n], double sol[n]);
static void swap_rows(double A[n][n], double b[n], int r1, int r2) {
    if (r1 == r2) return;
    for (int j = 0; j < n; ++j) {
        double tmp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = tmp;
    }
    double tb = b[r1]; b[r1] = b[r2]; b[r2] = tb;
}

int main() {
    double x[n], y[n];
    double V[n][n];
    double a[n];  // coeficientes del polinomio

    std::printf("Interpolacion (forma funcional) — con Gauss\n\n");
    cargarVector(x, y);
    std::printf("\nPuntos cargados:\n");
    leerVector(x, y);

    cargarMatriz(x, V);
    std::printf("\nSistema Vandermonde (V | y):\n");
    leerMatriz(V, y);

    if (!gauss(V, y, a)) {
        std::fprintf(stderr, "\nERROR: sistema singular o mal condicionado.\n");
        return 1;
    }

    std::printf("\nCoeficientes P(x) = a0 + a1 x + ... + a%d x^%d:\n", n-1, n-1);
    for (int i = 0; i < n; ++i)
        std::printf("a[%d] = %.10f\n", i, a[i]);

    return 0;
}

/* ===== I/O puntos ===== */
void cargarVector(double x[n], double y[n]) {
    std::printf("Vamos a cargar %d puntos (x_i, y_i):\n", n);
    for (int i = 0; i < n; ++i) {
        std::printf("x[%d] = ", i);
        std::scanf("%lf", &x[i]);
        std::printf("y[%d] = ", i);
        std::scanf("%lf", &y[i]);
    }
}
void leerVector(const double x[n], const double y[n]) {
    std::printf("   i\t        x_i\t\t        y_i\n");
    for (int i = 0; i < n; ++i)
        std::printf("  %2d\t% .10f\t% .10f\n", i, x[i], y[i]);
}

/* ===== Vandermonde ===== */
void cargarMatriz(const double x[n], double V[n][n]) {
    for (int i = 0; i < n; ++i) {
        double pot = 1.0;        // x_i^0
        for (int j = 0; j < n; ++j) {
            V[i][j] = pot;       // x_i^j
            pot *= x[i];         // x_i^{j+1}
        }
    }
}
void leerMatriz(const double V[n][n], const double y[n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::printf("%10.6f ", V[i][j]);
        std::printf("| %10.6f\n", y[i]);
    }
}

/* ===== Gauss con pivoteo parcial =====
   Resuelve A * sol = b. Modifica A y b in-place.
   Retorna 1 si OK, 0 si singular/mal condicionado. */
int gauss(double A[n][n], double b[n], double sol[n]) {
    // Eliminación hacia adelante + pivoteo parcial
    for (int k = 0; k < n; ++k) {
        // elegir pivote (máximo absoluto en la columna k)
        int piv = k;
        double maxabs = std::fabs(A[k][k]);
        for (int r = k + 1; r < n; ++r) {
            double v = std::fabs(A[r][k]);
            if (v > maxabs) { maxabs = v; piv = r; }
        }
        if (maxabs < EPS) return 0;  // columna ~ 0 => singular

        if (piv != k) swap_rows(A, b, k, piv);

        // eliminar debajo del pivote
        double akk = A[k][k];
        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / akk;
            A[i][k] = 0.0;
            for (int j = k + 1; j < n; ++j)
                A[i][j] -= factor * A[k][j];
            b[i] -= factor * b[k];
        }
    }

    // Retrosustitución (U * sol = b)
    for (int i = n - 1; i >= 0; --i) {
        double s = b[i];
        for (int j = i + 1; j < n; ++j)
            s -= A[i][j] * sol[j];
        double piv = A[i][i];
        if (std::fabs(piv) < EPS) return 0;
        sol[i] = s / piv;
    }
    return 1;
}
