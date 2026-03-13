// metodoSecante.cpp
#include <stdio.h>
#include <math.h>

// Funcion objetivo: buscar x tal que f(x)=0
// (Cambiala si queres resolver otra ecuacion)
double f(double x) {
    // Igual que (1/exp(x)) - x, pero mas claro y estable
    return 0.5*x*log2(x) + 2.5*sqrt(x) - 800.0;
}

int main(int argc, char const *argv[])
{
    // En secante siempre trabajamos con DOS aproximaciones anteriores:
    // x0 = x_{n-1}, x1 = x_n, y calculamos x2 = x_{n+1}
    double x0 = 0.0;
    double x1 = 0.0;
    double x2 = 0.0;

    double eAbsoluto = 0.0;      // error absoluto: |x_{n+1} - x_n|
    double eRelativo = 0.0;      // error relativo
    double ePorcentual = 0.0;    // error porcentual
    double tolerancia = 0.0;     // tolerancia = 10^(-decimales)

    int i = 0; // contador de iteraciones
    int decimalesPrecision = 0;
    int opcion = 0;
    int criterio = 1; // 1 = absoluto, 2 = porcentual

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

        printf("Ingrese el criterio de corte:\n"
               "1) Error absoluto (cantidad de cifras de precision)\n"
               "2) Error porcentual\n");
        scanf("%d", &criterio);
        
        if (criterio == 1)
        {
            printf("Ingrese la cantidad de cifras de precision: ");
            scanf("%d", &decimalesPrecision);
            tolerancia = pow(10.0, -decimalesPrecision);
        }
        else if (criterio == 2)
        {
            printf("Ingrese el error porcentual maximo permitido (en %%): ");
            scanf("%lf", &tolerancia);
            if (tolerancia <= 0.0 || tolerancia >= 100.0) {
                printf("Porcentaje invalido. Debe ser > 0 y < 100.\n");
                return 1;
            }
        }
        else
        {
            printf("Opcion de criterio no valida.\n");
            return 1;
        }
    } else {
        // Defaults razonables para esta f(x)
        x0 = 0.0;
        x1 = 1.0;
        criterio = 1;
        decimalesPrecision = 6;
        tolerancia = pow(10.0, -decimalesPrecision);
        printf("Usando valores por defecto (x0 = %.4f) (x1 = %.4f) (decimales = %d)\n",
               x0, x1, decimalesPrecision);
    }

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

        // Calcular error absoluto
        eAbsoluto = fabs(x2 - x1);

        // Calcular error relativo y porcentual si x2 != 0
        if (x2 != 0.0)
        {
            eRelativo = fabs(x2 - x1) / fabs(x2);
            ePorcentual = eRelativo * 100.0;
        }
        else
        {
            // Si x2 == 0 y usamos criterio porcentual, no se puede continuar
            if (criterio == 2)
            {
                printf("\n============================================\n");
                printf("  ADVERTENCIA: DIVISION POR CERO EN ERROR %%\n");
                printf("  x2 = 0. No es posible calcular error porcentual.\n");
                printf("  Ejecucion cancelada.\n");
                printf("============================================\n\n");
                return 2;
            }
        }

        // Avanzamos la "ventana" para la proxima iteracion
        x0 = x1;
        x1 = x2;

    } while (
        (
            (criterio == 1 && (eAbsoluto > tolerancia)) ||
            (criterio == 2 && (ePorcentual > tolerancia))
        )
        &&
        (i < MAX_ITERS)
    );

    // Advertencia si se alcanzó el límite de iteraciones
    if (
        (i >= MAX_ITERS) &&
        (
            (criterio == 1 && (eAbsoluto > tolerancia)) ||
            (criterio == 2 && (ePorcentual > tolerancia))
        )
    ) {
        printf("\n============================================\n");
        printf("  ADVERTENCIA: TOPE DE ITERACIONES ALCANZADO\n");
        printf("  (MAX_ITERS = %d) sin cumplir la tolerancia.\n", MAX_ITERS);
        printf("============================================\n\n");
    }

    printf("\n=== RESULTADOS ===\n");
    printf("Raiz (decimal):    %.12f\n", x1);
    printf("Raiz (cientifico): %.12e\n", x1);
    printf("Error absoluto (decimal):    %.12f\n", eAbsoluto);
    printf("Error absoluto (cientifico): %.12e\n", eAbsoluto);
    
    if (x1 != 0.0)
    {
        printf("Error relativo (decimal):    %.12f\n", eRelativo);
        printf("Error relativo (cientifico): %.12e\n", eRelativo);
        printf("Error porcentual (decimal):  %.6f%%\n", ePorcentual);
        printf("Error porcentual (cientifico): %.6e%%\n", ePorcentual);
    }
    else
    {
        printf("[Aviso] x1 = 0. Se omite el error relativo/porcentual para evitar division por cero.\n");
    }
    
    printf("Iteraciones: %d\n", i);
    printf("f(x): %.12f\n", f(x1));

    return 0;
}
