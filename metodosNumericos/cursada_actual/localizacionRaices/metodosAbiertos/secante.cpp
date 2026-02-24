// metodoSecante.cpp
#include <stdio.h>
#include <math.h>

// Funcion objetivo: buscar x tal que f(x)=0
// (Cambiala si queres resolver otra ecuacion)
double f(double x) {
    // Igual que (1/exp(x)) - x, pero mas claro y estable
    return exp(-x) - x;
}

int main(int argc, char const *argv[])
{
    // En secante siempre trabajamos con DOS aproximaciones anteriores:
    // x0 = x_{n-1}, x1 = x_n, y calculamos x2 = x_{n+1}
    double x0 = 0.0;
    double x1 = 0.0;
    double x2 = 0.0;

    double error = 0.0;       // error absoluto: |x_{n+1} - x_n|
    double tolerancia = 0.0;  // tolerancia = 10^(-decimales)

    int i = 0; // contador de iteraciones
    int decimalesPrecision = 0;
    int opcion = 0;

    const int MAX_ITERS = 10000;   // limite de seguridad
    const double EPS_DEN = 1e-12;  // evita dividir por (f1 - f0) ~ 0

    printf("Bienvenido al programa de calculo por el metodo de la secante\n");
    printf("seleccione una opcion\n"
           "1) ingresar los valores por terminal\n"
           "2) usar valores por defecto\n");
    scanf("%d", &opcion);

    if (opcion == 1) {
        printf("Ingrese el valor inicial x0 (primer punto): ");
        scanf("%lf", &x0);
        printf("Ingrese el valor inicial x1 (segundo punto): ");
        scanf("%lf", &x1);
        printf("Ingrese la cantidad de decimales de precision: ");
        scanf("%d", &decimalesPrecision);
    } else {
        // Defaults razonables para esta f(x)
        x0 = 0.0;
        x1 = 1.0;
        decimalesPrecision = 6;
        printf("Usando valores por defecto (x0 = %.4f) (x1 = %.4f) (decimales = %d)\n",
               x0, x1, decimalesPrecision);
    }

    // Ej: decimales=6 => tolerancia=1e-6
    tolerancia = pow(10.0, -decimalesPrecision);

    // Si x0 == x1 no hay recta secante (division por cero en la pendiente)
    if (x0 == x1) {
        printf("Error: x0 y x1 no pueden ser iguales.\n");
        return 1;
    }

    do {
        i++;

        // Evaluamos la funcion en los dos puntos actuales
        double f0 = f(x0);
        double f1 = f(x1);

        // Denominador de la formula: (f(x1) - f(x0))
        // Si es muy chico, la pendiente de la secante se vuelve inestable
        double denom = (f1 - f0);
        if (fabs(denom) < EPS_DEN) {
            printf("Denominador muy pequeno (f(x1) - f(x0) ~ 0). No es seguro continuar.\n");
            printf("f(x0)=%.12f  f(x1)=%.12f\n", f0, f1);
            return 1;
        }

        // Paso del metodo de la secante:
        // x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0))
        x2 = x1 - f1 * (x1 - x0) / denom;

        // Criterio de error (el que te toman): tamaño del salto
        error = fabs(x2 - x1);

        // Avanzamos la "ventana" para la proxima iteracion
        x0 = x1;
        x1 = x2;

    } while (error > tolerancia && i < MAX_ITERS);

    printf("raiz (decimal): %.12f\n"
           "raiz (cientifico): %.12e\n"
           "iteraciones: %d\n"
           "error absoluto (decimal): %.12f\n"
           "error absoluto (cientifico): %.12e\n"
           "f(x): %.12f\n",
           x1, x1, i, error, error, f(x1));

    return 0;
}
