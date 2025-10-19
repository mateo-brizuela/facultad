// este programa hace el metodo de biseccion teniendo en cuenta una toleracia relativa

#include <stdio.h>
#include <iostream>
#include <math.h>

double calcularFuncion(double x); // declaracion de la funcion

int main(int argc, char const *argv[])
{
    // declaracion de variables
    double a = 0.0; // a y b es el intervalo inicial para buscar la raiz [a,b]
    double b = 0.0;
    double c = 0.0;  // c es el valor intermedio en el intervalo [a,b]
    double cViejo = 0.0; 
    double fa = 0.0; // son los intervalos valuados en la funcion 
    double fb = 0.0;
    double fc = 0.0;

    double eAbsoluto = 0.0; // error absoluto
    int cifrasPrecision = 0; // para preguntar al usuario que nivel de precision desea con el metodo
    double toleracia = 0.0;
    int i = 0; //iteraciones

    bool manual = false; // un booleano que da la opcion de cargar los valores de manera manual en la terminal o tomar lo ingresado
    int opcion = 0;

    printf("Bienvenido al programa de calculo por biseccion!\n"
        "seleccione una opcion: \n"
        "1) ingresar los valores por terminal\n"
        "2) tomar los valores ingresados en el codigo\n");
    scanf("%d",&opcion);

    if (opcion == 1)
    {
        manual = true;
    }else{
        manual = false;
    }

    if (manual)
    {
        printf("ingrese el valor de a: ");
        scanf("%lf",&a);
        printf("ingrese el valor de b: ");
        scanf("%lf",&b);
        printf("ingrese la cantidad de cifras de precision: ");
        scanf("%d",&cifrasPrecision);
    }

    // calculamos por primera vez los valores en a y b para comprobar si el intervalo encierra a una raiz
    toleracia = pow(10,-cifrasPrecision); // asigno la toleracia basada en la cantidad de cifras de precision exigidas
    fa = calcularFuncion(a);
    fb = calcularFuncion(b);
    if ((fa * fb) > 0)
    {
        printf("error: no se encuentra una raiz en el intervalo especificado\n");
        return 1;
    }else{
        do
        {
            i++;
            c = (a+b)/2;
            fa = calcularFuncion(a);
            fb = calcularFuncion(b);
            fc = calcularFuncion(c);

            if ((fa * fc) > 0)
            {
                a = c;
            }else if ((fa * fc) < 0)
            {
                b = c;
            }else{
                printf("encontraste el valor exacto de la raiz!\n"
                    "la raiz es %.4f\n",c);
                return 0;
            }
            eAbsoluto = abs(c-cViejo);
            cViejo = c;
        } while (eAbsoluto > toleracia);

        printf("la raiz es %.9f\n",c);
        printf("con un error de: %.10f\n",eAbsoluto);
        printf("cantidad de iteraciones: %d\n",i);

    }
    return 0;
}


double calcularFuncion(double x){
    double fx = pow(x,3) -x -2; 
    return fx;
}