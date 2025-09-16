#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cfloat>

#define n 3
#define EPS 1e-12
#define MAX_ITER 100000

void cargar(double A[n][n], double b[n]);
void leer(const double A[n][n], const double b[n]);
bool es_diag_dom(const double A[n][n]);
void jacobi(const double A_[n][n], const double b_[n]);

int main() {
    double A[n][n], b[n];
    cargar(A, b);
    leer(A, b);
    jacobi(A, b);
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
        for (int j = 0; j < n; ++j) std::printf("%.2f\t", A[i][j]);
        std::printf("|%.2f\n", b[i]);
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

void jacobi(const double A_[n][n], const double b_[n]) {
    // Copias locales (A y b no cambian en Jacobi)
    double A[n][n], b[n];
    for (int i=0;i<n;++i){ for(int j=0;j<n;++j) A[i][j]=A_[i][j]; b[i]=b_[i]; }

    if (!es_diag_dom(A)) {
        std::printf("ADVERTENCIA: la matriz NO es estrictamente diagonalmente dominante; Jacobi puede no converger.\n\n");
    } else {
        std::printf("OK: la matriz es estrictamente diagonalmente dominante.\n\n");
    }

    for (int i = 0; i < n; ++i) {
        if (std::fabs(A[i][i]) < EPS) {
            std::fprintf(stderr, "Error: pivote ~0 en A[%d][%d]. Reordene filas o use otro metodo.\n", i, i);
            std::exit(1);
        }
    }

    double xv[n] = {0.0}; // viejo
    double xn[n] = {0.0}; // nuevo

    int cifrasTolerancia = 0;
    std::printf("ingrese la cantidad de cifras decimales de precision: ");
    if (std::scanf("%d", &cifrasTolerancia) != 1 || cifrasTolerancia < 0) {
        std::fprintf(stderr, "cifras invalidas\n"); std::exit(1);
    }
    double tolerancia = std::pow(10.0, -static_cast<double>(cifrasTolerancia));

    double error = DBL_MAX;
    int iter = 0;

    while (error > tolerancia && iter < MAX_ITER) {
        for (int i = 0; i < n; ++i) {
            double suma = 0.0;
            for (int j = 0; j < n; ++j) if (j != i) suma += A[i][j] * xv[j];
            xn[i] = (b[i] - suma) / A[i][i];
        }

        // error = norma infinito de (xn - xv)
        error = 0.0;
        for (int i = 0; i < n; ++i) {
            double diff = std::fabs(xn[i] - xv[i]);
            if (diff > error) error = diff;
        }

        for (int i = 0; i < n; ++i) xv[i] = xn[i];
        ++iter;
    }

    // ----- Salidas en ambos formatos -----

    if (error <= tolerancia)
        std::printf("Convergio en %d iteraciones\n", iter);
    else
        std::printf("No convergio en %d iteraciones\n", iter);

    // Error
    std::printf("error (fixed)       : %.12f\n", error);
    std::printf("error (cientifica)  : %.6e\n", error);
    std::printf("tolerancia (fixed)  : %.12f\n", tolerancia);
    std::printf("tolerancia (cient.) : %.6e\n", tolerancia);

    // Vector solución (decimal/fixed)
    std::printf("vector de incognitas (fixed): ");
    for (int i = 0; i < n; ++i) std::printf("x%d=%.12f  ", i+1, xn[i]);
    std::printf("\n");

    // Residuo ||Ax - b||_2 en ambos formatos
    double res2 = 0.0;
    for (int i = 0; i < n; ++i) {
        double ax = 0.0;
        for (int j = 0; j < n; ++j) ax += A[i][j] * xn[j];
        double ri = ax - b[i];
        res2 += ri * ri;
    }
    double res = std::sqrt(res2);
    std::printf("||Ax - b||_2 (fixed)      : %.12f\n", res);
    std::printf("||Ax - b||_2 (cientifica) : %.6e\n\n", res);
}
