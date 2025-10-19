#include "splineCubicaSimple.h"
#include <stdio.h>

// Arma el sistema lineal para el spline cúbico natural
void armarMatrizSimple(double x[], double y[], int d, double matriz[][4*(4-1)], double vector[]) {
    int m = d - 1;
    int n = 4 * m;
    // Inicializar matriz y vector a cero
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) matriz[r][c] = 0.0;
        vector[r] = 0.0;
    }
    int row = 0;
    // 1) Condiciones de interpolación
    for (int k = 0; k < m; ++k) {
        int c = 4 * k;
        double xk = x[k], xk1 = x[k+1];
        // S_k(x_k) = y_k
        matriz[row][c]   = xk*xk*xk;
        matriz[row][c+1] = xk*xk;
        matriz[row][c+2] = xk;
        matriz[row][c+3] = 1.0;
        vector[row] = y[k];
        row++;
        // S_k(x_{k+1}) = y_{k+1}
        matriz[row][c]   = xk1*xk1*xk1;
        matriz[row][c+1] = xk1*xk1;
        matriz[row][c+2] = xk1;
        matriz[row][c+3] = 1.0;
        vector[row] = y[k+1];
        row++;
    }
    // 2) Continuidad de primeras derivadas
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);
        matriz[row][cL]   = 3 * xi * xi;
        matriz[row][cL+1] = 2 * xi;
        matriz[row][cL+2] = 1.0;
        matriz[row][cR]   = -3 * xi * xi;
        matriz[row][cR+1] = -2 * xi;
        matriz[row][cR+2] = -1.0;
        vector[row] = 0.0;
        row++;
    }
    // 3) Continuidad de segundas derivadas
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);
        matriz[row][cL]   = 6 * xi;
        matriz[row][cL+1] = 2.0;
        matriz[row][cR]   = -6 * xi;
        matriz[row][cR+1] = -2.0;
        vector[row] = 0.0;
        row++;
    }
    // 4) Condiciones de frontera naturales
    matriz[row][0] = 6 * x[0];
    matriz[row][1] = 2.0;
    vector[row] = 0.0;
    row++;
    int lastBlock = 4*(m-1);
    matriz[row][lastBlock]   = 6 * x[m];
    matriz[row][lastBlock+1] = 2.0;
    vector[row] = 0.0;
}

// Resuelve el sistema lineal Ax = B por Gauss simple
void gaussSimple(double A[][4*(4-1)], double B[], double x[], int n) {
    double prod = 1.0;
    double ceroDef = 1e-2;
    double sum = 0.0;
    // Eliminación hacia adelante
    for (int i = 0; i < n; i++) {
        if (A[i][i] == 0.0) {
            int p = i;
            for (int l = i + 1; l < n; l++) {
                if (A[l][i] != 0.0) {
                    p = l;
                    break;
                }
            }
            for (int u = 0; u < n; u++) {
                double aux = A[p][u];
                A[p][u] = A[i][u];
                A[i][u] = aux;
            }
            double aux = B[p];
            B[p] = B[i];
            B[i] = aux;
        }
        for (int j = i + 1; j < n; j++) {
            double factor = -A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] += A[i][k] * factor;
            }
            B[j] += B[i] * factor;
        }
    }
    for (int i = 0; i < n; i++) prod *= A[i][i];
    if (prod == 0.0) {
        printf("Error: la matriz tiene determinante cero\n");
        return;
    }
    x[n-1] = B[n-1] / A[n-1][n-1];
    for (int i = n-2; i >= 0; i--) {
        sum = B[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
}

// Evalúa el spline cúbico en los puntos x_interp[]
void aproximarSplineSimple(double x[], double coef[], int d, double x_interp[], double y_interp[], int n_interp) {
    int m = d - 1;
    for (int i = 0; i < n_interp; i++) {
        double xr = x_interp[i];
        int intervalo = -1;
        for (int k = 0; k < m; k++) {
            if (xr >= x[k] && xr <= x[k+1]) {
                intervalo = k;
                break;
            }
        }
        if (intervalo == -1) intervalo = m-1;
        int base = 4 * intervalo;
        double a = coef[base];
        double b = coef[base+1];
        double c = coef[base+2];
        double d0 = coef[base+3];
        y_interp[i] = a*xr*xr*xr + b*xr*xr + c*xr + d0;
    }
}