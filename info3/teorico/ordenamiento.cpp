#include <stdio.h>

int main(int argc, char const *argv[])
{
    // declaracion de variables
    int i; //variables para recorrer el vector
    int j;
    int cop; // variable auxiliar para intercambiar de posicion elementos del vector
    int vector[] = {8, 5, 9, 2, 6, 3};

    // el bucle se ordena por el metodo de isercion
    for ( i = 1; i < 6; i++)
    {
        j = i;
        while (vector[j] < vector[j-1] && j!=0)
        {
            cop = vector[j-1];
            vector[j-1] = vector[j];
            vector[j] = cop;
            j--;    
        }
        
    }

    //imprimo el vector en pantalla
    for ( i = 0; i < 6; i++)
    {
        printf("%d",vector[i]);
    }

    return 0;
}
