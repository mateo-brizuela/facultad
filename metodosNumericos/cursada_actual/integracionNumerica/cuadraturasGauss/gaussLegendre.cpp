// repasar teoria de esta metodo, no se entiende mucho 

#include <stdio.h>
#include <cmath>

// prototipo de funciones
double func(double x){ // funcion matematica
    return exp(x*x);
}

void gauss_legendre();

int main(int argc, char const *argv[])
{
    printf("Bienvenido al programa para calcular integrales (Gauss-Legendre)\n");
    gauss_legendre();
    return 0;
}

void gauss_legendre(){
    double c0 = 0.0, c1 = 0.0, c2 = 0.0, c3 = 0.0, c4 = 0.0, c5 = 0.0; // pesos de cada punto
    double x0 = 0.0, x1 = 0.0, x2 = 0.0, x3 = 0.0, x4 = 0.0, x5 = 0.0; // puntos de evaluacion
    double a = 0.0, b = 0.0; // limites de integracion
    double integral = 0.0; // resultado de la integral
    int n = 0; // cantidad de puntos

    printf("Ingrese el limite inferior de la integral: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior de la integral: ");
    scanf("%lf", &b);
    printf("Ingrese la cantidad de puntos (2 a 6): ");
    scanf("%d", &n);
    if (n < 2 || n > 6) {
        printf("ERROR: la cantidad de puntos debe estar entre 2 y 6.\n");
        return;
    }

    switch (n) {
        case 2: {
            double m = a + 0.5 * (b - a); // xm = (a+b)/2 m se encarga de trasladar el intervalo a la mitad del intervalo original
            double d = 0.5 * (b - a);  // xr = (b-a)/2 d se encarga de escalar el intervalo para que tenga longitud 1
            double x0 = m + d * (-0.577350269); // x0 = primera raiz el -0.577350269 es la raiz de polinomio de legendre de grado 2
            double x1 = m + d * ( 0.577350269); // x1 = segunda raiz
            double c0 = 1.0000000, c1 = 1.0000000; // pesos
            integral = d * (c0 * func(x0) + c1 * func(x1)); // formula de la integral
            break;
        }

        // x0, x1, x2 son las raices del polinomio de legendre de grado 3
        // se multiplican por d para trasladar y escalar el intervalo a [-1,1], 
        //luego se suman a m para trasladar al intervalo original [a,b]

        case 3: {
            double m = a + 0.5 * (b - a);
            double d = 0.5 * (b - a);
            double x0 = m + d * (-0.774596669);
            double x1 = m + d * ( 0.0);
            double x2 = m + d * ( 0.774596669);
            double c0 = 0.5555556, c1 = 0.8888889, c2 = 0.5555556; // pesos para 3 puntos
            integral = d * (c0*func(x0) + c1*func(x1) + c2*func(x2));
            break;
        }

        case 4: {
            double m = a + 0.5 * (b - a);
            double d = 0.5 * (b - a);
            double x0 = m + d * (-0.861136312);
            double x1 = m + d * (-0.339981044);
            double x2 = m + d * ( 0.339981044);
            double x3 = m + d * ( 0.861136312);
            double c0 = 0.3478548, c1 = 0.6521452, c2 = 0.6521452, c3 = 0.3478548;
            integral = d * (c0*func(x0) + c1*func(x1) + c2*func(x2) + c3*func(x3));
            break;
        }

        case 5: {
            double m = a + 0.5 * (b - a);
            double d = 0.5 * (b - a);
            double x0 = m + d * (-0.906179846);
            double x1 = m + d * (-0.538469310);
            double x2 = m + d * ( 0.0);
            double x3 = m + d * ( 0.538469310);
            double x4 = m + d * ( 0.906179846);
            double c0 = 0.2369269, c1 = 0.4786287, c2 = 0.5688889, c3 = 0.4786287, c4 = 0.2369269;
            integral = d * (c0*func(x0) + c1*func(x1) + c2*func(x2) + c3*func(x3) + c4*func(x4));
            break;
        }

        case 6: {
            double m = a + 0.5 * (b - a);
            double d = 0.5 * (b - a);
            double xr = 0.5 * (b - a);
            double x0 = m + d * (-0.932469514);
            double x1 = m + d * (-0.661209386);
            double x2 = m + d * (-0.238619186);
            double x3 = m + d * ( 0.238619186);
            double x4 = m + d * ( 0.661209386);
            double x5 = m + d * ( 0.932469514);
            double c0 = 0.1713245, c1 = 0.3607616, c2 = 0.4679139,
                   c3 = 0.4679139, c4 = 0.3607616, c5 = 0.1713245;
            integral = d * (c0*func(x0) + c1*func(x1) + c2*func(x2) + c3*func(x3) + c4*func(x4) + c5*func(x5));
            break;
        }
    }

    // impresiones solicitadas: primero notación decimal, luego científica
    printf("Resultado integral: %.12f\n", integral);
    printf("Resultado integral (científica): %.6e\n", integral);
}


