// regresion_lineal_gauss_dynamic.cpp
// Ajuste por minimos cuadrados: y = a*x + b
// Arma el sistema 2x2 (ecuaciones normales) y lo resuelve con gauss_solve_dynamic()

#include "gauss_solver.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n;
    printf("REGRESION LINEAL (Gauss dinamico / ecuaciones normales)\n");
    printf("Modelo: y = a*x + b\n\n");

    printf("Ingrese cantidad de puntos n: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Error: se necesitan al menos 2 puntos.\n");
        return 1;
    }

    // Sumatorias
    double Sx = 0.0, Sy = 0.0, Sxx = 0.0, Sxy = 0.0;

    // Asignar memoria dinamica para los puntos
    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));
    if (x == NULL || y == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Punto %d:\n", i + 1);
        printf("  Ingrese x[%d]: ", i + 1);
        scanf("%lf", &x[i]);
        printf("  Ingrese y[%d]: ", i + 1);
        scanf("%lf", &y[i]);

        Sx  += x[i];
        Sy  += y[i];
        Sxx += x[i] * x[i];
        Sxy += x[i] * y[i];
    }

    leerVectoresTabla(x, y, n);

    // Sistema 2x2:
    // [ sum(x^2)  sum(x) ] [ a ] = [ sum(xy) ]
    // [ sum(x)      n    ] [ b ]   [ sum(y)  ]
    int dim = 2;

    double** A = new double*[dim];
    for (int i = 0; i < dim; i++) {
        A[i] = new double[dim];
        for (int j = 0; j < dim; j++) A[i][j] = 0.0;
    }

    double* Bv = new double[dim];
    double* Xv = new double[dim];

    A[0][0] = Sxx;        A[0][1] = Sx;
    A[1][0] = Sx;         A[1][1] = (double)n;

    Bv[0] = Sxy;
    Bv[1] = Sy;

    printf("=== SISTEMA 2x2 (Ecuaciones normales) ===\n");
    printf("[ %10.6f  %10.6f ] [ a ] = [ %10.6f ]\n", A[0][0], A[0][1], Bv[0]);
    printf("[ %10.6f  %10.6f ] [ b ]   [ %10.6f ]\n\n", A[1][0], A[1][1], Bv[1]);

    double det = 0.0;
    int status = gauss_solve_dynamic(dim, A, Bv, Xv, det);

    if (status != 0) {
        printf("Error: el sistema es singular o no se pudo resolver.\n");

        // liberar memoria
        for (int i = 0; i < dim; i++) delete[] A[i];
        delete[] A;
        delete[] Bv;
        delete[] Xv;
        return 1;
    }

    double a = Xv[0];
    double b = Xv[1];

    printf("\n=== RESULTADO ===\n");
    printf("a (pendiente)   = %.10f\n", a);
    printf("b (ordenada)    = %.10f\n", b);
    printf("Recta ajustada: y = %.10f * x + %.10f\n", a, b);
    printf("Determinante del sistema 2x2: %.10e\n", det);

    // (Opcional) residual del sistema 2x2 (no es el residual del ajuste a los datos)
    // double res = compute_residual_dynamic(dim, A, Xv, Bv);
    // printf("Residual del sistema (2x2): %.6e\n", res);

    // liberar memoria
    for (int i = 0; i < dim; i++) delete[] A[i];
    delete[] A;
    delete[] Bv;
    delete[] Xv;
    free(x);
    free(y);

    return 0;
}
