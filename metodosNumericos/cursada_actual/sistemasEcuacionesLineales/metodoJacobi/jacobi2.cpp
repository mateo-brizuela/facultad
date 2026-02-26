/*
    Resolución de sistemas lineales Ax=b usando el método iterativo de Jacobi
    Parámetro n: tamaño del sistema (matriz nxn)
*/
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#define n 3

void cargar(double matriz[n][n], double vector[n]);
void cargarVectorInicial(double xv[n]);
void leer(double matriz[n][n], double vector[n]);
void jacobi(double matriz[n][n], double vector[n], double xv[n]);

int main(int argc, char const *argv[])
{
    double matriz[n][n] , vector[n], xv[n];
    cargar(matriz, vector);
    cargarVectorInicial(xv);
    leer(matriz, vector);
    jacobi(matriz, vector, xv);

    return 0;
}

void cargar(double matriz[n][n], double vector[n]){
    printf("vamos a cargar la matriz\n");
    for ( int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Ingrese el elemento [%d][%d]: ",(i+1),(j+1));
            scanf("%lf",&matriz[i][j]);
        }
    }
    printf("\n");
    printf("vamos a cargar el vector independiente\n");
    for (int i = 0; i < n; i++)
    {
        printf("Ingrese el elemento b[%d]: ",i);
        scanf("%lf",&vector[i]);
    }

    printf("\n");
}

void cargarVectorInicial(double xv[n]){
    printf("vamos a cargar el vector inicial xv\n");
    for (int i = 0; i < n; i++)
    {
        printf("Ingrese el elemento xv[%d]: ",i);
        scanf("%lf",&xv[i]);
    }
    printf("\n");
}

void leer(double matriz[n][n], double vector[n]){
    printf("matriz:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2f\t",matriz[i][j]);
        }
        printf("|%.2f\n",vector[i]);
    }
    printf("\n");
}

void jacobi(double matriz[n][n], double vector[n], double xv[n]){
    // Validar si la matriz es diagonalmente dominante
    // (condición suficiente pero no necesaria para convergencia)
    bool dd = true;
    double suma = 0.0;
    
    for (int i = 0; i < n; i++)
    {
        suma = 0.0;
        // Sumar valores absolutos de elementos fuera de la diagonal
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                suma = suma + fabs(matriz[i][j]);
        }
        // Verificar si |a_ii| >= suma de |a_ij| para j != i
        if (fabs(matriz[i][i]) < suma)
            dd = false;
    }

    if (!dd)
        printf("ADVERTENCIA: la matriz no es diagonalmente dominante\n");

    // Inicializar arreglos y variables de control
    double xn[n];  // vector de solución en iteración actual
    for (int i = 0; i < n; i++)
        xn[i] = xv[i];  // copiar valores iniciales
    
    double errorV = 1000.0;  // error de iteración anterior
    double error = 0.0;      // error de iteración actual
    double tolerancia = 0.0; // tolerancia deseada
    int cifrasTolerancia = 0;
    int iter = 0;  // contador de iteraciones
    suma = 0.0;

    printf("ingrese la cantidad de cifras decimales de presicion: ");
    scanf("%d",&cifrasTolerancia);
    tolerancia = pow(10,-cifrasTolerancia);  // convertir cifras a tolerancia   

    // Bucle iterativo del método de Jacobi
    do
    {
        // Calcular nuevo valor para cada incógnita x_i
        for (int i = 0; i < n; i++)
        {
            suma = 0.0;
            // Sumar a_ij * x_j para j != i (usando valores anteriores xv)
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                    suma = suma + (matriz[i][j] * xv[j]);
            }
            
            // Verificar que elemento diagonal no sea cero
            if (matriz[i][i] == 0)
            {
                printf("error: hay un cero en la diagonal\n");
                exit(1);
            }
            
            // Fórmula de Jacobi: x_i^(k+1) = (b_i - suma) / a_ii
            xn[i] = (vector[i] - suma) / matriz[i][i];
        }

        // Calcular error: norma euclidiana de la diferencia entre iteraciones
        error = 0.0;
        for (int i = 0; i < n; i++)
            error = error + pow((xn[i]) - xv[i], 2);
        error = sqrt(error);

        // Verificar si el método diverge
        if (error > errorV)
        {
            printf("el metodo no converge\n");
            exit(1);
        }

        errorV = error;  // actualizar error anterior

        // Copiar nueva solución a vector anterior para siguiente iteración
        for (int i = 0; i < n; i++)
            xv[i] = xn[i];

        iter++;
        
    } while (error > tolerancia);  // repetir hasta alcanzar tolerancia

    printf("resultados: \n");
    printf("vector de incognitas: ");
    for (int i = 0; i < n; i++)
    {
        printf("x%d=%.2f    ",i+1,xn[i]);
    }
    printf("\niteraciones: %d\n"
            "error: %.9f",iter,error);
    printf("\n\n");
    
}
