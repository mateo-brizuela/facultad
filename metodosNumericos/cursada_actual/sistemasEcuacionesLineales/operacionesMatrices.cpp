#include <stdio.h>
#include <stdlib.h>   // malloc, free

int main(void) {
    int n;
    printf("Ingrese dimension del sistema (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) { puts("n invalido"); return 1; }

    // matriz aumentada: A | b  =>  n x (n+1)
    double **M = (double**)malloc(n * sizeof *M);
    if (!M) { puts("Sin memoria"); return 1; }
    for (int i = 0; i < n; ++i) {
        M[i] = (double*)malloc((n + 1) * sizeof **M);
        if (!M[i]) { puts("Sin memoria"); return 1; }
    }

    printf("Ingrese la matriz aumentada fila por fila (n*(n+1) valores):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (scanf("%lf", &M[i][j]) != 1) { puts("Entrada invalida"); return 1; }
        }
    }

    printf("\nMatriz aumentada [A|b]:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            printf("%10.4f ", M[i][j]);
        }
        putchar('\n');
    }

    // liberar
    for (int i = 0; i < n; ++i) free(M[i]);
    free(M);
    return 0;
}
