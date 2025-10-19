// Variante: Bisección con criterio de corte (absoluto o porcentual)
// - Rama de "raíz exacta" simplificada: errores = 0 y retorno inmediato.
// - Mantiene estructura con ifs y llaves, comentarios breves.
// - Incluye MAX_ITER, aviso por tope, y prints en decimal y científica.
// - Si se elige criterio porcentual y c==0 (sin raíz exacta), advierte y cancela.

#include <stdio.h>
#include <iostream>
#include <math.h>

#define MAX_ITER 100  // Tope de iteraciones

double calcularFuncion(double x); // declaración de la función

int main(int argc, char const *argv[])
{
    // Variables principales
    double a = 0.0;      // Extremo izquierdo del intervalo [a, b]
    double b = 0.0;      // Extremo derecho del intervalo [a, b]
    double c = 0.0;      // Punto medio
    double cViejo = 0.0; // Para medir error entre iteraciones

    double fa = 0.0;     // f(a)
    double fb = 0.0;     // f(b)
    double fc = 0.0;     // f(c)

    double eAbsoluto = 0.0;     // |c - cViejo|
    double eRelativo = 0.0;     // |c - cViejo| / |c|
    double ePorcentual = 0.0;   // eRelativo * 100
    int cifrasPrecision = 0;    // Cifras de precisión
    double toleracia = 0.0;     // 10^{-cifrasPrecision}
    int i = 0;                  // Iteraciones

    bool manual = false;        // Ingreso manual
    int opcion = 0;             // Opción de ingreso
    int criterio = 1;           // 1 = abs ; 2 = porcentual

    // Menú de ingreso
    printf("Bienvenido al programa de calculo por biseccion!\n"
           "Seleccione una opcion:\n"
           "1) Ingresar los valores por terminal\n"
           "2) Tomar los valores ingresados en el codigo\n");
    scanf("%d", &opcion);

    if (opcion == 1)
    {
        manual = true;
    }
    else
    {
        manual = false;
    }

    if (manual)
    {
        printf("Ingrese el valor de a: ");
        scanf("%lf", &a);
        printf("Ingrese el valor de b: ");
        scanf("%lf", &b);
        printf("Ingrese la cantidad de cifras de precision: ");
        scanf("%d", &cifrasPrecision);
    }

    // Criterio de corte
    printf("Criterio de corte:\n"
           "1) Error absoluto\n"
           "2) Error porcentual\n");
    scanf("%d", &criterio);

    // Tolerancia
    toleracia = pow(10, -cifrasPrecision);

    // Evaluaciones iniciales
    fa = calcularFuncion(a);
    fb = calcularFuncion(b);

    // Verificar cambio de signo
    if ((fa * fb) > 0)
    {
        printf("Error: no se encuentra una raiz en el intervalo especificado\n");
        return 1;
    }
    else
    {
        // Bucle principal de biseccion
        do
        {
            i++;

            c = (a + b) / 2.0;
            fa = calcularFuncion(a);
            fb = calcularFuncion(b);
            fc = calcularFuncion(c);

            // Reducción del intervalo manteniendo cambio de signo
            if ((fa * fc) > 0)
            {
                a = c;
            }
            else if ((fa * fc) < 0)
            {
                b = c;
            }
            else
            {
                // ================== RAIZ EXACTA ==================
                // Si f(c) == 0, la raiz es exacta => errores = 0.
                eAbsoluto = 0.0;
                eRelativo = 0.0;
                ePorcentual = 0.0;

                printf("Se encontro la raiz EXACTA (f(c) = 0). Los errores son 0.\n");
                printf("La raiz (decimal)           : %.9f\n", c);
                printf("La raiz (cientifica)        : %.9e\n", c);
                printf("Error absoluto (dec)        : %.10f\n", eAbsoluto);
                printf("Error absoluto (sci)        : %.10e\n", eAbsoluto);
                printf("Error relativo (dec)        : %.10f\n", eRelativo);
                printf("Error relativo (sci)        : %.10e\n", eRelativo);
                printf("Error porcentual (dec)      : %.6f%%\n", ePorcentual);
                printf("Error porcentual (sci)      : %.6e%%\n", ePorcentual);
                printf("Iteraciones                 : %d\n", i);
                return 0;
                // ==================================================
            }

            // Errores respecto de la iteración anterior
            eAbsoluto = fabs(c - cViejo);

            if (criterio == 2)
            {
                // Criterio porcentual: si c==0 no se puede calcular (cancelar)
                if (c == 0.0)
                {
                    printf("\n============================================\n");
                    printf("  ADVERTENCIA: DIVISION POR CERO EN ERROR %%\n");
                    printf("  c = 0. No es posible calcular error porcentual.\n");
                    printf("  Ejecucion cancelada.\n");
                    printf("============================================\n\n");
                    return 2;
                }
                else
                {
                    eRelativo = fabs(c - cViejo) / fabs(c);
                    ePorcentual = eRelativo * 100.0;
                }
            }
            else
            {
                // Criterio absoluto: calcular relativo si se puede (sin cancelar)
                if (c != 0.0)
                {
                    eRelativo = fabs(c - cViejo) / fabs(c);
                    ePorcentual = eRelativo * 100.0;
                }
                else
                {
                    // c==0 y no porcentual: el relativo sería indefinido, no lo usamos para cortar
                }
            }

            // Actualizar cViejo
            cViejo = c;

        }
        while (
            (
                (criterio == 1 && (eAbsoluto > toleracia)) ||
                (criterio == 2 && (ePorcentual > (toleracia * 100.0)))
            )
            &&
            (i < MAX_ITER)
        );

        // Aviso si se alcanzó el tope sin cumplir la tolerancia
        if (
            (i >= MAX_ITER) &&
            (
                (criterio == 1 && (eAbsoluto > toleracia)) ||
                (criterio == 2 && (ePorcentual > (toleracia * 100.0)))
            )
           )
        {
            printf("\n============================================\n");
            printf("  ADVERTENCIA: TOPE DE ITERACIONES ALCANZADO\n");
            printf("  (MAX_ITER = %d) sin cumplir la tolerancia.\n", MAX_ITER);
            printf("============================================\n\n");
        }

        // Resultados finales (decimal y científica)
        printf("La raiz (decimal)           : %.9f\n", c);
        printf("La raiz (cientifica)        : %.9e\n", c);
        printf("Error absoluto (dec)        : %.10f\n", eAbsoluto);
        printf("Error absoluto (sci)        : %.10e\n", eAbsoluto);

        if (c != 0.0)
        {
            printf("Error relativo (dec)        : %.10f\n", eRelativo);
            printf("Error relativo (sci)        : %.10e\n", eRelativo);
            printf("Error porcentual (dec)      : %.6f%%\n", ePorcentual);
            printf("Error porcentual (sci)      : %.6e%%\n", ePorcentual);
        }
        else
        {
            printf("[Aviso] c = 0. Se omite el error relativo/porcentual para evitar division por cero.\n");
        }

        printf("Iteraciones                 : %d\n", i);
    }

    return 0;
}

// Ejemplo de test: f(x) = x^3 - x - 2
double calcularFuncion(double x)
{
    double fx = pow(x, 3) - x - 2;
    return fx;
}
