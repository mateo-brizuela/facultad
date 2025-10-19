#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define n 5 // cantidad de datos con los que vamos a trabajar 
#define p 3 // INPORTANTE: definir el grado del polinomio antes de ejecutar el programa 

// funciones para cargar y leer los datos
void cargarVector(double x[n], double y[n]);
void leerVector(double x[n], double y[n]);

// funcion para armar la matriz, leerla, y resolverla
void armarMatriz(double x[n], double y[n], double matriz[p][p],double vector[p]);
void leerMatriz(double A[p][p], double B[p]);
void gauss(double A[p][p], double B[p], double x[p]);



int main(int argc, char const *argv[])
{
    double x[n],y[n], matriz[p][p], vector[p], incognitas[p] = {0};
    if (n+1 < p)
    {
        printf("advertencia: no hay datos(n) suficientes para definir la matriz(p)\n");
        exit(1);
    }
    
    cargarVector(x,y);
    armarMatriz(x,y,matriz,vector);
    gauss(matriz,vector,incognitas);


    
    return 0;
}

void cargarVector(double x[n], double y[n]){
    printf("vamos a cargar los datos: \n");

    for (int i = 0; i < n; i++)
    {
        printf("ingrese x[%d]: ",i);
        scanf("%lf",&x[i]);
        printf("ingrese y[%d]: ",i);
        scanf("%lf",&y[i]);
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

void armarMatriz(double x[n], double y[n], double matriz[p][p],double vector[p]){
    // esta funcion arma toda la matriz teniendo en cuenta los datos ingresados y el grado del polinomio
    for (int l = 0; l < p; l++) // recorre todas las filas de la matriz
    {
        double sumaxy = 0.0; // lo usamos para sumar todos los x y lo elevamos a la l para hacer 
        // el vector de variables independientes

        for (int i = 0; i < n; i++) // recorre todas las variables x sumandolas y elevandolas a la l y multiplica por yi
        {
            sumaxy = sumaxy + pow(x[i],l)*y[i];
        }
        vector[l] = sumaxy;

        for (int m = 0; m < p; m++) // recorre todas las colunas de la matriz
        {
            double sumax = 0.0;
            for (int i = 0; i < n; i++) // hace la suma de todas las x y las eleva respecto su posicion en la matriz
            // hay un patron que se repite en la regresion polinomica por eso se puede hacer esto 
            {
                sumax = sumax + pow(x[i],l+m);
            }
            matriz[l][m] = sumax;
        }
    }
    // aca la matriz ya esta armada
    printf("matriz resultante: \n");
    leerMatriz(matriz,vector);

}

void leerMatriz(double A[p][p], double B[p]){
    printf("matriz:\n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {
            printf("%.2f\t",A[i][j]);
        }
        printf("|%.2f\n",B[i]);
    }
    printf("\n");
}

void gauss(double A[p][p],double B[p], double x[p]){
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
    for (int i = 0; i < p; i++) // el bucle itera por todas las filas menos la ultima porque la ultima no es necesario reduccion
    {
        // metodo de pivoteo
        if (fabs(A[i][i]) < ceroDef)
        {
            int piv = i; // variable que guarda el indice de la fila a la que se hace el pivoteo
            double aux;
            for (int l = i + 1; l < p; l++)
            {
                if (fabs(A[l][i]) > fabs(A[piv][i])) // recorre desde la fila de abajo de i hasta la ultima
                {
                    piv = l;
                }
            }

            for (int m = 0; m < p; m++)
            {
                aux = A[piv][m]; // guarda la variable de la fila del pivoteo
                A[piv][m] = A[i][m];
                A[i][m] = aux; // se hace el intercambio en cada elemento de las filas
            }

            aux = B[piv];
            B[piv] = B[i];
            B[i] = aux;
        }
        

        for (int j = i + 1; j < p; j++) // este indice va desde la fila de abajo de i hasta la ultima fila, para ir haciendo todo cero
        {
            double factor = -((A[j][i])/A[i][i]);

            for (int k = i; k < p; k++) // este indice va recorriendo todas las columnas de la fila j aplicando la operacion matricial 
            {
                A[j][k] = A[j][k] + (A[i][k] * factor); // se hace la suma a la fila j la fila i multiplicada por el factor 
            }
            B[j] = B[j] + (B[i]*factor);
            
        }
    }

    printf("la matriz reducida en la forma gauss es la siguiente:\n");
    leerMatriz(A,B);
    
    // revisamos que el determinante de la matriz no sea cero
    for (int i = 0; i < p; i++)
    {
        prod = prod * (A[i][i]);
    }
    if (prod == 0)
    {
        printf("error: la matriz tiene determinante cero\n");
        exit(1);
    }

    // retrosustitucion
    x[p-1] = (B[p-1])/(A[p-1][p-1]); // definimos la incognita numero n(la ultima)
    for (int i = (p-1); i >= 0; i--) // itera desde la penultima fila hasta la primera haciendo la retrosustitucion 
    {
        sum = B[i];
        for (int j = i + 1; j < p; j++) // el buble itera desde la primera columna al lado dela diagonal hasta la
        // ultima columna, ya que el elemento de la diagonal divide, no multiplica
        {
            sum = sum - ((A[i][j]) * x[j]);
        }
        sum = sum/(A[i][i]);
        x[i] = sum;
    }
    
    printf("resultados: \n");
    printf("vector de incognitas: ");
    for (int i = 0; i < p; i++)
    {
        printf("x%d=%.2f    ",i+1,x[i]);
    }
    printf("\n\n");
}

