#include <stdio.h>
#include <math.h>

double f(double x) {
    return 20.0*x*x*x - 47.0*x*x + 26.0*x - 43.0;
}

int main() {
    double x0, x1;
    int cifras = 6;                 // cifras decimales deseadas
    const int maxIter = 100;

    printf("Metodo de la secante\n");
    printf("x0: "); scanf("%lf", &x0);
    printf("x1: "); scanf("%lf", &x1);
    printf("Cifras de precision (>=1): ");
    if (scanf("%d", &cifras) != 1 || cifras < 1) cifras = 6;
    double tol = pow(10.0, -cifras);

    double fx0 = f(x0), fx1 = f(x1);
    int iter = 0;
    while (iter < maxIter) {
        double denom = (fx1 - fx0);
        if (fabs(denom) < 1e-14) {
            printf("Denominador casi cero. Abortando.\n");
            return 1;
        }
        double x2 = x1 - fx1 * (x1 - x0) / denom;
        double fx2 = f(x2);

        printf("iter %2d: x=%.10f, f(x)=%.3e, |dx|=%.3e\n",
               iter, x2, fx2, fabs(x2 - x1));

        if (fabs(x2 - x1) < tol || fabs(fx2) < tol) {
            printf("Convergio en %d iteraciones: raiz ≈ %.10f (tol=%.1e)\n", iter+1, x2, tol);
            return 0;
        }

        x0 = x1; fx0 = fx1;
        x1 = x2; fx1 = fx2;
        ++iter;
    }
    printf("No convergio en %d iteraciones (tol=%.1e)\n", maxIter, tol);
    return 0;
}
