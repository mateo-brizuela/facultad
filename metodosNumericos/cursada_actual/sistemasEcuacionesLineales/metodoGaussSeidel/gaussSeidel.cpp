#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#define n 4

void cargar(double matriz[n][n], double vector[n]);
void cargarVectorInicial(double xv[n]);
void leer(double matriz[n][n], double vector[n]);
void gSeidel(double matriz[n][n],double vector[n],double xv[n]);

int main(int argc, char const *argv[])
{
    double matriz[n][n] , vector[n], xv[n];
    cargar(matriz, vector);
    cargarVectorInicial(xv);
    leer(matriz, vector);
    gSeidel(matriz,vector,xv);

    return 0;
}

void cargar(double matriz[n][n], double vector[n]){
    printf("vamos a cargar la matriz\n");
    for ( int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Ingrese el elemento [%d][%d]: ",i+1,j+1);
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

void gSeidel(double matriz[n][n],double vector[n],double xv[n]){
    bool dd = true; // es un booleano para ver si la matriz es diagonalmente dominante 
    double suma = 0.0;
    // verificacion si la matriz es diagonalmente dominante
    for (int i = 0; i < n; i++)
    {
        suma = 0.0;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                suma = suma + fabs(matriz[i][j]);    
            }
        }
        if (fabs(matriz[i][i]) < suma)
        {
            dd = false;
        }
    }

    if (!dd)
    {
        printf("ADVERTENCIA: la matriz no es diagonalmente dominante\n");
    }

    // empezamos a iterar con el metodo gauss-seidel 
    double xn[n];
    for (int i = 0; i < n; i++) {
        xn[i] = xv[i];  // Inicializar xn con los valores iniciales
    }
    double errorV = 1000.0; // este es el error viejo
    double error = 0.0; // error nuevo
    double tolerancia = 0.0;
    int cifrasTolerancia = 0;
    int opcion = 0;
    int iter = 0; // cuenta la cantidad de iteraciones 
    suma = 0.0;

    printf("ingrese la cantidad de cifras decimales de presicion: ");
    scanf("%d",&cifrasTolerancia);
    tolerancia = pow(10,-cifrasTolerancia);   

    do
    {
        for (int i = 0; i < n; i++)
        {
            suma = 0.0;

            for (int j = 0; j < i; j++) // este bucle itera desde la primer columna hasta i
            {
                suma = suma + matriz[i][j] * xn[j]; // uso los valores nuevos ya calculados
            }

            for (int j = i+1; j < n; j++) // este bucle itera desde la columna i+1 hasta la ultima columna
            {
                suma  = suma + matriz[i][j] * xv[j]; // uso los valores viejos
            }

            if (matriz[i][i] == 0.0)
            {
                printf("error: hay un cero en la diagonal\n");
                exit(1);
            }
            
            xn[i] = (vector[i] - suma) / matriz[i][i];
        }
        

        // se calcula el error
        error = 0.0; // se reinicia el error
        for (int i = 0; i < n; i++)
        {
            error = error + pow((xn[i]) - xv[i],2);
        }
        error = sqrt(error);

        if (error > errorV)
        {
            printf("el metodo no converge\n");
            exit(1);
        }

        errorV = error;

        for (int i = 0; i < n; i++)
        {
            xv[i] = xn[i];
        }

        iter++;
        
    } while (error > tolerancia);

    printf("resultados: \n");
    printf("vector de incognitas: \n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d=%.2f\n",i+1,xn[i]);
    }
    printf("iteraciones: %d\n"
            "error: %.9f",iter,error);
    printf("\n\n");
    
}
