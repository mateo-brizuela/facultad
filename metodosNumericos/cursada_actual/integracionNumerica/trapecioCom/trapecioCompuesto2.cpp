#include <stdio.h>
#include <cmath>

#define D 6 // es la cantidad de datos que se van a ingresar
#define MAX_PUNTOS_PROGRAMA D // la librería usará este valor

#include "../../librerias/splineCubica/spline_cubica.h"

double func(double x){
    return (x*x) + 1.0;
}

void trapecioFunc(double &res);
void trapecioTabla(double &res, double x[D], double y[D]); // Declaración de la nueva función
void cargarVector(double x[D], double y[D]);
void mostrarTabla(double x[D], double y[D]);

int main(int argc, char const *argv[])
{
    double res = 0.0, x[D], y[D];
    int opcion;
    printf("Bienvenido al programa para calcular integrales (trapecio compuesto)\n");
    printf("¿Cómo desea calcular la integral?\n");
    printf("1) Usar función matemática\n");
    printf("2) Ingresar tabla de datos\n");
    printf("Opción: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        trapecioFunc(res);
    } else if (opcion == 2) {
        cargarVector(x, y);
        mostrarTabla(x, y);
        trapecioTabla(res, x, y); 
    } else {
        printf("Opción no válida.\n");
    }

    return 0;
}

void trapecioFunc(double &res){
    double a = 0.0, b = 0.0, h = 0.0, n = 0.0, sum = 0.0;
    printf("Ingrese el limite inferior de la integral: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior de la integral: ");
    scanf("%lf", &b);
    printf("Ingrese la cantidad de subintervalos (n): ");
    scanf("%lf", &n);
    h = (b - a) / n;
    sum = func(a) + func(b);
    for (int i = 1; i < n; i++) {
        sum += 2 * func(a + i*h);
    }
    res = (h / 2) * sum;

    printf("El resultado de la integral(dec): %.6lf\n", res);
    printf("El resultado de la integral(cient): %.6e\n", res);
}

// Devuelve true si el vector x[] es equiespaciado, false si no lo es
bool esEquiespaciada(double x[D]) {
    double h = x[1] - x[0];
    const double EPS = 1e-6; // tolerancia para errores de redondeo
    for (int i = 2; i < D; i++) {
        if (fabs((x[i] - x[i-1]) - h) > EPS) {
            return false;
        }
    }
    return true;
}

void trapecioTabla(double &res, double x[D], double y[D]) {
    int n;
    printf("Ingrese la cantidad de subintervalos que desea: ");
    scanf("%d", &n);

    double a = x[0]; // defino el primer y el ultimo elemento de la integral 
    double b = x[D-1];
    double h = (b - a) / n; // calculo la distancia segun la cantidad de subintervalos ingresados
    double matriz_coeficientes[MAX_SEGMENTOS][4];

    // Definir los nuevos puntos equiespaciados
    double x_new[n+1], y_new[n+1]; // x_new y y_new es una nueva tabla donde los elementos estan equiespaciados 
    for (int i = 0; i <= n; i++) {
        x_new[i] = a + i * h;
    }

    // Interpolar los valores y_new usando spline cúbica
    int resultado = spline_calcular_coeficientes(x,y,D,matriz_coeficientes); // se verifica en resultado si funciono o no 
    if (resultado == -1)
    {
        printf("ERROR: algo paso en la libreria\n");
    }
    
    resultado = spline_evaluar_multiples_puntos(x, D, matriz_coeficientes, x_new, n+1, y_new); // se hacen las aproximaciones

    // Ahora puedes aplicar el método del trapecio compuesto con x_new[] y y_new[]
    // (puedes reutilizar el código de trapecioFunc adaptado para tabla)
    double sum = y_new[0] + y_new[n];
    for (int i = 1; i < n; i++) {
        sum += 2 * y_new[i];
    }
    res = (h / 2) * sum;

    printf("El resultado de la integral (por tabla y spline): %.6lf\n", res);
}

void cargarVector(double x[D], double y[D]) {
    printf("Cargando %d puntos (x_i, y_i):\n", D);
    for (int i = 0; i < D; i++) {
        printf("Ingrese x[%d]: ", i);
        scanf("%lf", &x[i]);
        printf("Ingrese y[%d]: ", i);
        scanf("%lf", &y[i]);
    }
}

void mostrarTabla(double x[D], double y[D]) {
    printf("\n=== TABLA DE DATOS ===\n");
    printf("Indice\tx\t\ty\n");
    for (int i = 0; i < D; i++) {
        printf("%d\t%.6f\t%.6f\n", i, x[i], y[i]);
    }
}