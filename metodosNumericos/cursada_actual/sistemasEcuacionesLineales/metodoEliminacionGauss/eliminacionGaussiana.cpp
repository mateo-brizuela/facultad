#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 3

void cargar(double matriz[n][n], double vector[n]);
void leer(double matriz[n][n], double vector[n]);
void gauss(double matriz[n][n], double vector[n]);

int main(int argc, char const *argv[])
{
    double matriz[n][n] , vector[n];
    cargar(matriz, vector);
    leer(matriz, vector);
    gauss(matriz,vector);

    return 0;
}

void cargar(double matriz[n][n], double vector[n]){
    printf("vamos a cargar la matriz\n");
    for ( int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("ingrese el elemento de la fila %d y la columna %d: ",(i+1),(j+1));
            scanf("%lf",&matriz[i][j]);
        }
    }
    printf("\n");
    printf("vamos a cargar el vector independiente\n");
    for (int i = 0; i < n; i++)
    {
        printf("ingrese el el elemento b%d: ",i);
        scanf("%lf",&vector[i]);
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

void gauss(double matriz[n][n],double vector[n]){
    double prod = 1.0;
    double x[n]; // es el vector con todas las incognitas
    double sum = 0.0; // es una variable para hacer las sumas en la retrosustitucion

    // reduccion a gauss de la matriz
    for (int i = 0; i < n; i++) // el bucle itera por todas las filas menos la ultima porque la ultima no es necesario reduccion
    {

        for (int j = i + 1; j < n; j++) // este indice va desde la fila de abajo de i hasta la ultima fila, para ir haciendo todo cero
        {
            double factor = -((matriz[j][i])/matriz[i][i]);

            for (int k = i; k < n; k++) // este indice va recorriendo todas las columnas de la fila j aplicando la operacion matricial 
            {
                matriz[j][k] = matriz[j][k] + (matriz[i][k] * factor); // se hace la suma a la fila j la fila i multiplicada por el factor 
            }
            vector[j] = vector[j] + (vector[i]*factor);
            
        }
    }

    printf("la matriz reducida en la forma gauss es la siguiente:\n");
    leer(matriz,vector);
    
    // revisamos que el determinante de la matriz no sea cero
    for (int i = 0; i < n; i++)
    {
        prod = prod * (matriz[i][i]);
    }
    if (prod == 0)
    {
        printf("error: la matriz tiene determinante cero\n");
        exit(1);
    }

    // retrosustitucion
    x[n-1] = (vector[n-1])/(matriz[n-1][n-1]); // definimos la incognita numero n(la ultima)
    for (int i = (n-1); i >= 0; i--) // itera desde la penultima fila hasta la primera haciendo la retrosustitucion 
    {
        sum = vector[i];
        for (int j = i + 1; j < n; j++)
        {
            sum = sum - ((matriz[i][j]) * x[j]);
        }
        sum = sum/(matriz[i][i]);
        x[i] = sum;
    }
    
    printf("resultados: \n");
    printf("vector de incognitas: ");
    for (int i = 0; i < n; i++)
    {
        printf("x%d=%.2f    ",i+1,x[i]);
    }
    printf("\n\n");
}
