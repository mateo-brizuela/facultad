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


int main(int argc, char const *argv[])
{
    double x[d], y[d], matriz[n][n], vector[n];
    cargarVector(x,y);
    armarMatriz(x,y,matriz,vector);



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


void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]){

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) matriz[r][c] = 0.0;
        vector[r] = 0.0;
    }

    for (int k = 0; k < m; k++) // recorre las primeras m filas correspondiente a la cantidad de segmentos
    {
        for (int j = 0; j < 4; j++) // esto recorre 4 veces por los exponentes cubicos
        {
            matriz[2*k][(4*k) + j] = pow(x[k],3-j); // la fila es 2k porque se cargan de 2 en 2 y solo cambia la xk a xk+1
            matriz[(2*k) + 1][(4*k) + j] = pow(x[k+1],3-j);
        }
        vector[2*k] = y[k]; // a cada fila se le carga su termino dependiente correspondiente 
        vector[(2*k)+1] = y[k+1];
    }

    for (int i = 2*m; i <= (3*m)-2 ; i++) //se repite hasta completar la seccion de derivadas primeras continuas
    {
        int g = i - 2*m; // k cuenta desde 0 hasta n-2 por el buble en el que esta, muy util para definir las columnas
        for (int j = 0; j < 3; j++) // se repite 3 veces porque se va reduciendo  el exponente desde 2 a 0(2 1 0)
        {
            printf("DEBUG S': fila=%d g=%d xi=%.6f\n", i, g, x[g+1]);

            matriz[i][(4*g) + j] = (3-j)* pow(x[g+1],2-j);
            matriz[i][4*(g+1) + j] = -(3-j)* pow(x[g+1],2-j);
        }
        vector[i] = 0;
    }
    

    /*

    for (int i = 2*n; i < (3*n)-2; i++)
    {
        for (int k = 0; k < n-2; k++)
        {
            for (int j = 0; j < 2; j++)
            {
                matriz[i][(4*k) + j] = (3-j) * pow(x[k+1],2-j);
                matriz[i][4*(k+1)+j] = -(3-j) * pow(x[k+1],2-j);
            }
        }
        vector[i] = 0;
    }
    
    for (int i = (3*n)-1; i < (4*n)-3; i++)
    {
        for (int k = 0; k < n-2; k++)
        {
            matriz[i][4*k] = 3*x[k+1];
            matriz[i][4*k+1] = 1;
            matriz[i][4*k+4] = -3*x[k+1];
            matriz[i][4*k+5] = -1;
        }
        vector[i] = 0;
    }

    // ultimas dos ecuaciones
    matriz[4*n-2][0] = 3*x[0];
    matriz[4*n-2][1] = 1;
    matriz[4*n-1][4*n-4] = 3*x[n];
    matriz[4*n-1][4*n-3] = 1;
    vector[4*n-2] = 0;
    vector[4*n-1] = 0;

*/
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
