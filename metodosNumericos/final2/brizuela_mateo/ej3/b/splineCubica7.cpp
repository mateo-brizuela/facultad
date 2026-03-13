#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "../../librerias/eliminacionGaussiana/gauss_solver.h"
#include "../../librerias/io/exportarResultados.h"

/*
  Versión: splineCubica7
  Objetivo: construir splines cúbicos naturales a partir de d puntos,
            resolver el sistema lineal para los 4*m coeficientes
            y proporcionar utilidades para evaluar el spline y
            generar tablas (inciso b) con opciones de discretización.
*/

/* ---------- CONFIGURACIÓN ---------- */
/* d: número de puntos de entrada (nodos) */
/* n: número de incógnitas del sistema lineal = 4*(d-1) */
/* m: número de intervalos = d-1 (cada intervalo tiene 4 coeficientes a,b,c,d) */
#define d 7
#define n 4*(d-1)
#define m d-1

/* ----- Prototipos ----- */
/* Entrada / armado sistema */
void cargarVector(double x[d], double y[d]);                      // lee los d pares (x,y)
void leerVector(double x[d], double y[d]);                        // imprime los pares leídos
void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]); // arma A*x=b
void leerMatriz(double A[n][n], double B[n]);                    // imprime A y B para depurar

/* Evaluación / tablas */
/* evaluarSplineEn: dado xval, nodos x_nodes y vector de coeficientes (4*m),
   devuelve el valor S(xval) */
double evaluarSplineEn(double xval, const double x_nodes[d], const double coeficientes[n]);
/* f_exact: función exacta del enunciado (para comparar/tabla) */
double f_exact(double xi);
/* generarTablaEquiespaciada: arma una tabla de 'puntos' equiespaciados en [x0, x_{d-1}] */
void generarTablaEquiespaciada(const double x_nodes[d], const double coeficientes[n], int puntos);
/* generarTablaPorPaso: arma una tabla usando un paso fijo h en [x0, x_{d-1}] */
void generarTablaPorPaso(const double x_nodes[d], const double coeficientes[n], double h);
/* tablaIncisoB: wrapper que genera la tabla del inciso b (conservar d puntos) */
void tablaIncisoB(const double x_nodes[d], const double coeficientes[n]);
/* tablaEquiespaciadaInteractiva: permite elegir N subintervalos o paso h */
void tablaEquiespaciadaInteractiva(const double x_nodes[d], const double coeficientes[n]);
/* modoInteractivo: permite evaluar valores arbitrarios hasta que el usuario corte */
void modoInteractivo(const double x_nodes[d], const double coeficientes[n]);
/* mostrarCoeficientes: imprime los coeficientes a,b,c,d por tramo para inspección */
void mostrarCoeficientes(const double x_nodes[d], const double coeficientes[n]);

/* ----- main ----- */
int main(int argc, char const *argv[])
{
    /* x, y: arrays con los nodos y valores dados por el usuario */
    double x[d], y[d];
    /* matriz, vector: sistema A * incognitas = vector */
    double matriz[n][n], vector[n];
    /* incognitas: vector resultado con los 4*m coeficientes ordenados por tramo:
       [a0,b0,c0,d0, a1,b1,c1,d1, ...] */
    double incognitas[n];
    /* det: (opcional) valor del determinante o parámetro de retorno del solver */
    double det = 1.0;

    cargarVector(x,y);                       // lee d puntos
    armarMatriz(x,y,matriz,vector);          // arma el sistema lineal

    /* El solver de Gauss en este proyecto espera double** (matriz dinámica),
       por eso convertimos la matriz estática antes de llamar al solver. */
    double **A = new double*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new double[n];
        for (int j = 0; j < n; ++j) A[i][j] = matriz[i][j];
    }

    /* gauss_solve_dynamic: firma esperada
       int gauss_solve_dynamic(int n, double** A, double* b, double* x, double &det);
       ajustar llamada si tu header/implementación difiere. */
    int status = gauss_solve_dynamic(n, A, vector, incognitas, det);
    if (status != 0) {
        printf("gauss_solve_dynamic devolvió error %d\n", status);
    }

    /* liberar memoria dinámica usada para la llamada al solver */
    for (int i = 0; i < n; ++i) delete[] A[i];
    delete[] A;

    /* Usar las utilidades implementadas */
    mostrarCoeficientes(x, incognitas);          // imprime polinomios por tramo
    tablaEquiespaciadaInteractiva(x, incognitas); // elegir N o h
    modoInteractivo(x, incognitas);              // interacción para evaluar valores arbitrarios

    return 0;
}

/* ----- implementaciones: entrada / armado ----- */

void cargarVector(double x[d], double y[d]){
    /* Lectura interactiva de los d pares (x,y). Los nodos deben estar ordenados
       en forma creciente en x para que la búsqueda de intervalo funcione correctamente. */
    printf("=== CARGA DE DATOS PARA SPLINES CUBICOS ===\n");
    for (int i = 0; i < d; i++) {
        printf("Ingrese x[%d]: ", i); scanf("%lf", &x[i]);
        printf("Ingrese y[%d]: ", i); scanf("%lf", &y[i]);
    }
    printf("\nDatos ingresados:\n");
    leerVector(x,y);
}

void leerVector(double x[d], double y[d]){
    /* Imprime los pares (x_i, y_i) con el índice para verificación */
    printf("x\t|\ty\n");
    for (int i = 0; i < d; i++)
        printf("%.6f\t|\t%.6f | indice: %d \n", x[i], y[i], i);
    printf("\n");
}

void armarMatriz(double x[d], double y[d], double matriz[n][n], double vector[n]) {
    /*
      Construye el sistema lineal para splines cúbicos naturales.
      Ecuaciones incluidas:
       - Interpolación en los extremos de cada tramo: S_k(x_k)=y_k, S_k(x_{k+1})=y_{k+1}
         → 2*m ecuaciones
       - Continuidad de primera derivada en nodos interiores: S_k'(x_{k+1}) = S_{k+1}'(x_{k+1})
         → m-1 ecuaciones
       - Continuidad de segunda derivada en nodos interiores: S_k''(x_{k+1}) = S_{k+1}''(x_{k+1})
         → m-1 ecuaciones
       - Condiciones naturales (borde): S_0''(x0)=0 y S_{m-1}''(xm)=0
         → 2 ecuaciones
      Total: 2*m + (m-1) + (m-1) + 2 = 4*m = n ecuaciones (coincide con número de incógnitas).
      Orden de incógnitas: a0,b0,c0,d0, a1,b1,c1,d1, ...
    */

    /* Inicializar a cero */
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) matriz[r][c] = 0.0;
        vector[r] = 0.0;
    }

    int row = 0;

    /* 1) Interpolación en extremos de cada tramo */
    for (int k = 0; k < m; ++k) {
        int c = 4*k;               // índice base de coeficientes para tramo k: a=b[c], b=b[c+1], ...
        double xk = x[k], xk1 = x[k+1];

        /* S_k(x_k) = y_k */
        matriz[row][c]   = xk*xk*xk;
        matriz[row][c+1] = xk*xk;
        matriz[row][c+2] = xk;
        matriz[row][c+3] = 1.0;
        vector[row] = y[k];
        row++;

        /* S_k(x_{k+1}) = y_{k+1} */
        matriz[row][c]   = xk1*xk1*xk1;
        matriz[row][c+1] = xk1*xk1;
        matriz[row][c+2] = xk1;
        matriz[row][c+3] = 1.0;
        vector[row] = y[k+1];
        row++;
    }

    /* 2) Continuidad de primera derivada en nodos interiores:
       S_k'(xi) = 3*a_k*xi^2 + 2*b_k*xi + c_k
       se pone igualdad entre tramo izquierdo y derecho (restando términos del derecho). */
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k, cR = 4*(k+1);
        matriz[row][cL]   = 3 * xi * xi;   // 3*a_k
        matriz[row][cL+1] = 2 * xi;        // 2*b_k
        matriz[row][cL+2] = 1.0;           // c_k
        matriz[row][cR]   = -3 * xi * xi;  // -3*a_{k+1}
        matriz[row][cR+1] = -2 * xi;       // -2*b_{k+1}
        matriz[row][cR+2] = -1.0;          // -c_{k+1}
        vector[row] = 0.0;
        row++;
    }

    /* 3) Continuidad de segunda derivada en nodos interiores:
       S''(x) = 6*a*x + 2*b */
    for (int k = 0; k < m-1; k++) {
        double xi = x[k+1];
        int cL = 4*k, cR = 4*(k+1);
        matriz[row][cL]   = 6 * xi;    // 6*a_k
        matriz[row][cL+1] = 2.0;       // 2*b_k
        matriz[row][cR]   = -6 * xi;   // -6*a_{k+1}
        matriz[row][cR+1] = -2.0;      // -2*b_{k+1}
        vector[row] = 0.0;
        row++;
    }

    /* 4) Condiciones naturales en extremos: S_0''(x0)=0 y S_{m-1}''(xm)=0 */
    matriz[row][0] = 6 * x[0]; matriz[row][1] = 2.0; vector[row] = 0.0; row++;
    int lastBlock = 4*(m-1);
    matriz[row][lastBlock] = 6 * x[m]; matriz[row][lastBlock+1] = 2.0; vector[row] = 0.0;

    printf("=== SISTEMA LINEAL CONSTRUIDO ===\n");
    leerMatriz(matriz, vector);
}

void leerMatriz(double A[n][n], double B[n]){
    /* Imprime la matriz del sistema A y el vector B (útil para depuración) */
    printf("Matriz del sistema (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%10.4f ", A[i][j]);
        printf(" | %12.6f\n", B[i]);
    }
    printf("\n");
}

/* ----- implementaciones: evaluación / tablas ----- */

double evaluarSplineEn(double xval, const double x_nodes[d], const double coeficientes[n]) {
    /*
      Devuelve S(xval) evaluando los coeficientes del tramo correspondiente.
      x_nodes: array con los nodos originales (longitud d)
      coeficientes: vector con 4*m valores en el orden [a0,b0,c0,d0, a1,...].
    */
    int intervalo = -1;
    /* si xval está fuera del rango, devolvemos valor usando el primer/último tramo */
    if (xval <= x_nodes[0]) intervalo = 0;
    else if (xval >= x_nodes[d-1]) intervalo = m-1;
    else {
        for (int k = 0; k < m; ++k) {
            if (xval >= x_nodes[k] && xval <= x_nodes[k+1]) { intervalo = k; break; }
        }
        if (intervalo == -1) intervalo = m-1; // seguridad
    }

    int base = 4 * intervalo; // índice del coeficiente 'a' del tramo encontrado
    double a = coeficientes[base];     // coef. cúbico en tramo
    double b = coeficientes[base+1];   // coef. cuadrático
    double c = coeficientes[base+2];   // coef. lineal
    double dco = coeficientes[base+3]; // término independiente
    double xr = xval;
    return a*xr*xr*xr + b*xr*xr + c*xr + dco;
}

double f_exact(double xi) {
    /* Función exacta del enunciado:
       f(x) = ln(x^2 + 1) - sin(x)
       (se usa para comparar en la tabla del inciso b) */
    return exp(2.0*sin(xi))*(1.0+log(xi));  // log() es logaritmo natural
}

void generarTablaEquiespaciada(const double x_nodes[d], const double coeficientes[n], int puntos) {
    /* Genera e imprime una tabla con 'puntos' equiespaciados en [x0, x_{d-1}].
       Para cada x_i calcula:
         - y_exact = f_exact(x_i)
         - y_interp = evaluarSplineEn(x_i,...)
         - err = |y_exact - y_interp|
    */
    if (puntos < 2) puntos = 2;
    double *xe = new double[puntos];
    double *ye_exact = new double[puntos];
    double *ye_interp = new double[puntos];
    double *err = new double[puntos];

    double h_eq = (x_nodes[d-1] - x_nodes[0]) / (double)(puntos - 1);
    for (int i = 0; i < puntos; ++i) {
        xe[i] = x_nodes[0] + i * h_eq;                         // nodo equiespaciado i
        ye_exact[i] = f_exact(xe[i]);                          // valor exacto
        ye_interp[i] = evaluarSplineEn(xe[i], x_nodes, coeficientes); // aproximación spline
        err[i] = fabs(ye_exact[i] - ye_interp[i]);             // error absoluto
    }

    printf("\n=== TABLA EQUIDISTANTE (puntos = %d) ===\n", puntos);
    printf(" i\t    x_i\t      y_exact\t   y_interp\t   |error|\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < puntos; ++i) {
        printf("%2d\t%10.6f\t%12.8f\t%12.8f\t%12.8f\n", i, xe[i], ye_exact[i], ye_interp[i], err[i]);
    }

    // Exportar tabla a archivo
    exportarTablaComparativa("spline_equiespaciada", xe, ye_exact, ye_interp, err, puntos);

    // exportar tabla csv para lectura en otros programas 
    exportarTablaCSV("spline_equiespaciada", xe, ye_interp, puntos);

    delete[] xe; delete[] ye_exact; delete[] ye_interp; delete[] err;
}

void generarTablaPorPaso(const double x_nodes[d], const double coeficientes[n], double h) {
    /* Genera e imprime una tabla con paso fijo h en [x0, x_{d-1}] */
    if (h <= 0.0) return;
    const double eps = 1e-12;
    double a = x_nodes[0];
    double b = x_nodes[d-1];

    int puntos = 0;
    double xt = a;
    while (xt <= b + eps) { ++puntos; xt += h; }
    if (puntos < 2) puntos = 2;

    double *xe = new double[puntos];
    double *ye_exact = new double[puntos];
    double *ye_interp = new double[puntos];
    double *err = new double[puntos];

    for (int i = 0; i < puntos; ++i) {
        double xi = a + i * h;
        if (xi > b) xi = b; // seguridad numérica
        xe[i] = xi;
        ye_exact[i] = f_exact(xe[i]);
        ye_interp[i] = evaluarSplineEn(xe[i], x_nodes, coeficientes);
        err[i] = fabs(ye_exact[i] - ye_interp[i]);
    }

    printf("\n=== TABLA POR PASO (h = %.6f, puntos = %d) ===\n", h, puntos);
    printf(" i\t    x_i\t      y_exact\t   y_interp\t   |error|\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < puntos; ++i) {
        printf("%2d\t%10.6f\t%12.8f\t%12.8f\t%12.8f\n", i, xe[i], ye_exact[i], ye_interp[i], err[i]);
    }

    // Exportar tabla a archivo
    exportarTablaComparativa("spline_por_paso", xe, ye_exact, ye_interp, err, puntos);

    delete[] xe; delete[] ye_exact; delete[] ye_interp; delete[] err;
}

void tablaIncisoB(const double x_nodes[d], const double coeficientes[n]) {
    /* Inciso b: generar tabla conservando d puntos equiespaciados */
    generarTablaEquiespaciada(x_nodes, coeficientes, d);
}

void tablaEquiespaciadaInteractiva(const double x_nodes[d], const double coeficientes[n]) {
    printf("\n=== TABLA EQUIDISTANTE (ELEGIR DISCRETIZACION) ===\n");
    printf("Seleccione el modo:\n");
    printf("  1) Definir cantidad de subintervalos (N)\n");
    printf("  2) Definir paso h\n");
    printf("Opcion (1/2): ");

    int modo = 1;
    if (scanf("%d", &modo) != 1 || (modo != 1 && modo != 2)) {
        printf("Opcion invalida. Usando modo 1 (por N).\n");
        modo = 1;
    }

    if (modo == 1) {
        int numSubintervalos = 0;
        do {
            printf("N (>=1): ");
            scanf("%d", &numSubintervalos);
            if (numSubintervalos < 1) printf("N debe ser >= 1\n");
        } while (numSubintervalos < 1);
        int puntos = numSubintervalos + 1;
        generarTablaEquiespaciada(x_nodes, coeficientes, puntos);
    } else {
        double h = 0.0;
        double rango = x_nodes[d-1] - x_nodes[0];
        do {
            printf("h (0 < h <= %.6f): ", rango);
            scanf("%lf", &h);
            if (h <= 0.0 || h > rango) printf("h invalido.\n");
        } while (h <= 0.0 || h > rango);
        generarTablaPorPaso(x_nodes, coeficientes, h);
    }
}

void modoInteractivo(const double x_nodes[d], const double coeficientes[n]) {
    /* Modo interactivo: solicita xr y muestra S(xr) usando evaluarSplineEn.
       El bucle continúa hasta que el usuario responda 'n' o se produzca EOF. */
    printf("\n=== MODO INTERACTIVO (evaluar spline) ===\n");
    char cont = 's';
    while (cont == 's' || cont == 'S') {
        double xr;
        printf("Ingrese xr para aproximar: ");
        if (scanf("%lf", &xr) != 1) break;
        double y_approx = evaluarSplineEn(xr, x_nodes, coeficientes);
        printf("Spline(%.6f) = %12.8f\n", xr, y_approx);
        printf("¿Continuar? (s/n): ");
        scanf(" %c", &cont); /* el espacio consume el salto de línea previo */
    }
}

void mostrarCoeficientes(const double x_nodes[d], const double coeficientes[n]) {
    /* Imprime, por tramo, los coeficientes (a,b,c,d) que definen cada polinomio
       en notación científica y decimal */
    printf("\n=== COEFICIENTES DE SPLINES (por tramo) ===\n");
    printf("(mostrados en notación científica y decimal)\n\n");
    for (int k = 0; k < m; ++k) {
        int base = 4*k; // posición inicial de coeficientes del tramo k
        printf("S%d en [%.6f, %.6f]:\n", k, x_nodes[k], x_nodes[k+1]);
        printf("  a (x³) = %.8e  =  %.10f\n", coeficientes[base], coeficientes[base]);
        printf("  b (x²) = %.8e  =  %.10f\n", coeficientes[base+1], coeficientes[base+1]);
        printf("  c (x¹) = %.8e  =  %.10f\n", coeficientes[base+2], coeficientes[base+2]);
        printf("  d (x⁰) = %.8e  =  %.10f\n", coeficientes[base+3], coeficientes[base+3]);
        printf("\n");
    }
}
