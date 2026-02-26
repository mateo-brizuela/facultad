/*
 * PROGRAMA: Integración Numérica con Simpson (v3)
 * Descripción: Calcula integrales numéricas usando la regla de Simpson
 * Opciones:
 *   1) Mediante una función matemática
 *   2) Mediante una tabla de datos (manual o desde CSV)
 * 
 * Para tablas no equiespaciadas, utiliza interpolación con splines cúbicos
 */

#include <stdio.h>
#include <cmath>
#include <cstring>

#define D 11                                    // máximo de puntos para tabla manual
#define MAX_PUNTOS_PROGRAMA D

// RUTA DEL ARCHIVO CSV (modificar según necesidad)
#define RUTA_CSV_DEFECTO "../../librerias/io/outputs/csv/datos_ejemplo.csv"

// Librerías propias
#include "../../librerias/eliminacionGaussiana/gauss_solver.h"
#include "../../librerias/splineCubica/spline_cubica.h"
#include "../../librerias/io/exportarResultados.h"

// Función matemática para la opción 1 (puede modificarse)
double func(double x){
    return exp(2.0*sin(x))*(1.0+log(x));
}

// ============ PROTOTIPOS DE FUNCIONES ============

// Calcula integral usando función matemática
void simpsonFunc();

// Calcula integral usando tabla de datos (manual o CSV)
void simpsonTable();

// Verifica si los puntos están equiespaciados
bool esEquiespaciada(const double x[], int n);

typedef struct {
    double *x;
    double *y;
    int puntos;
} Tabla;

int main(int argc, char const *argv[])
{
    int opcion = 0;
    printf("Bienvenido al programa para calcular integrales (Simpson) - v3\n");
    printf("=============================================================\n");
    printf("¿Cómo desea calcular la integral?\n");
    printf("  1) Usar función matemática\n");
    printf("  2) Ingresar tabla de datos\n");
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

    printf("\n--- MODO: INTEGRACIÓN POR FUNCIÓN MATEMÁTICA ---\n");
    printf("Ingrese el limite inferior de la integral: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior de la integral: ");
    scanf("%lf", &b);
    printf("Ingrese la cantidad de subintervalos (n DEBE SER PAR!): ");
    scanf("%d", &n);

    // Validación del número de subintervalos
    if (n % 2 != 0) {
        printf("ERROR: debe ser un numero PAR de intervalos\n");
        return;
    }

    // Aplicar regla de Simpson compuesta
    h = (b - a) / n;
    suma = func(a) + func(b);

    // Términos con coeficiente 4
    for (int i = 1; i < n; i += 2) {
        suma += 4.0 * func(a + i * h);
    }
    // Términos con coeficiente 2
    for (int i = 2; i < n; i += 2) {
        suma += 2.0 * func(a + i * h);
    }

    res = (h / 3.0) * suma;
    printf("\nEl resultado de la integracion es: %.10f\n", res);
}

bool esEquiespaciada(const double x[], int n) {
    if (n < 2) return true;
    
    double h = x[1] - x[0];
    const double EPS = 1e-8;
    
    // Primer intervalo debe ser válido
    if (fabs(h) < EPS) return false;
    
    // Verificar que todos los intervalos tengan el mismo tamaño
    for (int i = 2; i < n; i++) {
        if (fabs((x[i] - x[i-1]) - h) > EPS) {
            return false;
        }
    }
    return true;
}

// Calcula integral por Simpson compuesta en una tabla equiespaciada
static double simpsonCompuesto(const double *x, const double *y, int puntos) {
    int n_sub = puntos - 1;
    double h = x[1] - x[0];
    double suma = y[0] + y[puntos - 1];
    
    // Coeficientes 4 para índices impares
    for (int i = 1; i < puntos - 1; i += 2) suma += 4.0 * y[i];
    
    // Coeficientes 2 para índices pares
    for (int i = 2; i < puntos - 1; i += 2) suma += 2.0 * y[i];
    
    return (h / 3.0) * suma;
}

// Carga tabla de datos manualmente desde teclado
void cargarTablaManual(double x[], double y[], int &puntos) {
    printf("Ingrese la cantidad de puntos para la tabla: ");
    scanf("%d", &puntos);
    
    if (puntos <= 0 || puntos > D) {
        printf("ERROR: cantidad de puntos inválida (máximo %d)\n", D);
        puntos = 0;
        return;
    }
    
    printf("Ingrese los valores de X:\n");
    cargarVectorTeclado(x, puntos);
    printf("Ingrese los valores de Y:\n");
    cargarVectorTeclado(y, puntos);
}

// Lee tabla de datos desde archivo CSV (usa constante RUTA_CSV_DEFECTO)
void cargarTablaCSV(double x[], double y[], int &puntos) {
    printf("Leyendo archivo CSV desde: %s\n", RUTA_CSV_DEFECTO);
    
    // Intentar leer el CSV
    int n_leido = leerTablaCSV(RUTA_CSV_DEFECTO, x, y, D);
    
    if (n_leido <= 0) {
        printf("ERROR: No se pudo leer el archivo CSV o archivo vacío\n");
        printf("Verifica que la ruta sea correcta: %s\n", RUTA_CSV_DEFECTO);
        puntos = 0;
        return;
    }
    
    puntos = n_leido;
    printf("✓ Se cargaron exitosamente %d puntos desde el CSV\n\n", puntos);
}

void simpsonTable(){
    double x[D] = {0.0}, y[D] = {0.0};
    int puntos = 0;
    int opcion_auto = 0;

    printf("\n--- MODO: INTEGRACIÓN POR TABLA DE DATOS ---\n");
    printf("¿Cómo desea ingresar la tabla?\n");
    printf("  1) Cargar manualmente (por teclado)\n");
    printf("  2) Leer desde archivo CSV\n");
    printf("Opción: ");
    scanf("%d", &opcion_auto);

    if (opcion_auto == 1) {
        cargarTablaManual(x, y, puntos);
    } else if (opcion_auto == 2) {
        cargarTablaCSV(x, y, puntos);
    } else {
        printf("Opción inválida\n");
        return;
    }
    
    if (puntos <= 0) {
        printf("ERROR: No se cargaron datos válidos\n");
        return;
    }

    // Mostrar tabla cargada
    printf("La tabla cargada es la siguiente:\n");
    leerVectoresTabla(x, y, puntos);
    printf("\n");

    // Verificar si es equiespaciada y tiene subintervalos pares
    bool equi = esEquiespaciada(x, puntos);
    int n_sub_original = puntos - 1;

    if (equi && (n_sub_original % 2 == 0)) {
        printf("✓ Tabla es equiespaciada con subintervalos pares\n");
        printf("Opciones:\n");
        printf("  1) Usar tabla original (Simpson directo)\n");
        printf("  2) Generar nueva tabla con spline (n elegido)\n");
        printf("Seleccione opción (1/2): ");
        int opt = 1;
        if (scanf("%d", &opt) != 1) opt = 1;

        if (opt == 1) {
            double integral = simpsonCompuesto(x, y, puntos);
            printf("\nEl resultado de la integracion es: %.10f\n", integral);
            return;
        }
    } else if (equi && (n_sub_original % 2 != 0)) {
        printf("⚠ Tabla equiespaciada pero con %d subintervalos (impar)\n", n_sub_original);
        printf("Se usará spline cúbico para generar tabla con subintervalos pares\n\n");
    } else {
        printf("⚠ Tabla NO equiespaciada -> se usará interpolación con splines\n\n");
    }

    // Definir subintervalos para la tabla interpolada
    printf("¿Desea definir automáticamente la cantidad de subintervalos?\n");
    printf("  1) Sí, definir automáticamente\n");
    printf("  2) No, ingresar manualmente\n");
    printf("Opción: ");
    scanf("%d", &opcion_auto);

    int n_sub = 0;
    if (opcion_auto == 1) {
        // Si puntos-1 es par, usamos puntos-1; si es impar, sumamos 1
        if ((puntos - 1) % 2 == 0) n_sub = puntos - 1;
        else n_sub = puntos;
        printf("Cantidad de subintervalos: %d\n\n", n_sub);
    } else {
        printf("Ingrese la cantidad de subintervalos (debe ser PAR): ");
        scanf("%d", &n_sub);
        if (n_sub % 2 != 0) {
            printf("⚠ %d es impar. Se ajusta a %d para aplicar Simpson\n\n", n_sub, n_sub + 1);
            n_sub += 1;
        }
    }

    // Crear tabla equiespaciada mediante interpolación con spline
    int n_puntos_new = n_sub + 1;
    double *x_new = new double[n_puntos_new];
    double *y_new = new double[n_puntos_new];
    double a = x[0], b = x[puntos - 1];
    double h = (b - a) / n_sub;

    // Generar nuevos puntos X equiespaciados
    x_new[0] = a;
    x_new[n_puntos_new - 1] = b;
    for (int i = 1; i < n_puntos_new - 1; i++) {
        x_new[i] = x_new[0] + (i * h);
    }

    // Interpolar con spline cúbico
    double coeficientes[MAX_SEGMENTOS][4] = {0.0};
    spline_calcular_coeficientes(x, y, puntos, coeficientes);
    spline_evaluar_multiples_puntos(x, puntos, coeficientes, x_new, n_puntos_new, y_new);

    // Mostrar tabla interpolada
    printf("Tabla interpolada y equiespaciada:\n");
    leerVectoresTabla(x_new, y_new, n_puntos_new);

    // Calcular integral con Simpson sobre tabla interpolada
    double integral = simpsonCompuesto(x_new, y_new, n_puntos_new);
    printf("\nEl resultado de la integracion es: %.10f\n", integral);

    // Liberar memoria dinámica
    delete[] x_new;
    delete[] y_new;
}
