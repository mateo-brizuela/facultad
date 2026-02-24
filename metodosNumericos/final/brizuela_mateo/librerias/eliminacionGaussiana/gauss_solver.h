// gauss_solver.h (versión modificada)
#ifndef GAUSS_SOLVER_H
#define GAUSS_SOLVER_H

// ============================================================================
// CONFIGURACIÓN FLEXIBLE: La librería se adapta al programa
// ============================================================================

/**
 * @note IMPORTANTE: Para usar esta librería, debe definirse MAX_SISTEMA_PROGRAMA
 *       en el programa principal antes de incluir este header.
 * 
 *       Ejemplo en el programa:
 *       #define MAX_SISTEMA_PROGRAMA 10
 *       #include "gauss_solver.h"
 */

// La librería usa el tamaño máximo definido por el programa
#ifndef MAX_PROGRAMA
#define MAX_PROGRAMA 24  // Valor por defecto para compatibilidad
#endif

#define N MAX_PROGRAMA

// ============================================================================
// DECLARACIONES DE FUNCIONES
// ============================================================================

// Funciones originales (tamaño fijo)
int gauss_solve(double A[][N], double B[], double X[], double &determinant);
double compute_residual(double A[][N], double X[], double B[]);

// Funciones dinámicas (se mantienen igual)
int gauss_solve_dynamic(int n, double** A, double* B, double* X, double& determinant);
double compute_residual_dynamic(int n, double** A, double* X, double* B);

// ============================================================================
// FUNCIONES AUXILIARES PARA ENTRADA DE DATOS
// ============================================================================

/**
 * @brief Carga un vector con datos ingresados por teclado
 * @param vector Vector donde se almacenarán los datos
 * @param tamaño Tamaño del vector
 */
void cargarVectorTeclado(double vector[], int tamaño);

/**
 * @brief Muestra en pantalla los elementos de un vector
 * @param vector Vector a mostrar
 * @param tamaño Tamaño del vector
 */
void leerVectorPantalla(double vector[], int tamaño);

/**
 * @brief Carga una matriz con datos ingresados por teclado
 * @param matriz Matriz donde se almacenarán los datos
 * @param filas Número de filas de la matriz
 * @param columnas Número de columnas de la matriz
 */
void cargarMatrizTeclado(double matriz[][N], int filas, int columnas);

/**
 * @brief Muestra en pantalla los elementos de una matriz
 * @param matriz Matriz a mostrar
 * @param filas Número de filas de la matriz
 * @param columnas Número de columnas de la matriz
 */
void leerMatrizPantalla(double matriz[][N], int filas, int columnas);


/**
 * @brief Muestra en pantalla los elementos de dos vectores en formato de tabla
 * @param x Vector de coordenadas x
 * @param y Vector de coordenadas y  
 * @param tamaño Tamaño de los vectores
 */
void leerVectoresTabla(double x[], double y[], int tamaño);

#endif