#include <stdio.h>
#include <math.h>

double f(double x){
    return (1/exp(x)) -x;
}

double fDeriv(double x){
    return (f(x + 0.001) - f(x))/0.001;
}


int main(int argc, char const *argv[])
{
    double x0 = 0.0; // valor inicial para empezar el metodo
    double x1 = 0.0;
    double error = 0.0;
    double tolerancia = 0.0;
    int i = 0; // numero de iteraciones
    int decimalesPrecision = 0;

    int opcion = 0;
    double aux = 0.0;

    printf("Bienvenido al programa de calculo por newton-raphson\n");
    printf("seleccione una opcion\n"
        "1) ingresar los valores por terminal\n"
        "2) usar valores por defecto\n");
    scanf("%d",&opcion);

    if (opcion == 1)
    {
        printf("ingrese el valor inicial x0: ");
        scanf("%lf",&x0);
        printf("ingrese la cantidad de decimales de precision: ");
        scanf("%d",&decimalesPrecision);
    }else{
        x0 = 0.0;
        decimalesPrecision = 6;
        printf("usando valores por defecto (x0 = %.4f)(decimales = %d)",x0,decimalesPrecision);
    }

    tolerancia = pow(10,-decimalesPrecision);

    do
    {
        i++;
        // verificacion de si la derivada es muy pequeña, si es muy pequeña el metodo tardaria mucho en converger
        if (fabs(fDeriv(x0)) < pow(10,-4))
        {
            printf("derivada muy pequeña\n");
            return 1;
        }

        x1 = x0 - (f(x0)/fDeriv(x0)); // se traza la recta tangente y se toma el punto en el eje x
        error = fabs(x1-x0); // se calcula el errorr
        x0 = x1; // proxima iteracion
        
    } while (error > tolerancia && i < 10000);
    
    // mostrar resultados
    aux = f(x1);
    printf("raiz: %.9f\n"
        "iteraciones: %d\n"
        "error absoluto: %.9f\n"
        "f(x1): %.9f\n",x1,i,error,aux);
    return 0;
}
