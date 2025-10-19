#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define d 3 // d es la cantidad de datos
#define n 4*(d-1) // n es la dimension de la matriz n*n
#define m d-1 // es la catidad de intervalos que hay 

//funciones para cargar y leer los datos
void cargarVector(double x[d], double y[d]);
void leerVector(double x[d], double y[d]);

//funciones para armar, leer y resolver la matriz
void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]);
void leerMatriz(double A[n][n], double B[n]);
void gauss(double A[n][n], double B[n], double x[n]); // EN ESTA FUNCION X ES EL VECTOR INCOGNITA


int main(int argc, char const *argv[])
{
    double x[d], y[d], matriz[n][n], vector[n], incognitas[n];
    cargarVector(x,y);
    armarMatriz(x,y,matriz,vector);
    gauss(matriz,vector,incognitas);



    return 0;
}

void cargarVector(double x[d], double y[d]){
    printf("vamos a cargar los datos: \n");

    for (int i = 0; i < d; i++)
    {
        printf("ingrese x[%d]: ",i);
        scanf("%lf",&x[i]);
        printf("ingrese y[%d]: ",i);
        scanf("%lf",&y[i]);
    }
    printf("vector ingresado: \n");
    leerVector(x,y);
}

void leerVector(double x[d], double y[d]){
    printf("x\t|\ty\n");
    for (int i = 0; i < d; i++)
    {
        printf("%.2f\t|\t%.2f| indice: %d \n",x[i],y[i],i);
    }
    
}


void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]) {
    // Limpiar matriz y vector
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) matriz[r][c] = 0.0;
        vector[r] = 0.0;
    }

    int row = 0; // Contador de filas, la usa comouna variable de toda la funcion entonces siempre esta actualizada

    // 1) Condiciones de interpolación (2 ecuaciones por tramo)
    for (int k = 0; k < m; ++k) {
        int c = 4*k; // Bloque del tramo k
        double xk = x[k], xk1 = x[k+1]; // asigna los x[k] y x[k+1] en una variable local

        // S_k(x_k) = y_k
        matriz[row][c]   = xk*xk*xk;
        matriz[row][c+1] = xk*xk;
        matriz[row][c+2] = xk;
        matriz[row][c+3] = 1.0;
        vector[row] = y[k];
        row++;

        // S_k(x_{k+1}) = y_{k+1}
        matriz[row][c]   = xk1*xk1*xk1;
        matriz[row][c+1] = xk1*xk1;
        matriz[row][c+2] = xk1;
        matriz[row][c+3] = 1.0;
        vector[row] = y[k+1];
        row++;
    }

    // 2) Continuidad de primeras derivadas en nodos interiores (m-1 ecuaciones)
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1]; // se asigna el punto de la continuidad en una variable local
        int cL = 4*k;     // Bloque izquierdo (tramo k)
        int cR = 4*(k+1); // Bloque derecho (tramo k+1)

        // Derivada de S_k(xi): 3*a_k*xi^2 + 2*b_k*xi + c_k
        matriz[row][cL]   = 3 * xi * xi;
        matriz[row][cL+1] = 2 * xi;
        matriz[row][cL+2] = 1.0;

        // Derivada de S_{k+1}(xi): -[3*a_{k+1}*xi^2 + 2*b_{k+1}*xi + c_{k+1}]
        matriz[row][cR]   = -3 * xi * xi;
        matriz[row][cR+1] = -2 * xi;
        matriz[row][cR+2] = -1.0;

        vector[row] = 0.0;
        row++;
    }

    // 3) Continuidad de segundas derivadas en nodos interiores (m-1 ecuaciones)
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k;
        int cR = 4*(k+1);

        // Segunda derivada de S_k(xi): 6*a_k*xi + 2*b_k
        matriz[row][cL]   = 6 * xi;
        matriz[row][cL+1] = 2.0;

        // Segunda derivada de S_{k+1}(xi): -[6*a_{k+1}*xi + 2*b_{k+1}]
        matriz[row][cR]   = -6 * xi;
        matriz[row][cR+1] = -2.0;

        vector[row] = 0.0;
        row++;
    }

    // 4) Condiciones de frontera naturales (2 ecuaciones)
    // Segunda derivada en x0: 6*a0*x0 + 2*b0 = 0
    matriz[row][0] = 6 * x[0];
    matriz[row][1] = 2.0;
    vector[row] = 0.0;
    row++;

    // Segunda derivada en x_{m}: 6*a_{m-1}*x_m + 2*b_{m-1} = 0
    int lastBlock = 4*(m-1);
    matriz[row][lastBlock]   = 6 * x[m];
    matriz[row][lastBlock+1] = 2.0;
    vector[row] = 0.0;

    leerMatriz(matriz,vector);
}


void leerMatriz(double A[n][n], double B[n]){
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

            for (int u = 0; u < n; u++)
            {
                aux = A[p][u]; // guarda la variable de la fila del pivoteo
                A[p][u] = A[i][u];
                A[i][u] = aux; // se hace el intercambio en cada elemento de las filas
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
        printf("x%d=%.6f    ",i+1,x[i]);
    }
    printf("\n\n");
}



