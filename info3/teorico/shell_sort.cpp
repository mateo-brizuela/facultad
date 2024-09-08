#include <stdio.h>

void leer_vector(int vector[], int n);

int main(int argc, char const *argv[])
{
    // declaracion de variables
    int izq;
    int der;
    int izq2;
    int der2;
    int gap; // variables para recorrer el arreglo
    int aux;
    
    int v[] = {19,13,5,27,1,26,31,16,2,9,11,21}; // vector a ordenar
    int n = 12;

    gap = n;

    leer_vector(v,n);
    // inicio el bucle para ordenar el vector
    while (gap != 0)
    {
        // valuo las varibles 
        gap /= 2;
        izq = 0;
        der = izq + gap;

        // inicio otro bucle del vector que recorre el mismo en intervalos de magnitud gap
        while (der < n)
        {
            // si encuentra que el valor a la izquierda del intervalo es mayor que
            // el valor a la derecha del intervalo entonces inicia un tercer bucle
            if (v[izq] > v[der])
            {
                izq2 = izq;
                der2 = der;
                // el objetivo de este bucle es ir comparando en intervalos gap
                // el valor de la derecha con los anteriores hasta que encuentre un numero menor
                while (v[der2] < v[izq2] && izq2 >= 0)
                {
                    aux = v[izq2];
                    v[izq2] = v[der2];
                    v[der2] = aux;
                    izq2 -= gap;
                    der2 -= gap;
                    //printf("se intercambiaron los elementos\n");
                }

            }
            izq++;
            der++;
        }
        
        
    }
    leer_vector(v,n);
    



    return 0;
}

 // una funcion que lee el vector
 // recibe el vector y la cantidad de elementos
void leer_vector(int vector[], int n){
    int i = 0;
    for ( i = 0; i < n; i++)
    {
        printf("%d\t",vector[i]);
    }
    printf("\n\n");
    
}