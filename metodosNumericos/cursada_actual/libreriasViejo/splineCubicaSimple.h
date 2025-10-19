#ifndef SPLINE_CUBICA_SIMPLE_H
#define SPLINE_CUBICA_SIMPLE_H

// Arma el sistema lineal para el spline cúbico natural
void armarMatrizSimple(double x[], double y[], int d, double matriz[][4*(4-1)], double vector[]);

// Resuelve el sistema lineal Ax = B por Gauss simple
void gaussSimple(double A[][4*(4-1)], double B[], double x[], int n);

// Evalúa el spline cúbico en los puntos x_interp[]
void aproximarSplineSimple(double x[], double coef[], int d, double x_interp[], double y_interp[], int n);

#endif