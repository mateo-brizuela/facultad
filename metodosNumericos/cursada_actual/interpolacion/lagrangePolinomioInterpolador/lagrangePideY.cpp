#include <stdio.h>

#define n 3  // cantidad de puntos (hay n elementos: índices 0..n-1)

void cargarVector(double x[n], double y[n]);
void leerVector(double x[n], double y[n]);
void lagrange(double x[n], double y[n]);

int main(int argc, char const *argv[])
{
    double x[n], y[n];
    cargarVector(x, y);
    leerVector(x, y);
    lagrange(x, y);
    return 0;
}

void cargarVector(double x[n], double y[n]){
    // ahora cargamos x e y manualmente
    printf("Cargando los %d puntos (x_i, y_i)\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("ingrese x%d: ", i);
        scanf("%lf", &x[i]);
        printf("ingrese y%d: ", i);
        scanf("%lf", &y[i]);
    }
}

void leerVector(double x[n], double y[n]){
    printf("x\t|\ty\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.2f\t|\t%.2f | indice: %d \n", x[i], y[i], i);
    }
}

void lagrange(double x[n], double y[n]){
    // declaracion de variables locales 
    double suma = 0.0; // suma de todos los terminos del polinomio 
    double xr = 0.0;   // x donde queremos aproximar

    // pedimos el valor a interpolar
    printf("ingrese el valor que quiere aproximar por interpolacion: ");
    scanf("%lf", &xr);

    printf("calculando lagrange\n");
    for (int k = 0; k < n; k++)
    {
        double prod = 1.0;
        for (int i = 0; i < n; i++)
        {
            if (i != k)
            {
                // chequeo simple por si hay nodos x repetidos
                if (x[k] == x[i]) {
                    fprintf(stderr, "Error: x[%d] y x[%d] son iguales; no se puede interpolar.\n", k, i);
                    return;
                }
                prod = prod * ((xr - x[i]) / (x[k] - x[i]));
            }
        }
        suma = suma + y[k] * prod;
    }
    
    printf("resultados:\n"
           "variable a aproximar xr: %.2f\n"
           "aproximacion pn(xr): %.2f\n"
           "datos utilizados para la aproximacion:\n", xr, suma);
    leerVector(x, y);
}
