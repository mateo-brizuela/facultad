#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 8

/*
    documentacion del programa:
    A: es la matriz que se va a resolver mediante gauss y luego retrosustitucion
    B: es el vector que contiende todos los terminos dependientes
    x: es el vector que contiene todas las incognitas a resolver 

    gauss: es la funcion que resuelve la matriz reduciandola a gauss y escribe en el vector de incognitas 
    las soluciones 
*/

void cargar(double A[n][n], double B[n]);
void leer(double A[n][n], double B[n]);
void gauss(double A[n][n], double B[n], double x[n]);

int main(int argc, char const *argv[])
{
    double A[n][n] , B[n], x[n];
    cargar(A, B);
    leer(A, B);
    gauss(A,B,x);

    return 0;
}

void cargar(double A[n][n], double B[n]){
    printf("vamos a cargar la matriz\n");
    for ( int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("ingrese el elemento de la fila %d y la columna %d: ",(i+1),(j+1));
            scanf("%lf",&A[i][j]);
        }
    }
    printf("\n");
    printf("vamos a cargar el vector independiente\n");
    for (int i = 0; i < n; i++)
    {
        printf("ingrese el el elemento b%d: ",i);
        scanf("%lf",&B[i]);
    }

    printf("\n");
}

void leer(double A[n][n], double B[n]){
    printf("matriz:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2f\t",A[i][j]);
        }
        printf("|%.2f\n",B[i]);
    }
    printf("\n");
}

void gauss(double A[n][n],double B[n], double x[n]){
    /* parametros solicitados:
    A: es la matriz que se va a despejar
    B: es el vector que contiene todos los terminos dependientes
    x: es el vector que contiene todas las incoginitas, quese van a resolver 
    ceroDef: ES MUY IMPORTANTE, PARA DEFINI QUE VA A CONSIDERAR CERO EL PROGRAMA
    */ 
    
    double prod = 1.0;
    double ceroDef =  pow(10,-2); // es la variable que se va a usar para comparar con cero o una aprox
    double sum = 0.0; // es una variable para hacer las sumas en la retrosustitucion

    // reduccion a gauss de la matriz
    for (int i = 0; i < n; i++) // el bucle itera por todas las filas menos la ultima porque la ultima no es necesario reduccion
    {
        // metodo de pivoteo
        if (fabs(A[i][i]) < ceroDef)
        {
            int p = i; // variable que guarda el indice de la fila a la que se hace el pivoteo
            double aux;
            for (int l = i + 1; l < n; l++)
            {
                if (fabs(A[l][i]) > fabs(A[p][i])) // recorre desde la fila de abajo de i hasta la ultima
                {
                    p = l;
                }
            }

            for (int m = 0; m < n; m++)
            {
                aux = A[p][m]; // guarda la variable de la fila del pivoteo
                A[p][m] = A[i][m];
                A[i][m] = aux; // se hace el intercambio en cada elemento de las filas
            }

            aux = B[p];
            B[p] = B[i];
            B[i] = aux;
        }
        

        for (int j = i + 1; j < n; j++) // este indice va desde la fila de abajo de i hasta la ultima fila, para ir haciendo todo cero
        {
            double factor = -((A[j][i])/A[i][i]);

            for (int k = i; k < n; k++) // este indice va recorriendo todas las columnas de la fila j aplicando la operacion matricial 
            {
                A[j][k] = A[j][k] + (A[i][k] * factor); // se hace la suma a la fila j la fila i multiplicada por el factor 
            }
            B[j] = B[j] + (B[i]*factor);
            
        }
    }

    printf("la matriz reducida en la forma gauss es la siguiente:\n");
    leer(A,B);
    
    // revisamos que el determinante de la matriz no sea cero
    for (int i = 0; i < n; i++)
    {
        prod = prod * (A[i][i]);
    }
    if (prod == 0)
    {
        printf("error: la matriz tiene determinante cero\n");
        exit(1);
    }

    // retrosustitucion
    x[n-1] = (B[n-1])/(A[n-1][n-1]); // definimos la incognita numero n(la ultima)
    for (int i = (n-1); i >= 0; i--) // itera desde la penultima fila hasta la primera haciendo la retrosustitucion 
    {
        sum = B[i];
        for (int j = i + 1; j < n; j++) // el buble itera desde la primera columna al lado dela diagonal hasta la
        // ultima columna, ya que el elemento de la diagonal divide, no multiplica
        {
            sum = sum - ((A[i][j]) * x[j]);
        }
        sum = sum/(A[i][i]);
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
