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
void cargarMatriz(double x[n], double y[n], double matriz[n][n]);
void leerMatriz(double matriz[n][n], double y[n]);

// funciones para resolver la matriz cargada
void gauss(double A[n][n], double B[n], double x[n]);

// funciones de interpolacion
void interpolar(double x[n], double a[n]);  // Cambio en parámetros
void mostrarPolinomio(double a[n]);         // Nueva función

int main(int argc, char const *argv[])
{
    double x[n];
    double y[n];
    double a[n]; // vector con los coeficientes del polinomio
    double matriz[n][n]; 

    printf("bienvenido al programa que usa la forma funcional de interpolacion!\n");
    cargarVector(x,y);
    cargarMatriz(x,y,matriz); 
    leerMatriz(matriz,y);
    gauss(matriz,y,a);
    interpolar(x,a);        // Cambio en llamada
    mostrarPolinomio(a);    // Nueva llamada

    return 0;
}

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
            printf("ingrese y[%d]: ",i);
            scanf("%lf",&y[i]);
        } else {
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
    
    // Resultados en ambas notaciones
    printf("=== RESULTADOS DEL SISTEMA ===\n");
    printf("Coeficientes del polinomio (notacion decimal):\n");
    for (int i = 0; i < n; i++) {
        printf("a%d = %.10f\n", i, x[i]);
    }
    
    printf("\nCoeficientes del polinomio (notacion cientifica):\n");
    for (int i = 0; i < n; i++) {
        printf("a%d = %.10e\n", i, x[i]);
    }
    
    printf("Determinante de A = %.10f\n", detA);
    printf("Intercambios realizados: %d\n\n", intercambios);
}

// FUNCIÓN INTERPOLAR MODIFICADA: permite múltiples aproximaciones
void interpolar(double x[n], double a[n]) {
    double xr = 0.0;    // valor a interpolar
    double suma = 0.0;  // acumulador del polinomio
    char continuar;     // control para continuar interpolando
    
    printf("=== INTERPOLACION DE VALORES ===\n");
    
    do {
        printf("Ingrese el valor x a interpolar: ");
        scanf("%lf", &xr);
        
        // Reiniciar acumulador para nueva evaluación
        suma = 0.0;
        
        // Evaluar el polinomio P(x) = a0 + a1*x + a2*x² + ... + an*x^n
        for (int i = 0; i < n; i++) {
            suma += a[i] * pow(xr, i);
        }
        
        // Mostrar resultados en ambas notaciones
        printf("\n=== RESULTADOS PARA x = %.6f ===\n", xr);
        printf("Aproximacion P(%.6f) [decimal]:    %.10f\n", xr, suma);
        printf("Aproximacion P(%.6f) [cientifica]: %.10e\n", xr, suma);
        
        // Mostrar cálculo término por término
        printf("\nCalculo termino por termino:\n");
        for (int i = 0; i < n; i++) {
            double termino = a[i] * pow(xr, i);
            printf("a%d * x^%d = %.6f * %.6f^%d = %.10f\n", 
                   i, i, a[i], xr, i, termino);
        }
        
        // Preguntar si desea interpolar otro valor
        printf("\n¿Desea interpolar otro valor? (s/n): ");
        scanf(" %c", &continuar);  // espacio antes de %c para ignorar saltos de línea
        
    } while (continuar == 's' || continuar == 'S');
}

// NUEVA FUNCIÓN: muestra el polinomio en formato para graficadora
void mostrarPolinomio(double a[n]) {
    printf("\n=== POLINOMIO INTERPOLANTE ===\n");
    printf("Grado del polinomio: %d\n", n-1);
    
    // Forma desarrollada (fácil lectura)
    printf("\nForma desarrollada (facil lectura):\n");
    printf("P(x) = ");
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("%.10f", a[i]);  // término constante
        } else {
            if (a[i] >= 0) {
                printf(" + %.10f*x", a[i]);
            } else {
                printf(" - %.10f*x", fabs(a[i]));
            }
            
            if (i > 1) {
                printf("^%d", i);
            }
        }
    }
    
    // Forma compacta para graficadoras
    printf("\n\nForma compacta para graficadoras:\n");
    printf("P(x) = ");
    for (int i = 0; i < n; i++) {
        printf("%.10f", a[i]);
        if (i > 0) {
            printf("*x");
            if (i > 1) {
                printf("^%d", i);
            }
        }
        if (i < n-1) {
            printf(" + ");
        }
    }
    
    printf("\n");
}