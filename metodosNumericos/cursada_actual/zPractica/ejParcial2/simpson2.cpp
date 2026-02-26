#include <stdio.h>
#include <cmath>

#define D 11 // cantidad de puntos que vamos a cargar en el programa
#define MAX_PUNTOS_PROGRAMA D

// librerias propias
#include "librerias/eliminacionGaussiana/gauss_solver.h"
#include "librerias/splineCubica/spline_cubica.h"

// funcion matematica (opcion con función)
double func(double x){
    return (x*x) + 1.0;
}

// prototipo de funciones
void simpsonFunc();
void simpsonTable();

// utilidades
bool esEquiespaciada(const double x[D]);

typedef struct {
    double *x;
    double *y;
    int puntos;
} Tabla;

int main(int argc, char const *argv[])
{
    int opcion = 0;
    printf("Bienvenido al programa para calcular integrales (Simpson) - v2\n");
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

    for (int i = 1; i < n; i += 2) {
        suma += 4.0 * func(a + i * h);
    }
    for (int i = 2; i < n; i += 2) {
        suma += 2.0 * func(a + i * h);
    }

    res = (h / 3.0) * suma;
    printf("El resultado de la integracion es: %.10f\n", res);
}

bool esEquiespaciada(const double x[D]) {
    double h = x[1] - x[0];
    const double EPS = 1e-8;
    if (fabs(h) < EPS) return false;
    for (int i = 2; i < D; i++) {
        if (fabs((x[i] - x[i-1]) - h) > EPS) {
            return false;
        }
    }
    return true;
}

static double simpsonCompuesto(const double *x, const double *y, int puntos) {
    int n_sub = puntos - 1;
    double h = x[1] - x[0];
    double suma = y[0] + y[puntos - 1];
    for (int i = 1; i < puntos - 1; i += 2) suma += 4.0 * y[i];
    for (int i = 2; i < puntos - 1; i += 2) suma += 2.0 * y[i];
    return (h / 3.0) * suma;
}

void simpsonTable(){
    double x[D] = {0.0}, y[D] = {0.0};
    int opcion_auto = 0;

    printf("Seleccionó la opción de calcular la integral usando una tabla de datos\n");
    printf("Ingrese todos los datos que correspondan a X:\n");
    cargarVectorTeclado(x, D);
    printf("Ingrese todos los datos que correspondan a Y:\n");
    cargarVectorTeclado(y, D);

    printf("La tabla cargada es la siguiente:\n");
    leerVectoresTabla(x, y, D);
    printf("\n");

    bool equi = esEquiespaciada(x);
    int n_sub_original = D - 1;

    if (equi && (n_sub_original % 2 == 0)) {
        printf("La tabla es equiespaciada y tiene subintervalos pares.\n");
        printf("Opciones:\n");
        printf(" 1) Usar tabla original (Simpson directo)\n");
        printf(" 2) Generar nueva tabla con spline (n elegido)\n");
        printf("Seleccione opción (1/2): ");
        int opt = 1;
        if (scanf("%d", &opt) != 1) opt = 1;

        if (opt == 1) {
            double integral = simpsonCompuesto(x, y, D);
            printf("\nEl resultado de la integracion es: %.10f\n", integral);
            return;
        }
    } else if (equi && (n_sub_original % 2 != 0)) {
        printf("ADVERTENCIA: la tabla es equiespaciada pero tiene %d subintervalos (impar).\n", n_sub_original);
        printf("Se usará spline cúbico para generar una tabla con subintervalos pares.\n");
    } else {
        printf("La tabla NO es equiespaciada -> se usará spline cúbico.\n");
    }

    // Definir subintervalos para la tabla interpolada
    printf("¿Desea definir automáticamente la cantidad de subintervalos?\n");
    printf("1) Sí, definir automáticamente\n");
    printf("2) No, ingresar manualmente\n");
    printf("Opción: ");
    scanf("%d", &opcion_auto);

    int n_sub = 0;
    if (opcion_auto == 1) {
        // Si D-1 es par, usamos D-1; si es impar, sumamos 1 subintervalo
        if ((D - 1) % 2 == 0) n_sub = D - 1;
        else n_sub = D;
        printf("Cantidad de subintervalos definida automáticamente: %d\n", n_sub);
    } else {
        printf("Ingrese la cantidad de subintervalos (debe ser PAR): ");
        scanf("%d", &n_sub);
        if (n_sub % 2 != 0) {
            printf("ADVERTENCIA: %d es impar. Se ajusta a %d para aplicar Simpson.\n", n_sub, n_sub + 1);
            n_sub += 1;
        }
    }

    int puntos = n_sub + 1;
    double *x_new = new double[puntos];
    double *y_new = new double[puntos];
    double a = x[0], b = x[D - 1];
    double h = (b - a) / n_sub;

    x_new[0] = a;
    x_new[puntos - 1] = b;
    for (int i = 1; i < puntos - 1; i++) {
        x_new[i] = x_new[0] + (i * h);
    }

    // Interpolación con spline cúbico
    double coeficientes[MAX_SEGMENTOS][4] = {0.0};
    spline_calcular_coeficientes(x, y, D, coeficientes);
    spline_evaluar_multiples_puntos(x, D, coeficientes, x_new, puntos, y_new);

    printf("\nTabla interpolada y equiespaciada:\n");
    leerVectoresTabla(x_new, y_new, puntos);

    double integral = simpsonCompuesto(x_new, y_new, puntos);
    printf("\nEl resultado de la integracion es: %.10f\n", integral);

    delete[] x_new;
    delete[] y_new;
}
