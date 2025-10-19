#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define n 6
#define MAX_ITER 10000

void cargar(double matriz[n][n], double vector[n]);
void leer(double matriz[n][n], double vector[n]);
void gSeidel(double matriz[n][n], double vector[n]);

int main(int argc, char const *argv[])
{
    double matriz[n][n], vector[n];
    cargar(matriz, vector);   // Se cargan los valores de A y b desde teclado
    leer(matriz, vector);     // Se muestra el sistema A|b
    gSeidel(matriz, vector);  // Se resuelve con el método de Gauss–Seidel (opcionalmente con relajación)
    return 0;
}

void cargar(double matriz[n][n], double vector[n]) {
    printf("=== CARGA DEL SISTEMA ===\n");
    
    // Lectura de la matriz A
    printf("\nCargando matriz A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("\nFila %d:\n", i+1);
        for (int j = 0; j < n; j++) {
            printf("  A[%d][%d]: ", i+1, j+1);
            scanf("%lf", &matriz[i][j]);   // %lf → lectura de double
        }
    }
    
    // Lectura del vector b
    printf("\nCargando vector b (%d elementos):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  b[%d]: ", i+1);
        scanf("%lf", &vector[i]);
    }
    printf("\n");
}

void leer(double matriz[n][n], double vector[n]) {
    printf("=== SISTEMA COMPLETO ===\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // %8.2f → imprime un número flotante
            //   8   = ancho mínimo del campo
            //  .2   = 2 decimales
            //   f   = formato decimal fijo
            printf("%8.2f ", matriz[i][j]);
        }
        printf(" | %8.2f\n", vector[i]);
    }
    printf("\n");
}

void gSeidel(double matriz[n][n], double vector[n]) {
    bool dd = true;
    double suma = 0.0;
    
    // Verificación de diagonal dominante (condición suficiente de convergencia)
    for (int i = 0; i < n; i++) {
        suma = 0.0;
        for (int j = 0; j < n; j++) {
            if (j != i) suma = suma + fabs(matriz[i][j]);    
        }
        if (fabs(matriz[i][i]) < suma) dd = false;
    }

    if (!dd) {
        printf("ADVERTENCIA: la matriz no es diagonalmente dominante\n");
        printf("La convergencia de Gauss-Seidel NO está garantizada\n\n");
    }

    // Factor de relajación (ω=1 → Gauss–Seidel clásico)
    double omega = 1.0;
    printf("¿Usar relajación? (1 = Sí, 0 = No): ");
    int usarRelajacion;
    scanf("%d", &usarRelajacion);
    
    if (usarRelajacion) {
        printf("Ingrese el factor de relajación ω (0 < ω < 2): ");
        scanf("%lf", &omega);
        if (omega <= 0 || omega >= 2) {
            printf("ω debe estar entre 0 y 2. Usando ω=1.0\n");
            omega = 1.0;
        }
    }

    // Variables del método
    double xn[n] = {1.0};   // valores nuevos (iteración actual)|| ESTE LO CAMBIO PARA VALORES INICIALES EN 1
    double xv[n] = {0.0};   // valores viejos (iteración anterior)
    double error = 0.0;
    double tolerancia = 0.0;
    int cifrasTolerancia = 0;
    int iter = 0;

    // Se pide la cantidad de cifras correctas deseadas
    printf("Ingrese la cantidad de cifras decimales de precision: ");
    scanf("%d", &cifrasTolerancia);
    tolerancia = pow(10, -cifrasTolerancia);

    printf("\n=== INICIANDO GAUSS-SEIDEL ===\n");
    // %.0e → notación científica con exponente, sin decimales
    printf("Configuración: ω=%.2f, tolerancia=%.0e, max_iter=%d\n\n", omega, tolerancia, MAX_ITER);

    do {
        // Actualización variable por variable
        for (int i = 0; i < n; i++) {
            suma = 0.0;

            // Se usan valores NUEVOS ya calculados en esta iteración
            for (int j = 0; j < i; j++) {
                suma += matriz[i][j] * xn[j];
            }
            
            // Se usan valores VIEJOS para los que aún no se actualizaron
            for (int j = i+1; j < n; j++) {
                suma += matriz[i][j] * xv[j];
            }

            if (fabs(matriz[i][i]) < 1e-15) {
                printf("Error: elemento diagonal cero o muy pequeño en A[%d][%d]\n", i+1, i+1);
                return;
            }
            
            // Fórmula de Gauss–Seidel con relajación
            double x_gs = (vector[i] - suma) / matriz[i][i];
            xn[i] = (1.0 - omega) * xv[i] + omega * x_gs;
            
            // Comprobación de NaN (divergencia numérica)
            if (std::isnan(xn[i])) {
                printf("¡DIVERGENCIA! Valor nan en iteración %d, variable x%d\n", iter, i+1);
                printf("El método no converge para esta matriz\n");
                
                // Mostrar valores obtenidos antes del error
                printf("\nValores calculados antes de la divergencia:\n");
                for (int k = 0; k < n; k++) {
                    printf("x%d = %.6f\n", k+1, xn[k]);
                }
                return;
            }
        }

        // Se calcula el error máximo entre iteraciones
        error = 0.0;
        for (int i = 0; i < n; i++) {
            if (std::isnan(xn[i]) || std::isnan(xv[i])) {
                printf("¡DIVERGENCIA! Valor nan detectado en iteración %d\n", iter);
                return;
            }
            error = fmax(error, fabs(xn[i] - xv[i]));
        }

        // Actualización del vector viejo
        for (int i = 0; i < n; i++) {
            xv[i] = xn[i];
        }

        iter++;

        // Mensaje de progreso cada 100 iteraciones
        if (iter % 100 == 0) {
            printf("Iteración %d: error = %.2e\n", iter, error);
        }
        
        if (iter >= MAX_ITER) {
            printf("¡ALERTA! Se alcanzó el límite de %d iteraciones\n", MAX_ITER);
            printf("Error actual: %.2e (tolerancia: %.0e)\n", error, tolerancia);
            break;
        }
        
    } while (error > tolerancia);

    // Resultados finales
    printf("\n=== RESULTADOS FINALES ===\n");
    printf("Iteraciones: %d\n", iter);
    // %.2e → notación científica con 2 decimales
    // %.10f → notación decimal fija con 10 decimales
    printf("Error final: %.2e  (en decimal: %.10f)\n", error, error);
    printf("Factor ω utilizado: %.2f\n", omega);
    
    if (iter >= MAX_ITER && error > tolerancia) {
        printf("ESTADO: No convergió dentro del límite de iteraciones\n");
    } else {
        printf("ESTADO: Convergencia exitosa\n");
    }
    
    // Impresión de la tabla de solución
    printf("\nSolución obtenida:\n");
    printf("%-8s %-20s %-15s\n", "Variable", "Notación científica", "Formato decimal");
    printf("%-8s %-20s %-15s\n", "-------", "-------------------", "---------------");
    
    for (int i = 0; i < n; i++) {
        // >>>> FORMATO DETALLADO <<<<
        // x%-7d     → "x" + número entero, ancho mínimo 7, alineado a la izquierda
        // %-20.6e   → número double en notación científica, 6 decimales, ancho 20, alineado a la izquierda
        // %-15.8f   → número double en notación decimal fijo, 8 decimales, ancho 15, alineado a la izquierda
        printf("x%-7d %-20.6e %-15.10f\n", i+1, xn[i], xn[i]);
    }
}
