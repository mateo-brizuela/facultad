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

    // Variables de control de precisión
    int cifrasTolerancia = 0; // Cantidad de decimales de precisión requeridos
    double tolerancia = 0.0;  // Tolerancia calculada como 10^{-cifrasTolerancia}
    int i = 0;                // Contador de iteraciones
    int opcion = 0;           // Opción del menú de entrada

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
        printf("ingrese la cantidad de decimales de precision: ");
        scanf("%d",&cifrasTolerancia);
    }
    else
    {
        // Valores por defecto (configuración predefinida)
        x0 = 0.5;
        cifrasTolerancia = 6;
    }
    
    // Cálculo de la tolerancia basada en las cifras requeridas
    tolerancia = pow(10,-cifrasTolerancia);

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
        
        // Actualizar x0 para la siguiente iteración
        x0 = x1;
        
    } while (eAbsoluto > tolerancia && i < MAX_ITER); // Condiciones de parada
    
    // Advertencia si se alcanzó el límite de iteraciones
    if (i >= MAX_ITER) {
        printf("Advertencia: se alcanzo el maximo de iteraciones (%d)\n", MAX_ITER);
    }
    
    // Presentación de resultados finales
    printf("\n=== RESULTADOS ===\n");
    printf("Raiz (decimal):    %.12f\n", x1);      // Notación decimal con 12 decimales
    printf("Raiz (cientifica): %.12e\n", x1);      // Notación científica con 12 dígitos
    printf("Error absoluto (decimal):    %.12f\n", eAbsoluto);
    printf("Error absoluto (cientifica): %.12e\n", eAbsoluto);
    printf("Iteraciones: %d\n", i);

    return 0;
}

// Función g(x) para la iteración de punto fijo: x = g(x)
// En este caso: g(x) = cos(sin(x))
double calcularFuncion(double x){
    return cos(sin(x));  // Ecuación: x = cos(sin(x))
}

// Cálculo numérico de la derivada g'(x) usando diferencia central
// h = 1e-5 proporciona un buen equilibrio entre precisión y estabilidad
double calcularDerivada(double x){
    double h = 1e-5; // Paso para el cálculo de la derivada
    return (calcularFuncion(x + h) - calcularFuncion(x - h)) / (2 * h);
}