    #include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ===================== Configuración ===================== */
#define n   3           /* cantidad de puntos -> grado = n-1 */
#define EPS 1e-12       /* tolerancia para pivotes ~ 0 */

/* ===================== Prototipos ===================== */
/* I/O de puntos */
void cargarVector(double x[n], double y[n]);
void leerVector(const double x[n], const double y[n]);

/* Vandermonde */
void cargarMatriz(const double x[n], double V[n][n]);  /* V[i][j] = x_i^j */
void leerMatriz(const double V[n][n], const double y[n]);

/* Gauss con pivoteo parcial */
int  gauss(double A[n][n], double B[n], double sol[n]); /* retorna 1 si OK, 0 si singular */

/* Interpolación: evalúa P(x) con coeficientes 'a' */
void interpolar(const double U[n][n], const double y[n], const double a[n]);

/* Utilitarios */
static void swap_rows(double A[n][n], double B[n], int r1, int r2);
static int  has_duplicate_x(const double x[n]);
static double eval_horner(int grado, const double a[], double xr);

/* ===================== Programa principal ===================== */
int main(void)
{
    double x[n], y[n];      /* datos (x_i, y_i) */
    double V[n][n];         /* matriz de Vandermonde */
    double a[n];            /* coeficientes del polinomio P(x) = a0 + a1 x + ... + a_{n-1} x^{n-1} */

    printf("Bienvenido: Interpolacion polinomica (forma funcional: Vandermonde + Gauss)\n\n");

    /* 1) Cargar puntos */
    cargarVector(x, y);

    if (has_duplicate_x(x)) {
        fprintf(stderr, "ERROR: hay x_i repetidos. La Vandermonde es singular.\n");
        return 1;
    }

    printf("\nPuntos cargados:\n");
    leerVector(x, y);

    /* 2) Armar Vandermonde V[i,j] = x_i^j */
    cargarMatriz(x, V);

    printf("\nSistema Vandermonde (V | y):\n");
    leerMatriz(V, y);

    /* 3) Resolver V * a = y por Gauss con pivoteo parcial */
    if (!gauss(V, y, a)) {
        fprintf(stderr, "\nERROR: sistema singular o mal condicionado. No se puede resolver.\n");
        return 1;
    }

    /* 4) Interpolar: pedir xr y evaluar P(xr) */
    interpolar(V, y, a);

    return 0;
}

/* ===================== Implementaciones ===================== */
/* -------- I/O puntos -------- */
void cargarVector(double x[n], double y[n]){
    printf("Vamos a cargar %d puntos (x_i, y_i):\n", n);
    for (int i = 0; i < n; i++) {
        printf("x[%d] = ", i);
        if (scanf("%lf", &x[i]) != 1) exit(1);
        printf("y[%d] = ", i);
        if (scanf("%lf", &y[i]) != 1) exit(1);
    }
}

void leerVector(const double x[n], const double y[n]){
    printf("   i\t        x_i\t\t        y_i\n");
    for (int i = 0; i < n; i++)
        printf("  %2d\t% .10f\t% .10f\n", i, x[i], y[i]);
}

/* -------- Vandermonde -------- */
/* Más eficiente que usar pow: construimos x_i^j acumulando potencias */
void cargarMatriz(const double x[n], double V[n][n]){
    for (int i = 0; i < n; i++) {
        double pot = 1.0;           /* x_i^0 */
        for (int j = 0; j < n; j++) {
            V[i][j] = pot;          /* x_i^j */
            pot *= x[i];            /* prepara x_i^{j+1} */
        }
    }
}

void leerMatriz(const double V[n][n], const double y[n]){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%10.6f ", V[i][j]);
        printf("| %10.6f\n", y[i]);
    }
}

/* -------- Gauss con pivoteo parcial --------
   Resuelve A * sol = B. Modifica A (queda triangular sup.) y B in-place.
   Retorna 1 si OK, 0 si singular/mal condicionado.
*/
int gauss(double A[n][n], double B[n], double sol[n]){
    /* 1) Eliminación hacia adelante + pivoteo parcial SIEMPRE */
    for (int i = 0; i < n; ++i) {
        /* (a) elegir el mejor pivote en la columna i */
        int piv = i;
        double maxabs = fabs(A[i][i]);
        for (int r = i + 1; r < n; ++r) {
            double v = fabs(A[r][i]);
            if (v > maxabs) { maxabs = v; piv = r; }
        }
        /* (b) si el mejor pivote es ~0 => columna casi nula => singular */
        if (maxabs < EPS) {
            /* No se puede continuar */
            return 0;
        }
        /* (c) traer el pivote a la fila i (swap en A y en B) */
        if (piv != i) swap_rows(A, B, i, piv);

        /* (d) eliminar por debajo del pivote (dejar ceros en columna i, filas r>i) */
        double aii = A[i][i];
        for (int r = i + 1; r < n; ++r) {
            double factor = A[r][i] / aii;
            A[r][i] = 0.0;                   /* forzamos el cero exacto */
            for (int j = i + 1; j < n; ++j)
                A[r][j] -= factor * A[i][j];
            B[r] -= factor * B[i];
        }
    }

    /* 2) Retrosustitución: U * sol = B con U triangular superior */
    for (int i = n - 1; i >= 0; --i) {
        double s = B[i];
        for (int j = i + 1; j < n; ++j)
            s -= A[i][j] * sol[j];

        double piv = A[i][i];
        if (fabs(piv) < EPS) return 0;   /* por si acaso */
        sol[i] = s / piv;
    }

    return 1; /* OK */
}

/* -------- Interpolación (evalúa P con Horner) -------- */
void interpolar(const double U[n][n], const double y[n], const double a[n]){
    (void)U; (void)y; /* U y y ya se mostraron antes; si querés mostrarlos acá, sacá estas líneas */

    double xr = 0.0;
    printf("\nIngrese x* para evaluar P(x*): ");
    if (scanf("%lf", &xr) != 1) {
        fprintf(stderr, "Entrada invalida.\n");
        return;
    }

    /* Horner: O(n), mucho más estable que sumar a[i]*xr^i con pow */
    double px = eval_horner(n - 1, a, xr);

    printf("\nCoeficientes a (a0..a%d):\n", n-1);
    for (int i = 0; i < n; ++i)
        printf("a[%d] = %.10f\n", i, a[i]);

    printf("\nValor a interpolar xr: %.10f\n", xr);
    printf("Aproximacion P(xr) ≈ %.10f\n", px);
}

/* -------- Utilitarios -------- */
static void swap_rows(double A[n][n], double B[n], int r1, int r2){
    if (r1 == r2) return;
    for (int j = 0; j < n; ++j) {
        double tmp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = tmp;
    }
    double tb = B[r1]; B[r1] = B[r2]; B[r2] = tb;
}

static int has_duplicate_x(const double x[n]){
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (fabs(x[i] - x[j]) < EPS) return 1;
    return 0;
}

/* Horner para P(x) = a0 + a1 x + ... + a_grado x^grado */
static double eval_horner(int grado, const double a[], double xr){
    double acc = a[grado];
    for (int i = grado - 1; i >= 0; --i)
        acc = acc * xr + a[i];
    return acc;
}
