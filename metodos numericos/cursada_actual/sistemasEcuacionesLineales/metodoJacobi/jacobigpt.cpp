#include <stdbool.h>
#include <math.h>

#define EPS 1e-12
#define MAX_ITER 100000

void jacobi(double matriz[n][n], double vector[n]){
    // 1) Chequeo de dominancia diagonal (opcional, solo warning)
    bool dd = true;
    for (int i = 0; i < n; i++) {
        double suma_abs = 0.0;
        for (int j = 0; j < n; j++) if (j != i) suma_abs += fabs(matriz[i][j]);
        if (!(fabs(matriz[i][i]) > suma_abs + EPS)) dd = false;
    }
    if (!dd) {
        printf("ADVERTENCIA: la matriz NO es estrictamente diagonalmente dominante; Jacobi puede no converger.\n");
    }

    // 2) Inicializaciones
    double xn[n] = {0};   // x nuevo
    double xv[n] = {0};   // x viejo
    double error = INFINITY, errorV = INFINITY;
    int cifras; 
    printf("Ingrese la cantidad de cifras decimales de precision: ");
    scanf("%d", &cifras);
    double tolerancia = pow(10.0, -cifras);

    // 3) Iteraciones Jacobi
    int iter = 0;
    do {
        // calcular xn usando SOLO xv
        for (int i = 0; i < n; i++) {
            if (fabs(matriz[i][i]) < EPS) {
                fprintf(stderr, "Pivote ~0 en fila %d. Reordene filas o use pivoteo.\n", i+1);
                exit(1);
            }
            double suma = 0.0;                      // <-- reiniciar por fila
            for (int j = 0; j < n; j++) {
                if (j != i) suma += matriz[i][j] * xv[j];
            }
            xn[i] = (vector[i] - suma) / matriz[i][i];
        }

        // error entre iteraciones (norma infinito)
        error = 0.0;                                 // <-- reiniciar por iteración
        for (int i = 0; i < n; i++) {
            double diff = fabs(xn[i] - xv[i]);
            if (diff > error) error = diff;
        }

        if (error > errorV + 1e-16) {               // leve margen numérico
            printf("El método parece no converger (error creciente).\n");
            break;
        }
        errorV = error;

        // pasar xn -> xv
        for (int i = 0; i < n; i++) xv[i] = xn[i];

        iter++;
        if (iter >= MAX_ITER) {
            printf("No convergio en %d iteraciones (error=%.3e).\n", MAX_ITER, error);
            break;
        }
    } while (error > tolerancia);

    // 4) Resultado
    if (error <= tolerancia)
        printf("Convergio en %d iteraciones (error=%.3e).\n", iter, error);

    printf("Resultados:\nVector de incógnitas: ");
    for (int i = 0; i < n; i++) printf("x%d=%.6f  ", i+1, xn[i]);
    printf("\n\n");
}
    