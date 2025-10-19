#ifndef SPLINE_CUBICA_H
#define SPLINE_CUBICA_H

// Aproxima valores usando spline cúbica
// x[], y[]: tabla original de tamaño d
// d: cantidad de datos originales
// x_interp[]: puntos donde se desea interpolar (tamaño n_interp)
// y_interp[]: resultados de la interpolación (tamaño n_interp)
// n_interp: cantidad de puntos a interpolar
void splineCubicaAproximar(
    double x[], double y[], int d,
    double x_interp[], double y_interp[], int n_interp
);

#endif