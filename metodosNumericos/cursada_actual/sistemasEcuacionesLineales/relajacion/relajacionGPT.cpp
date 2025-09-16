#include <cstdio>
#include <cstdlib>
#include <cmath>

#define n 3
#define EPS 1e-12
#define MAX_ITER 100000

void cargar(double A[n][n], double b[n]);
void leer(const double A[n][n], const double b[n]);
bool es_diag_dom(const double A[n][n]);
void relajacion(const double A_[n][n], const double b_[n]); // SOR

int main() {
    double A[n][n], b[n];
    cargar(A, b);
    leer(A, b);
    relajacion(A, b);
    return 0;
}

void cargar(double A[n][n], double b[n]) {
    std::printf("vamos a cargar la matriz\n");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            std::printf("ingrese el elemento de la fila %d y la columna %d: ", i+1, j+1);
            if (std::scanf("%lf", &A[i][j]) != 1) { std::fprintf(stderr,"entrada invalida\n"); std::exit(1); }
        }

    std::printf("\nvamos a cargar el vector independiente\n");
    for (int i = 0; i < n; ++i) {
        std::printf("ingrese el elemento b%d: ", i);
        if (std::scanf("%lf", &b[i]) != 1) { std::fprintf(stderr,"entrada invalida\n"); std::exit(1); }
    }
    std::printf("\n");
}

void leer(const double A[n][n], const double b[n]) {
    std::printf("matriz:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) std::printf("%.6f\t", A[i][j]);
        std::printf("|%.6f\n", b[i]);
    }
    std::printf("\n");
}

bool es_diag_dom(const double A[n][n]) {
    for (int i = 0; i < n; ++i) {
        double suma_abs = 0.0;
        for (int j = 0; j < n; ++j) if (j != i) suma_abs += std::fabs(A[i][j]);
        if (!(std::fabs(A[i][i]) > suma_abs + EPS)) return false; // estricta
    }
    return true;
}

void relajacion(const double A_[n][n], const double b_[n]) {
    // copias locales (A y b no cambian en SOR)
    double A[n][n], b[n];
    for (int i=0;i<n;++i){ for(int j=0;j<n;++j) A[i][j]=A_[i][j]; b[i]=b_[i]; }

    if (!es_diag_dom(A))
        std::printf("ADVERTENCIA: la matriz NO es estrictamente diagonalmente dominante; SOR puede no converger.\n\n");

    // pivotes válidos
    for (int i = 0; i < n; ++i) {
        if (std::fabs(A[i][i]) < EPS) {
            std::fprintf(stderr, "Error: pivote ~0 en A[%d][%d]. Reordene filas o use otro metodo.\n", i, i);
            std::exit(1);
        }
    }

    // estado
    double xv[n] = {0.0}; // viejo
    double xn[n] = {0.0}; // nuevo

    // parámetros
    int cifrasTolerancia = 0;
    std::printf("ingrese la cantidad de cifras decimales de precision: ");
    if (std::scanf("%d", &cifrasTolerancia) != 1 || cifrasTolerancia < 0) { std::fprintf(stderr,"cifras invalidas\n"); std::exit(1); }
    double tol = std::pow(10.0, -static_cast<double>(cifrasTolerancia));

    double omega = 1.0;
    std::printf("ingrese omega (1.0 = Gauss-Seidel; tipico 1.1..1.9): ");
    if (std::scanf("%lf", &omega) != 1) { std::fprintf(stderr,"omega invalido\n"); std::exit(1); }

    // iteración SOR
    double error = 1e300;
    int iter = 0;

    while (error > tol && iter < MAX_ITER) {
        for (int i = 0; i < n; ++i) {
            double suma = 0.0;
            // j < i: usar xn (ya actualizado)
            for (int j = 0; j < i; ++j) suma += A[i][j] * xn[j];
            // j > i: usar xv (viejo)
            for (int j = i+1; j < n; ++j) suma += A[i][j] * xv[j];

            // Gauss-Seidel "puro" para la componente i
            double xgs = (b[i] - suma) / A[i][i];
            // SOR: mezcla con el valor viejo
            xn[i] = (1.0 - omega) * xv[i] + omega * xgs;
        }

        // error = norma infinito de (xn - xv)
        error = 0.0;
        for (int i = 0; i < n; ++i) {
            double d = std::fabs(xn[i] - xv[i]);
            if (d > error) error = d;
        }

        // preparar próxima iteración
        for (int i = 0; i < n; ++i) xv[i] = xn[i];
        ++iter;
    }

    if (error <= tol)
        std::printf("Convergio en %d iteraciones (error=%.12f, tol=%.12f)\n", iter, error, tol);
    else
        std::printf("No convergio en %d iteraciones (error=%.12f, tol=%.12f)\n", iter, error, tol);

    // solución y residuo
    std::printf("vector de incognitas: ");
    for (int i = 0; i < n; ++i) std::printf("x%d=%.12f  ", i+1, xn[i]);
    std::printf("\n");

    double res2 = 0.0;
    for (int i = 0; i < n; ++i) {
        double ax = 0.0;
        for (int j = 0; j < n; ++j) ax += A[i][j] * xn[j];
        double ri = ax - b[i];
        res2 += ri * ri;
    }
    std::printf("||Ax - b||_2 = %.12f\n\n", std::sqrt(res2));
}
