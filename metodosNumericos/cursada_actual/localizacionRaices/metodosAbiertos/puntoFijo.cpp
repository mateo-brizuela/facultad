#include <stdio.h>
#include <math.h>

double calcularFuncion(double x);
double verificarDerivada(double x); // metodo parisi

int main(int argc, char const *argv[])
{
    double x0 = 0.0; // xi
    double x1 = 0.0; // x(i+1)
    double eAbsoluto = 0.0;

    int cifrasTolerancia = 0.0;
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
        printf("ingrese la cantidad de decimales de precision");
        scanf("%d",&cifrasTolerancia);
    }
    
    tolerancia = pow(10,-cifrasTolerancia);

    do
    {
        i++;
        if (abs(verificarDerivada(x0) >= 1))
        {
            printf("error: el metodo no converge\n");
            return 1;
        }

        x1 = calcularFuncion(x0);
        eAbsoluto = fabs(x1 - x0);
        x0 = x1;
    } while (eAbsoluto > tolerancia);
    
    printf("\nresultados:\n");
    printf("raiz: %.10f\nerror %.10f\niteraciones: %d\n",x1,eAbsoluto,i);

    return 0;
}

double calcularFuncion(double x){
    double e = std::exp(1.0);
    return 0.4*pow(e,pow(x,2));
}

double verificarDerivada(double x){
    return ((calcularFuncion(x + 0.001) -calcularFuncion(x))/0.001);
}