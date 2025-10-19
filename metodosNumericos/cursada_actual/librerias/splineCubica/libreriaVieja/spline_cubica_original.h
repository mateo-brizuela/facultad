#ifndef SPLINE_CUBICA_H
#define SPLINE_CUBICA_H

#include "../eliminacionGaussiana/gauss_solver.h"

// Constantes para tamaños máximos
#define MAX_PUNTOS 6
#define MAX_SEGMENTOS (MAX_PUNTOS - 1)
#define MAX_ECUACIONES (4 * MAX_SEGMENTOS)

/**
 * @brief Calcula los coeficientes de los splines cúbicos naturales
 * @param x Vector de coordenadas x de los puntos (tamaño: d)
 * @param y Vector de coordenadas y de los puntos (tamaño: d)  
 * @param d Cantidad de puntos (debe ser >= 2 y <= MAX_PUNTOS)
 * @param coeficientes Matriz donde se guardan los coeficientes (tamaño: MAX_SEGMENTOS × 4)
 *                    Formato: Cada fila i contiene [a_i, b_i, c_i, d_i] para el spline i
 *                    - Se utilizan las primeras (d-1) filas
 *                    - Ejemplo: Para 5 puntos, se usan filas 0 a 3
 * @return 0 si éxito, -1 si error
 * 
 * @note Los puntos x deben estar ordenados en forma creciente
 * @note La matriz coeficientes debe declararse como: double coeficientes[MAX_SEGMENTOS][4]
 */
int spline_calcular_coeficientes(double x[], double y[], int d, double coeficientes[][4]);

/**
 * @brief Evalúa el spline en un punto específico
 * @param x Vector de coordenadas x original (tamaño: d)
 * @param d Cantidad de puntos
 * @param coeficientes Matriz de coeficientes calculados (tamaño: MAX_SEGMENTOS × 4)
 * @param x_punto Valor x donde evaluar el spline
 * @param y_resultado Puntero donde se guarda el resultado y = S(x_punto)
 * @return Índice del segmento usado si éxito, -1 si x_punto está fuera de rango
 */
int spline_evaluar_punto(double x[], int d, double coeficientes[][4], 
                        double x_punto, double* y_resultado);

/**
 * @brief Evalúa el spline en múltiples puntos (versión simplificada)
 * @param x Vector de coordenadas x original (para determinar intervalos)
 * @param d Cantidad de puntos originales
 * @param coeficientes Matriz de coeficientes calculados (tamaño: MAX_SEGMENTOS × 4)
 * @param x_aproximar Vector de puntos x a aproximar
 * @param num_aproximaciones Cantidad de aproximaciones a calcular
 * @param y_resultados Vector donde se guardan los resultados y = S(x)
 * 
 * @note Esta función muestra en pantalla los cálculos paso a paso
 * @note Similar a la función aproximarSpline de tu código original
 */
void spline_evaluar_multiples_puntos(double x[], int d, double coeficientes[][4],
                                   double x_aproximar[], int num_aproximaciones,
                                   double y_resultados[]);

/**
 * @brief Imprime las ecuaciones de todos los segmentos del spline
 * @param x Vector de coordenadas x original (tamaño: d)
 * @param d Cantidad de puntos
 * @param coeficientes Matriz de coeficientes calculados (tamaño: MAX_SEGMENTOS × 4)
 */
void spline_imprimir_ecuaciones(double x[], int d, double coeficientes[][4]);

#endif