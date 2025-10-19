#include <stdio.h>
#include <cmath>

#define D 7 // cantidad de puntos que vamos a cargar en el programa 
#define MAX_PUNTOS_PROGRAMA D // le dejamos un punto de margen por si se usa n = D + 1

// librerias propias 
#include "../../librerias/eliminacionGaussiana/gauss_solver.h"
#include "../../librerias/splineCubica/spline_cubica.h"

// funcion matematica
double func(double x){
    return (x*x) + 1.0;
}

// prototipo de funciones 
void simpsonFunc();
void simpsonTable();

int main(int argc, char const *argv[])
{
    int opcion = 0;
    printf("Bienvenido al programa para calcular integrales (Simpson)\n");
    printf("¿Cómo desea calcular la integral?\n");
    printf("1) Usar función matemática\n");
    printf("2) Ingresar tabla de datos\n");
    printf("Opción: ");
    scanf("%d", &opcion);

    if (opcion == 1)
        simpsonFunc();
    else if (opcion == 2)
        simpsonTable();

    return 0;
}

void simpsonFunc(){
    double a = 0.0, b = 0.0, h = 0.0, suma = 0.0, res = 0.0;
    int n = 0;
    
    printf("Ingrese el limite inferior de la integral: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior de la integral: ");
    scanf("%lf", &b);
    printf("Ingrese la cantidad de subintervalos (n DEBE SER PAR!): ");
    scanf("%d", &n);
    
    if (n % 2 != 0) {
        printf("ERROR: debe ser un numero PAR de intervalos\n");
        return;
    }

    h = (b - a) / n;
    suma = func(a) + func(b);

    // Puntos impares: coeficiente 4
    for (int i = 1; i < n; i += 2) {
        suma += 4.0 * func(a + i * h);
    }
    
    // Puntos pares internos: coeficiente 2
    for (int i = 2; i < n; i += 2) {
        suma += 2.0 * func(a + i * h);
    }

    res = (h / 3.0) * suma;
    printf("El resultado de la integracion es: %.10f\n", res);
}

void simpsonTable(){
    double x[D] = {0.0}, y[D] = {0.0};
    double suma = 0.0;
    int n = 0; // cantidad de puntos a usar en la nueva tabla
    int opcion_auto = 0;

    printf("Seleccionó la opción de calcular la integral usando una tabla de datos\n");
    printf("Ingrese todos los datos que correspondan a X:\n");
    cargarVectorTeclado(x, D);
    printf("Ingrese todos los datos que correspondan a Y:\n");
    cargarVectorTeclado(y, D);

    printf("La tabla cargada es la siguiente:\n");
    leerVectoresTabla(x, y, D);
    printf("\n");

    // Nueva opción: decidir cómo definir la cantidad de subintervalos
    printf("¿Desea definir automáticamente la cantidad de subintervalos?\n");
    printf("1) Sí, definir automáticamente\n");
    printf("2) No, ingresar manualmente\n");
    printf("Opción: ");
    scanf("%d", &opcion_auto);

    if (opcion_auto == 1) {
        // Si D es par, agregamos un punto extra para cumplir la regla de Simpson
        if (D % 2 == 0)
            n = D + 1;
        else
            n = D;
        printf("Cantidad de subintervalos definida automáticamente: %d\n", n - 1);
    } else {
        printf("Ingrese la cantidad de subintervalos (debe ser PAR): ");
        scanf("%d", &n);
        n += 1; // los subintervalos son n-1, así mantenemos consistencia con el array
        if ((n - 1) % 2 != 0) {
            printf("ERROR: el número de subintervalos debe ser par.\n");
            return;
        }
    }

    // Construcción de la tabla equiespaciada
    double x_new[n], y_new[n];
    double a = x[0], b = x[D - 1];
    double coeficientes[MAX_SEGMENTOS][4] = {0.0};
    x_new[0] = a; 
    x_new[n - 1] = b; 
    double h = (b - a) / (n - 1);

    for (int i = 1; i < n - 1; i++) {
        x_new[i] = x_new[0] + (i * h);
    }
    
    // Interpolación con spline cúbico
    spline_calcular_coeficientes(x, y, D, coeficientes);
    spline_evaluar_multiples_puntos(x, D, coeficientes, x_new, n, y_new);

    printf("\nTabla interpolada y equiespaciada:\n");
    leerVectoresTabla(x_new, y_new, n);

    // Simpson compuesto (versión estándar, clara)
    suma = y_new[0] + y_new[n - 1];
    for (int i = 1; i < n - 1; i += 2) {
        suma += 4.0 * y_new[i];
    }
    for (int i = 2; i < n - 1; i += 2) {
        suma += 2.0 * y_new[i];
    }
    double integral = (h / 3.0) * suma;

    printf("\nEl resultado de la integracion es: %.10f\n", integral);
}
