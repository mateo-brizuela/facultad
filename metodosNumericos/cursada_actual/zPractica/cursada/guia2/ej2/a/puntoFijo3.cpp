#include <stdio.h>
#include <math.h>

#define MAX_ITER 10000  // Límite de iteraciones

double calcularFuncion(double x);
double calcularDerivada(double x);

int main(int argc, char const *argv[])
{
    double x0 = 0.0; // xi
    double x1 = 0.0; // x(i+1)
    double eAbsoluto = 0.0;

    int cifrasTolerancia = 0;
    double tolerancia = 0.0;
    int i = 0; // cuenta la cantidad de iteraciones 
    int opcion = 0;

    printf("Bienvenido al programa de calculo por punto fijo\n");
    printf("seleccione una opcion\n"
        "1) ingresar los valores por terminal\n"
        "2) tomar los valores por defecto en el codigo\n");
    scanf("%d",&opcion);

    if (opcion == 1)
    {
        printf("ingrese el punto x0: ");
        scanf("%lf",&x0);
        printf("ingrese la cantidad de decimales de precision: ");
        scanf("%d",&cifrasTolerancia);
    }
    else
    {
        // Valores por defecto (debes definir estos según tu problema)
        x0 = 0.5;
        cifrasTolerancia = 6;
    }
    
    tolerancia = pow(10,-cifrasTolerancia);

    do
    {
        i++;
        if (fabs(calcularDerivada(x0)) >= 1)
        {
            printf("error: el metodo no converge\n");
            return 1;
        }

        x1 = calcularFuncion(x0);
        eAbsoluto = fabs(x1 - x0);
        x0 = x1;
    } while (eAbsoluto > tolerancia && i < MAX_ITER);
    
    if (i >= MAX_ITER) {
        printf("Advertencia: se alcanzo el maximo de iteraciones (%d)\n", MAX_ITER);
    }
    
    printf("\nresultados:\n");
    printf("raiz: %.10f\nerror: %.10f\niteraciones: %d\n",x1,eAbsoluto,i);

    return 0;
}

double calcularFuncion(double x){
    return cos(sin(x));  // Punto fijo: x = cos(x)
}
double calcularDerivada(double x){
    double h = 1e-5;
    return (calcularFuncion(x + h) - calcularFuncion(x - h)) / (2 * h);
}