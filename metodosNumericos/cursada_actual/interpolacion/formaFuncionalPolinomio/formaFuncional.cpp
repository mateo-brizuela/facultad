#include <stdio.h>
#include <cmath>
#include <stdlib.h>

#define n   3          // tamaño del sistema (3x3)

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

    printf("bienvenido al programa que us ala forma funcional de interpolacion!\n");
    cargarVector(x,y);
    cargarMatriz(x,y,matriz); 
    leerMatriz(matriz,y);
    gauss(matriz,y,a);
    interpolar(matriz,y,a);

    return 0;
}

void cargarVector(double x[n], double y[n]){
    printf("vamos a cargar los datos: \n");

    for (int i = 0; i < n; i++)
    {
        printf("ingrese x%d: ",i);
        scanf("%lf",&x[i]);
        printf("ingrese y%d: ",i);
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
    leerMatriz(A,B);
    
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
