/*
================================================================================
            INTERPOLACIÓN POLINÓMICA DE LAGRANGE
================================================================================

MÉTODO NUMÉRICO: Interpolación de Lagrange

CONSISTE EN:
- Dados n puntos (x_i, y_i), encontrar un polinomio P(x) de grado n-1 que pase 
  exactamente por todos los puntos
- El polinomio se construye como combinación lineal de polinomios base L_k(x)
- Fórmula: P(x) = Σ [y_k * L_k(x)] para k = 0 hasta n-1
- Polinomios base: L_k(x) = Π [(x - x_i)/(x_k - x_i)] para i ≠ k

=======================================================================
*/

#include <stdio.h>

#define n 3  // Cantidad de puntos (índices 0 hasta n-1)

// Prototipos de funciones
void cargarVector(double x[n], double y[n]);
void leerVector(double x[n], double y[n]);
void lagrange(double x[n], double y[n]);
void mostrarPolinomio(double x[n], double y[n]);

int main(int argc, char const *argv[])
{
    double x[n], y[n];  // Arreglos para almacenar los puntos (x_i, y_i)
    
    // Flujo principal del programa
    cargarVector(x, y);   // Cargar puntos desde teclado
    leerVector(x, y);     // Mostrar tabla de puntos
    lagrange(x, y);       // Realizar interpolación
    
    return 0;
}

/**
 * Función: cargarVector
 * Propósito: Cargar los n puntos (x_i, y_i) desde entrada estándar
 * Parámetros:
 *   - x[n]: arreglo de coordenadas x
 *   - y[n]: arreglo de coordenadas y (valores de la función)
 */
void cargarVector(double x[n], double y[n]){
    printf("Cargando los %d puntos (x_i, y_i)\n", n);
    
    // Iterar sobre cada punto
    for (int i = 0; i < n; i++)
    {
        printf("ingrese x%d: ", i);    // Solicitar coordenada x
        scanf("%lf", &x[i]);           // Leer como double
        printf("ingrese y%d: ", i);    // Solicitar coordenada y
        scanf("%lf", &y[i]);           // Leer como double
    }
}

/**
 * Función: leerVector
 * Propósito: Mostrar en pantalla la tabla de puntos cargados
 * Parámetros:
 *   - x[n]: arreglo de coordenadas x
 *   - y[n]: arreglo de coordenadas y
 */
void leerVector(double x[n], double y[n]){
    printf("\nTabla de puntos cargados:\n");
    printf("x\t|\ty\t| indice\n");
    printf("--------+-------+--------\n");
    
    // Mostrar cada punto con formato tabular
    for (int i = 0; i < n; i++)
    {
        printf("%.2f\t|\t%.2f\t| %d \n", x[i], y[i], i);
    }
}

/**
 * Función: mostrarPolinomio
 * Propósito: Mostrar la expresión simbólica del polinomio de Lagrange
 * Parámetros:
 *   - x[n]: nodos de interpolación
 *   - y[n]: valores de la función en los nodos
 */
void mostrarPolinomio(double x[n], double y[n]) {
    printf("\nExpresion del polinomio de Lagrange P%d(x):\n", n-1);
    printf("P(x) = ");
    
    int primer_termino = 1;  // Bandera para controlar el signo "+"
    
    // Construir cada término del polinomio: y_k * L_k(x)
    for (int k = 0; k < n; k++) {
        // Agregar signo "+" excepto para el primer término
        if (!primer_termino) {
            printf(" + ");
        }
        
        // Mostrar coeficiente y_k
        printf("%.2f", y[k]);
        
        // Construir el polinomio base L_k(x)
        for (int i = 0; i < n; i++) {
            if (i != k) {
                // Cada factor: (x - x_i)/(x_k - x_i)
                printf(" * ((x - %.2f)/%.2f)", x[i], x[k] - x[i]);
            }
        }
        primer_termino = 0;  // Ya no es el primer término
    }
    printf("\n");
}

/**
 * Función: lagrange
 * Propósito: Calcular la interpolación de Lagrange para un valor xr específico
 * Parámetros:
 *   - x[n]: nodos de interpolación
 *   - y[n]: valores de la función en los nodos
 */
void lagrange(double x[n], double y[n]){
    double suma = 0.0;  // Acumulará el valor del polinomio P(xr)
    double xr = 0.0;    // Valor x donde se quiere interpolar

    // Solicitar el punto de interpolación
    printf("\nIngrese el valor que quiere aproximar por interpolacion: ");
    scanf("%lf", &xr);

    // Encabezado del método
    printf("\n=== INTERPOLACION DE LAGRANGE ===\n");
    printf("Polinomio de grado: %d\n", n-1);

    // Mostrar la forma simbólica del polinomio
    mostrarPolinomio(x, y);

    // VERIFICACIÓN: ¿xr está dentro del rango de interpolación?
    int dentro_rango = 0;
    double x_min = x[0], x_max = x[0];
    
    // Encontrar los valores mínimo y máximo de x
    for (int i = 1; i < n; i++) {
        if (x[i] < x_min) x_min = x[i];
        if (x[i] > x_max) x_max = x[i];
    }
    
    // Determinar si xr está dentro del intervalo [x_min, x_max]
    if (xr >= x_min && xr <= x_max) {
        dentro_rango = 1;
    }
    
    // Mostrar advertencia si es extrapolación
    if (!dentro_rango) {
        printf("\nADVERTENCIA: xr = %.2f está fuera del rango [%.2f, %.2f]\n", 
               xr, x_min, x_max);
        printf("   Esto es EXTRAPOLACION (mayor error posible)\n");
    } else {
        printf("xr = %.2f está dentro del rango [%.2f, %.2f]\n", 
               xr, x_min, x_max);
    }

    printf("\nCalculando P(%.2f)...\n", xr);
    
    // ALGORITMO PRINCIPAL: Cálculo del polinomio de Lagrange
    for (int k = 0; k < n; k++)  // Para cada término del polinomio
    {
        double prod = 1.0;  // Acumulará el polinomio base L_k(xr)
        
        // Calcular L_k(xr) = Π [(xr - x_i)/(x_k - x_i)] para i ≠ k
        for (int i = 0; i < n; i++)
        {
            if (i != k)  // Excluir el índice k del producto
            {
                // Verificar que no hay nodos repetidos (evitar división por cero)
                if (x[k] == x[i]) {
                    fprintf(stderr, "Error: x[%d] = x[%d] = %.2f (nodos repetidos)\n", 
                            k, i, x[k]);
                    fprintf(stderr, "No se puede interpolar con nodos repetidos.\n");
                    return;
                }
                
                // Calcular factor: (xr - x_i)/(x_k - x_i)
                prod = prod * ((xr - x[i]) / (x[k] - x[i]));
            }
        }
        
        // Sumar el término: y_k * L_k(xr)
        suma = suma + y[k] * prod;
    }
    
    // MOSTRAR RESULTADOS
    printf("\n=== RESULTADOS ===\n");
    printf("Variable a aproximar xr: %.6f\n", xr);
    printf("Aproximacion P%d(xr): \n", n-1);
    printf("  Notacion decimal:    %.10f\n", suma);      // Formato decimal
    printf("  Notacion cientifica: %.6e\n", suma);       // Formato científico
    
    // Mostrar nuevamente los datos utilizados
    printf("\nDatos utilizados para la interpolacion:\n");
    leerVector(x, y);
    
    // Recordatorio final si fue extrapolación
    if (!dentro_rango) {
        printf("\nRecordatorio: Estás haciendo EXTRAPOLACION\n");
        printf("   El error puede ser mayor que en interpolacion\n");
    }
}