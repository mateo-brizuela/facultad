#include <cstdio>
#include <cstdlib>
#include <cmath>

#define n 3
#define EPS 1e-12
#define MAX_ITER 100000

void cargar(double matriz[n][n], double vector[n]);
void leer(const double matriz[n][n], const double vector[n]);
bool es_diag_dom(const double A[n][n]);
void gauss_seidel(const double A_[n][n], const double b_[n]);

int main() {
    double A[n][n], b[n];
    cargar(A, b);
    leer(A, b);
    gauss_seidel(A, b);
    return 0;
}

void cargar(double matriz[n][n], double vector[n]) {
    std::printf("vamos a cargar la matriz\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::printf("ingrese el elemento de la fila %d y la columna %d: ", (i+1), (j+1));
            if (std::scanf("%lf", &matriz[i][j]) != 1) {
                std::fprintf(stderr, "entrada invalida\n"); std::exit(1);
            }
        }
    }
    std::printf("\nvamos a cargar el vector independiente\n");
    for (int i = 0; i < n; i++){
        std::printf("ingrese el elemento b%d: ", i);
        if (std::scanf("%lf", &vector[i]) != 1) {
            std::fprintf(stderr, "entrada invalida\n"); std::exit(1);
        }
    }
    std::printf("\n");
}

void leer(const double matriz[n][n], const double vector[n]) {
    std::printf("matriz:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::printf("%.6f\t", matriz[i][j]);
        }
        std::printf("|%.6f\n", vector[i]);
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

void gauss_seidel(const double A_[n][n], const double b_[n]) {
    // Copias locales (A y b no cambian en GS, pero dejo firmas const limpias)
    double A[n][n], b[n];
    for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) A[i][j] = A_[i][j]; b[i] = b_[i]; }

    // Aviso (no aborto) sobre dominancia diagonal
    if (!es_diag_dom(A)) {
        std::printf("ADVERTENCIA: la matriz NO es estrictamente diagonalmente dominante; Gauss–Seidel puede no converger.\n\n");
    } else {
        std::printf("OK: la matriz es estrictamente diagonalmente dominante.\n\n");
    }

    // Chequeo de pivote ≈ 0
    for (int i = 0; i < n; ++i) {
        if (std::fabs(A[i][i]) < EPS) {
            std::fprintf(stderr, "Error: pivote ~0 en A[%d][%d]. Reordene filas o use otro metodo.\n", i, i);
            std::exit(1);
        }
    }

    // Estados
    double x_old[n] = {0.0};
    double x_new[n] = {0.0};

    // Tolerancia desde cifras decimales
    int cifrasTolerancia = 0;
    std::printf("ingrese la cantidad de cifras decimales de precision: ");
    if (std::scanf("%d", &cifrasTolerancia) != 1 || cifrasTolerancia < 0) {
        std::fprintf(stderr, "cifras invalidas\n"); std::exit(1);
    }
    double tol = std::pow(10.0, -static_cast<double>(cifrasTolerancia));

    // Iteración Gauss–Seidel
    double error = 1e300;
    int iter = 0;

    while (error > tol && iter < MAX_ITER) {
        for (int i = 0; i < n; ++i) {
            double suma = 0.0;

            // j < i: usar x_new (ya actualizado en esta pasada)
            for (int j = 0; j < i; ++j) suma += A[i][j] * x_new[j];

            // j > i: usar x_old (todavía no actualizado)
            for (int j = i + 1; j < n; ++j) suma += A[i][j] * x_old[j];

            x_new[i] = (b[i] - suma) / A[i][i];
        }

        // error = norma infinito de (x_new - x_old)
        error = 0.0;
        for (int i = 0; i < n; ++i) {
            double diff = std::fabs(x_new[i] - x_old[i]);
            if (diff > error) error = diff;
        }

        // preparar siguiente iteración
        for (int i = 0; i < n; ++i) x_old[i] = x_new[i];
        ++iter;
    }

    if (error <= tol)
        std::printf("Convergio en %d iteraciones (error=%.12f, tol=%.12f)\n", iter, error, tol);
    else
        std::printf("No convergio en %d iteraciones (error=%.12f, tol=%.12f)\n", iter, error, tol);

    // Mostrar solución en decimal (fixed)
    std::printf("vector de incognitas: ");
    for (int i = 0; i < n; ++i) std::printf("x%d=%.12f  ", i+1, x_new[i]);
    std::printf("\n");

    // Residuo ||Ax - b||_2 (diagnóstico)
    double res2 = 0.0;
    for (int i = 0; i < n; ++i) {
        double ax = 0.0;
        for (int j = 0; j < n; ++j) ax += A[i][j] * x_new[j];
        double ri = ax - b[i];
        res2 += ri * ri;
    }
    std::printf("||Ax - b||_2 = %.12f\n\n", std::sqrt(res2));
}
