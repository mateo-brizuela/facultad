#include <stdio.h>
#include <math.h>

#define MAX_ITER 10000  // Límite máximo de iteraciones para evitar bucles infinitos

double calcularFuncion(double x);
double calcularDerivada(double x);

int main(int argc, char const *argv[])
{
    // Variables principales del método
    double x0 = 0.0;          // Valor inicial (x_i)
    double x1 = 0.0;          // Siguiente iteración (x_{i+1})
    double eAbsoluto = 0.0;   // Error absoluto entre iteraciones
    double eRelativo = 0.0;   // Error relativo
    double ePorcentual = 0.0; // Error porcentual

    // Variables de control de precisión
    int cifrasTolerancia = 0; // Cantidad de decimales de precisión requeridos
    double tolerancia = 0.0;  // Tolerancia calculada como 10^{-cifrasTolerancia}
    int i = 0;                // Contador de iteraciones
    int opcion = 0;           // Opción del menú de entrada
    int criterio = 1;         // 1 = absoluto, 2 = porcentual

    // Menú de configuración inicial
    printf("Bienvenido al programa de calculo por punto fijo\n");
    printf("seleccione una opcion\n"
        "1) ingresar los valores por terminal\n"
        "2) tomar los valores por defecto en el codigo\n");
    scanf("%d",&opcion);

    // Configuración de parámetros según la opción seleccionada
    if (opcion == 1)
    {
        // Entrada manual de parámetros
        printf("ingrese el punto x0: ");
        scanf("%lf",&x0);

        printf("seleccione el criterio de corte para la tolerancia\n"
            "1) por cantidad de decimales (error absoluto)\n"
            "2) por error porcentual\n");
        scanf("%d",&criterio);
        
        if (criterio == 1)
        {
            printf("ingrese la cantidad de decimales de precision: ");
            scanf("%d",&cifrasTolerancia);
            tolerancia = pow(10,-cifrasTolerancia);
        }
        else if (criterio == 2)
        {
            printf("Ingrese el error porcentual maximo permitido (en %%): ");
            scanf("%lf",&tolerancia);
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
    }
    else
    {
        // Valores por defecto (configuración predefinida)
        x0 = 0.5;
        criterio = 1;
        cifrasTolerancia = 6;
        tolerancia = pow(10,-cifrasTolerancia);
    }

    // Bucle principal del método de punto fijo
    do
    {
        i++; // Incrementar contador de iteraciones
        
        // Verificación de convergencia: |g'(x)| debe ser < 1
        if (fabs(calcularDerivada(x0)) >= 1)
        {
            printf("error: el metodo no converge\n");
            return 1;
        }

        // Aplicar la función de iteración: x_{i+1} = g(x_i)
        x1 = calcularFuncion(x0);
        
        // Calcular error absoluto entre iteraciones consecutivas
        eAbsoluto = fabs(x1 - x0);
        
        // Calcular error relativo y porcentual si x1 != 0
        if (x1 != 0.0)
        {
            eRelativo = fabs(x1 - x0) / fabs(x1);
            ePorcentual = eRelativo * 100.0;
        }
        else
        {
            // Si x1 == 0 y usamos criterio porcentual, no se puede continuar
            if (criterio == 2)
            {
                printf("\n============================================\n");
                printf("  ADVERTENCIA: DIVISION POR CERO EN ERROR %%\n");
                printf("  x1 = 0. No es posible calcular error porcentual.\n");
                printf("  Ejecucion cancelada.\n");
                printf("============================================\n\n");
                return 2;
            }
        }
        
        // Actualizar x0 para la siguiente iteración
        x0 = x1;
        
    } while (
        (
            (criterio == 1 && (eAbsoluto > tolerancia)) ||
            (criterio == 2 && (ePorcentual > tolerancia))
        )
        &&
        (i < MAX_ITER)
    ); // Condiciones de parada
    
    // Advertencia si se alcanzó el límite de iteraciones
    if (
        (i >= MAX_ITER) &&
        (
            (criterio == 1 && (eAbsoluto > tolerancia)) ||
            (criterio == 2 && (ePorcentual > tolerancia))
        )
    ) {
        printf("\n============================================\n");
        printf("  ADVERTENCIA: TOPE DE ITERACIONES ALCANZADO\n");
        printf("  (MAX_ITER = %d) sin cumplir la tolerancia.\n", MAX_ITER);
        printf("============================================\n\n");
    }
    
    // Presentación de resultados finales
    printf("\n=== RESULTADOS ===\n");
    printf("Raiz (decimal):    %.12f\n", x1);      // Notación decimal con 12 decimales
    printf("Raiz (cientifica): %.12e\n", x1);      // Notación científica con 12 dígitos
    printf("Error absoluto (decimal):    %.12f\n", eAbsoluto);
    printf("Error absoluto (cientifica): %.12e\n", eAbsoluto);
    
    if (x1 != 0.0)
    {
        printf("Error relativo (decimal):    %.12f\n", eRelativo);
        printf("Error relativo (cientifica): %.12e\n", eRelativo);
        printf("Error porcentual (decimal):  %.6f%%\n", ePorcentual);
        printf("Error porcentual (cientifica): %.6e%%\n", ePorcentual);
    }
    else
    {
        printf("[Aviso] x1 = 0. Se omite el error relativo/porcentual para evitar division por cero.\n");
    }
    
    printf("Iteraciones: %d\n", i);

    return 0;
}

// Función g(x) para la iteración de punto fijo: x = g(x)
// En este caso: g(x) = cos(sin(x))
double calcularFuncion(double x){
    return (2.5*sqrt(x) - 800.0) / (-0.5*log2(x));
}

// Cálculo numérico de la derivada g'(x) usando diferencia central
// h = 1e-5 proporciona un buen equilibrio entre precisión y estabilidad
double calcularDerivada(double x){
    double h = 1e-5; // Paso para el cálculo de la derivada
    return (calcularFuncion(x + h) - calcularFuncion(x - h)) / (2 * h);
}