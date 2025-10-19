#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define n 5 // cantidad de datos con los que vamos a trabajar 
#define p 3 // IMPORTANTE: definir el grado del polinomio antes de ejecutar el programa 

// Función matemática para cálculo automático de y
double funcionMatematica(double x) {
    return x*x;  // Ejemplo: f(x) = x² (modificar según necesidad)
}

// funciones para cargar y leer los datos
void cargarVector(double x[n], double y[n]);
void leerVector(double x[n], double y[n]);

// funcion para armar la matriz, leerla, y resolverla
void armarMatriz(double x[n], double y[n], double matriz[p][p], double vector[p]);
void leerMatriz(double A[p][p], double B[p]);
void gauss(double A[p][p], double B[p], double x[p]);

// Nuevas funciones para Gauss-Seidel y mostrar resultados
void gauss_seidel(double A[p][p], double B[p], double x[p], int max_iter, double tol);
void mostrarPolinomio(double coeficientes[p]);
void interpolarPolinomio(double coeficientes[p]);

int main(int argc, char const *argv[])
{
    double x[n], y[n], matriz[p][p], vector[p], incognitas[p] = {0};
    int metodo;
    
    if (n < p) {
        printf("Error: no hay datos(n=%d) suficientes para el grado del polinomio(p=%d)\n", n, p);
        printf("Se necesitan al menos p+1 puntos de datos\n");
        exit(1);
    }
    
    cargarVector(x, y);
    armarMatriz(x, y, matriz, vector);
    
    printf("Seleccione el metodo de resolucion:\n");
    printf("1) Eliminacion Gaussiana\n");
    printf("2) Gauss-Seidel\n");
    printf("Opcion: ");
    scanf("%d", &metodo);
    
    if (metodo == 1) {
        gauss(matriz, vector, incognitas);
    } else {
        gauss_seidel(matriz, vector, incognitas, 1000, 1e-6);
    }
    
    mostrarPolinomio(incognitas);
    interpolarPolinomio(incognitas);
    
    return 0;
}

void cargarVector(double x[n], double y[n]){
    int opcion;
    
    printf("¿Como desea cargar los valores de y?\n");
    printf("1) Ingresar manualmente\n");
    printf("2) Calcular automaticamente con funcion matematica\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    
    printf("Vamos a cargar %d puntos de datos:\n", n);

    for (int i = 0; i < n; i++) {
        printf("Ingrese x[%d]: ", i);
        scanf("%lf", &x[i]);
        
        if (opcion == 1) {
            printf("Ingrese y[%d]: ", i);
            scanf("%lf", &y[i]);
        } else {
            y[i] = funcionMatematica(x[i]);
            printf("y[%d] calculado automaticamente: %.6f\n", i, y[i]);
        }
    }
    printf("Datos ingresados: \n");
    leerVector(x, y);
}

void leerVector(double x[n], double y[n]){
    printf("x\t|\ty\n");
    printf("----------------\n");
    for (int i = 0; i < n; i++) {
        printf("%.4f\t|\t%.4f | indice: %d \n", x[i], y[i], i);
    }
    printf("\n");
}

void armarMatriz(double x[n], double y[n], double matriz[p][p], double vector[p]){
    // Construye el sistema de ecuaciones normales para regresión polinomial
    for (int l = 0; l < p; l++) {
        double sumaxy = 0.0;
        
        // Calcula el término del vector independiente: Σ(x_i^l * y_i)
        for (int i = 0; i < n; i++) {
            sumaxy += pow(x[i], l) * y[i];
        }
        vector[l] = sumaxy;
        
        // Calcula los términos de la matriz: Σ(x_i^(l+m))
        for (int m = 0; m < p; m++) {
            double sumax = 0.0;
            for (int i = 0; i < n; i++) {
                sumax += pow(x[i], l + m);
            }
            matriz[l][m] = sumax;
        }
    }
    
    printf("Sistema de ecuaciones normales para regresion polinomial:\n");
    leerMatriz(matriz, vector);
}

void leerMatriz(double A[p][p], double B[p]){
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            printf("%12.4f ", A[i][j]);
        }
        printf("| %12.4f\n", B[i]);
    }
    printf("\n");
}

void gauss(double A[p][p], double B[p], double x[p]){
    double ceroDef = 1e-10;
    double sum = 0.0;
    int intercambios = 0;

    // Eliminación gaussiana con pivoteo
    for (int i = 0; i < p; i++) {
        // Pivoteo parcial
        if (fabs(A[i][i]) < ceroDef) {
            int piv = i;
            for (int l = i + 1; l < p; l++) {
                if (fabs(A[l][i]) > fabs(A[piv][i])) {
                    piv = l;
                }
            }

            if (piv != i) {
                intercambios++;
                for (int m = 0; m < p; m++) {
                    double aux = A[piv][m];
                    A[piv][m] = A[i][m];
                    A[i][m] = aux;
                }
                double aux = B[piv];
                B[piv] = B[i];
                B[i] = aux;
            }
        }

        // Eliminación
        for (int j = i + 1; j < p; j++) {
            double factor = -A[j][i] / A[i][i];
            for (int k = i; k < p; k++) {
                A[j][k] += A[i][k] * factor;
            }
            B[j] += B[i] * factor;
        }
    }

    printf("Matriz triangular superior:\n");
    leerMatriz(A, B);
    
    // Retrosustitución
    x[p-1] = B[p-1] / A[p-1][p-1];
    for (int i = p-2; i >= 0; i--) {
        sum = B[i];
        for (int j = i + 1; j < p; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
    
    // Resultados en ambas notaciones
    printf("=== COEFICIENTES DEL POLINOMIO (GAUSS) ===\n");
    printf("Notacion decimal:\n");
    for (int i = 0; i < p; i++) {
        printf("a%d = %.10f\n", i, x[i]);
    }
    
    printf("\nNotacion cientifica:\n");
    for (int i = 0; i < p; i++) {
        printf("a%d = %.10e\n", i, x[i]);
    }
    printf("Intercambios realizados: %d\n\n", intercambios);
}

// MÉTODO DE GAUSS-SEIDEL MEJORADO
void gauss_seidel(double A[p][p], double B[p], double x[p], int max_iter, double tol) {
    double x_anterior[p];
    int iter;
    double error;
    
    printf("Resolviendo por Gauss-Seidel (max_iter=%d, tol=%.0e)\n", max_iter, tol);
    
    // Verificar diagonal dominante
    for (int i = 0; i < p; i++) {
        double sum = 0.0;
        for (int j = 0; j < p; j++) {
            if (j != i) sum += fabs(A[i][j]);
        }
        if (fabs(A[i][i]) <= sum) {
            printf("Advertencia: La matriz puede no ser diagonal dominante en fila %d\n", i);
        }
    }
    
    // Iteraciones de Gauss-Seidel
    for (iter = 0; iter < max_iter; iter++) {
        // Guardar valores anteriores
        for (int i = 0; i < p; i++) {
            x_anterior[i] = x[i];
        }
        
        // Actualizar cada variable
        for (int i = 0; i < p; i++) {
            double sum = B[i];
            for (int j = 0; j < p; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            x[i] = sum / A[i][i];
        }
        
        // Calcular error máximo
        error = 0.0;
        for (int i = 0; i < p; i++) {
            double diff = fabs(x[i] - x_anterior[i]);
            if (diff > error) error = diff;
        }
        
        // Mostrar progreso cada 50 iteraciones
        if (iter % 50 == 0) {
            printf("Iteracion %d: error = %.10e\n", iter, error);
        }
        
        // Verificar convergencia
        if (error < tol) {
            break;
        }
    }
    
    printf("=== COEFICIENTES DEL POLINOMIO (GAUSS-SEIDEL) ===\n");
    printf("Iteraciones realizadas: %d\n", iter);
    printf("Error final: %.10e\n", error);
    
    printf("\nNotacion decimal:\n");
    for (int i = 0; i < p; i++) {
        printf("a%d = %.10f\n", i, x[i]);
    }
    
    printf("\nNotacion cientifica:\n");
    for (int i = 0; i < p; i++) {
        printf("a%d = %.10e\n", i, x[i]);
    }
    printf("\n");
}

void mostrarPolinomio(double coeficientes[p]) {
    printf("=== POLINOMIO DE REGRESION ===\n");
    printf("Grado del polinomio: %d\n", p-1);
    
    // Forma matemática
    printf("\nForma matematica:\n");
    printf("P(x) = ");
    for (int i = 0; i < p; i++) {
        if (i == 0) {
            printf("%.10f", coeficientes[i]);
        } else {
            if (coeficientes[i] >= 0) {
                printf(" + %.10f", coeficientes[i]);
            } else {
                printf(" - %.10f", fabs(coeficientes[i]));
            }
            printf("*x");
            if (i > 1) printf("^%d", i);
        }
    }
    
    // Forma para graficadoras
    printf("\n\nForma para graficadoras:\n");
    printf("y = ");
    for (int i = p-1; i >= 0; i--) {
        printf("%.10f", coeficientes[i]);
        if (i > 0) {
            printf("*x");
            if (i > 1) printf("^%d", i);
        }
        if (i > 0) printf(" + ");
    }
    
    // Forma para Python/Excel
    printf("\n\nForma para Python/Excel:\n");
    printf("f(x) = ");
    for (int i = 0; i < p; i++) {
        printf("%.10f", coeficientes[i]);
        if (i > 0) {
            printf("*x**%d", i);
        }
        if (i < p-1) printf(" + ");
    }
    printf("\n\n");
}

void interpolarPolinomio(double coeficientes[p]) {
    double xr, resultado;
    char continuar;
    
    printf("=== INTERPOLACION CON EL POLINOMIO ===\n");
    
    do {
        printf("Ingrese el valor x a evaluar: ");
        scanf("%lf", &xr);
        
        resultado = 0.0;
        for (int i = 0; i < p; i++) {
            resultado += coeficientes[i] * pow(xr, i);
        }
        
        printf("\nResultados para x = %.6f:\n", xr);
        printf("Notacion decimal:    P(%.6f) = %.10f\n", xr, resultado);
        printf("Notacion cientifica: P(%.6f) = %.10e\n", xr, resultado);
        
        printf("\n¿Evaluar otro punto? (s/n): ");
        scanf(" %c", &continuar);
        
    } while (continuar == 's' || continuar == 'S');
}