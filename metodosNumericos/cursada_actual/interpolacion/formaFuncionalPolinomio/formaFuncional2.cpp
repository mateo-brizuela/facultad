#include <stdio.h>
#include <cmath>
#include <stdlib.h>

#define n   3          // tamaño del sistema (3x3)

// Función matemática para calcular y automáticamente a partir de x
double funcionMatematica(double x) {
    return x*x;  // Ejemplo: f(x) = x² (modificar según necesidad)
}

// funciones para cargar y leer los datos
void cargarVector(double x[n], double y[n]);
void leerVector(double x[n], double y[n]);

// funciones para armar y leer la matriz
void cargarMatriz(double x[n], double y[n], double matriz[n][n]); // arma la matriz para luego resolverla por gauss
void leerMatriz(double matriz[n][n], double y[n]);

// funciones para resolver la matriz cargada
void gauss(double A[n][n], double B[n], double x[n]);

// funciones de interpolacion
void interpolar(double matriz[n][n], double y[n], double a[n]);


int main(int argc, char const *argv[])
{
    double x[n];
    double y[n];
    double a[n]; // este es el vector con todas las incognitas
    double matriz[n][n];

    printf("bienvenido al programa que usa la forma funcional de interpolacion!\n");
    cargarVector(x,y);
    cargarMatriz(x,y,matriz); 
    leerMatriz(matriz,y);
    gauss(matriz,y,a);
    interpolar(matriz,y,a);

    return 0;
}

// MODIFICADA: Ahora permite elegir entre carga manual o automática
void cargarVector(double x[n], double y[n]){
    int opcion;
    
    printf("¿Como desea cargar los valores de y?\n");
    printf("1) Ingresar manualmente\n");
    printf("2) Calcular automaticamente con funcion matematica\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    
    printf("vamos a cargar los datos: \n");

    for (int i = 0; i < n; i++)
    {
        printf("ingrese x[%d]: ",i);
        scanf("%lf",&x[i]);
        
        if (opcion == 1) {
            // Carga manual de valores y
            printf("ingrese y[%d]: ",i);
            scanf("%lf",&y[i]);
        } else {
            // Carga automática usando función matemática
            y[i] = funcionMatematica(x[i]);
            printf("y[%d] calculado automaticamente: %.6f\n", i, y[i]);
        }
    }
    printf("vector ingresado: \n");
    leerVector(x,y);
}

void leerVector(double x[n], double y[n]){
    printf("x\t|\ty\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.2f\t|\t%.2f| indice: %d \n",x[i],y[i],i);
    }
    
}

void cargarMatriz(double x[n], double y[n], double matriz[n][n]){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = pow(x[i],j);
        }
    }
    
}

void leerMatriz(double matriz[n][n], double y[n]){
    printf("esta es la matriz cargada: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2f\t",matriz[i][j]);
        }
        printf("| %.2f\n",y[i]);
    }
    
}

// FUNCIÓN GAUSS MEJORADA
void gauss(double A[n][n], double B[n], double x[n]) {
    double ceroDef = pow(10, -2);
    double sum = 0.0;
    int intercambios = 0;
    
    // Eliminación gaussiana con pivoteo
    for (int i = 0; i < n; i++) {
        // Pivoteo parcial
        if (fabs(A[i][i]) < ceroDef) {
            int p = i;
            for (int l = i + 1; l < n; l++) {
                if (fabs(A[l][i]) > fabs(A[p][i])) {
                    p = l;
                }
            }
            
            if (p != i) {
                intercambios++;
                double aux;
                for (int m = 0; m < n; m++) {
                    aux = A[p][m];
                    A[p][m] = A[i][m];
                    A[i][m] = aux;
                }
                aux = B[p];
                B[p] = B[i];
                B[i] = aux;
            }
        }
        
        // Eliminación hacia adelante
        for (int j = i + 1; j < n; j++) {
            double factor = -A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] += A[i][k] * factor;
            }
            B[j] += B[i] * factor;
        }
    }
    
    printf("Matriz reducida:\n");
    leerMatriz(A, B);
    
    // Calcular determinante
    double prod = 1.0;
    for (int i = 0; i < n; i++) {
        prod *= A[i][i];
    }
    
    double detA = prod;
    if (intercambios % 2 == 1) {
        detA = -prod;
    }
    
    // Verificar si la matriz es singular
    if (fabs(prod) < ceroDef) {
        printf("Error: la matriz es singular\n");
        exit(1);
    }
    
    // Retrosustitución
    x[n-1] = B[n-1] / A[n-1][n-1];
    for (int i = n-2; i >= 0; i--) {
        sum = B[i];
        for (int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
    
    // Resultados
    printf("=== RESULTADOS ===\n");
    printf("Solución del sistema:\n");
    for (int i = 0; i < n; i++) {
        printf("a%d = %.10f\n", i, x[i]);
    }
    printf("Determinante de A = %.10f\n", detA);
    printf("Intercambios realizados: %d\n\n", intercambios);
}

void interpolar(double matriz[n][n], double y[n], double a[n]){
    double xr = 0.0; // es el valor a interpolar
    double suma = 0.0;

    printf("sistema resuelto, se procede con interpolacion\n");
    printf("ingrese el valor a interpolar: ");
    scanf("%lf",&xr);

    for (int i = 0; i < n; i++) // arma el polinomio y va aarmando la suma para la aproximacion
    {
        suma = suma + a[i] * pow(xr,i);
    }
    
    /* -------- Resultados -------- */
    printf("\nresultados:\n");

    printf("matriz tras gauss (triangular superior | y):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%10.6f ", matriz[i][j]);
        printf("| %10.6f\n", y[i]);
    }

    printf("\ncoeficientes a (a0..a%d):\n", n-1);
    for (int i = 0; i < n; ++i)
        printf("a[%d] = %.10f\n", i, a[i]);

    printf("\nvalor a interpolar xr: %.10f\n", xr);
    printf("aproximacion P(xr) ≈ %.10f\n", suma);
}