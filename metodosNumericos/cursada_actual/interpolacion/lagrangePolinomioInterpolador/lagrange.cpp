#include <stdio.h>
#include <cstdlib>
#include <cmath>

#define n 3

double funcion(double variable);
void cargarVector(double x[n], double y[n]);
void leerVector(double x[n], double y[n]);
void lagrange(double x[n], double y[n]);

int main(int argc, char const *argv[])
{
    double x[n], y[n];
    cargarVector(x,y);
    leerVector(x,y);
    lagrange(x,y);
    return 0;
}

void cargarVector(double x[n], double y[n]){
    // cargamos el vector de forma manual por ahora
    printf("cargando el vector\n");
    for (int i = 0; i < n; i++)
    {
        printf("ingrese x%d: ",i);
        scanf("%lf",&x[i]);
        y[i] = funcion(x[i]);
    }
    
}

void leerVector(double x[n], double y[n]){
    printf("x\t|\ty\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.2f\t|\t%.2f| indice: %d \n",x[i],y[i],i);
    }
    
}

double funcion(double variable){
    return variable + (2/variable);
}

void lagrange(double x[n], double y[n]){
    // declaracion de variables locales 
    double suma = 0.0; // lo usamos para ir haciendo la suma de todos los terminos del polinomio 
    double xr = 0.0; // esta es la x la cual queremos aproximar su valor en y

    // pedimos el valor que se debe aproximar por interpolacion
    printf("ingrese el valor que quiere aproximar por interpolacion: ");
    scanf("%lf",&xr);

    printf("calculando lagrange\n");
    for (int k = 0; k < n; k++)
    {
        double prod = 1;
        for (int i = 0; i < n; i++)
        {
            if (i != k)
            {
                prod = prod * ((xr-x[i])/(x[k]-x[i]));
            }
        }
        suma = suma + y[k] * prod;
    }
    
    printf("resultados:\n"
        "variable a aproximar xr: %.2f\n"
        "aproximacion pn(xr): %.2f\n"
        "datos utilizados para la aproximacion: \n",xr,suma);
        leerVector(x,y);
}


