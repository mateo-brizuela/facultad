#include <stdio.h>

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

    // inicio el bucle paraordenar el vector
    while (gap != 0)
    {
        // valuo las varibles 
        gap /= 2;
        izq = 0;
        der = izq + gap;

        // inicio otro bucle del vector que recorre el mismo en intervalos de magnitud gap
        while (der < n-1)
        {
            // si encuentra que el valor a la izquierda del intervalo es mayor que
            // el valor a la derecha del intervalo entonces inicia un tercer bucle
            if (v[izq] > v[der])
            {
                izq2 = izq;
                der2 = der;
                // el objetivo de este bucle es ir comparando en intervalos gap
                // el valor de la derecha con los anteriores hasta que encuentre un numero menor
                while (v[der2] < v[izq2] && izq2 > 0)
                {
                    
                }
                
            }
            
        }
        
        
    }
    

    return 0;
}
