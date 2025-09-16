#include <stdio.h>
#include <math.h>   // exp, fabs, pow, isfinite

// g(x): función iterativa de punto fijo (x_{i+1} = g(x_i))
double g(double x) {
    // Tu elección actual: x = 0.4 * e^{x^2}  (punto fijo de x - 0.4 e^{x^2} = 0)
    double e = std::exp(1.0);
    return 0.4*pow(e,pow(x,2));
}

// Aproximación de g'(x): diferencia central (mejor que adelantada)
double g_deriv(double x) {
    const double h = 0.001;
    return (g(x + h) - g(x)) / h;
}

// (opcional) residuo de la ecuación f(x)=0 equivalente: f(x) = x - g(x)
double f(double x) { return x - g(x); }

int main(void)
{
    double x0 = 0.0; // xi
    double x1 = 0.0; // x(i+1)
    double eAbsoluto = 0.0;

    int cifrasTolerancia = 0;
    double tolerancia = 0.0;
    int i = 0;
    int opcion = 0;

    printf("Bienvenido al programa de calculo por punto fijo\n");
    printf("Seleccione una opcion\n"
           "1) ingresar los valores por terminal\n"
           "2) usar valores por defecto\n");
    if (scanf("%d",&opcion) != 1) return 1;

    if (opcion == 1) {
        printf("Ingrese el punto x0: ");
        if (scanf("%lf",&x0) != 1) return 1;
        printf("Ingrese la cantidad de decimales de precision: ");
        if (scanf("%d",&cifrasTolerancia) != 1) return 1;
    } else {
        x0 = 0.1;             // elegí un x0 razonable
        cifrasTolerancia = 6; // p. ej. 6 decimales
        printf("Usando defaults: x0=%.6f, cifras=%d\n", x0, cifrasTolerancia);
    }

    // tolerancia por cifras (puedes usar 10^{-p} si lo prefieren)
    tolerancia = pow(10.0, -cifrasTolerancia);

    const int MAX_IT = 1000;

    do {
        i++;

        // (opcional) aviso de contracción
        double dg = g_deriv(x0);
        if (fabs(dg) >= 1.0) {
            printf("Advertencia: |g'(x0)|=%.6f >= 1 en x0=%.6f. Puede NO converger.\n", dg, x0);
            return 1;
            // Si tu profe pide cortar, reemplazá por: return 1;
        }

        x1 = g(x0); // calcula el punto critico usando el metodo iterativo 
        if (!isfinite(x1)) {
            printf("Divergencia/overflow.\n");
            return 1;
        }

        eAbsoluto = fabs(x1 - x0);
        x0 = x1;

        if (i >= MAX_IT) {
            printf("Se alcanzo el maximo de iteraciones (%d).\n", MAX_IT);
            break;
        }
    } while (eAbsoluto > tolerancia /* && fabs(f(x1)) > tolerancia */);

    printf("\nResultados:\n");
    printf("Raiz aproximada (punto fijo): %.10f\n", x1);
    printf("Error aprox (abs): %.10f\n", eAbsoluto);
    printf("Iteraciones: %d\n", i);
    // (opcional) también imprimí el residuo:
    printf("|f(x)| = %.3e\n", fabs(f(x1)));

    return 0;
}
