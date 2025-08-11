#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

long arreglo[] = {1,1,1}; // arreglo donde los hilos hacen los productos parciales

void calcular_parte_factorial(int min, int max, int id_hilo);

void *factorial_hilo(void *param){
    int id_hilo = *(int *) param; // casteo y extraigo el valor del hilo
    int min;
    int max;

    switch (id_hilo)
    {
    case 0:
        calcular_parte_factorial(1,4,id_hilo);
        break;
    case 1:
        calcular_parte_factorial(5,8,id_hilo);
        break;
    case 2:
        calcular_parte_factorial(9,12,id_hilo);
        break;
    
    default:
        break;
    }

    pthread_exit(NULL);
}

void calcular_parte_factorial(int min, int max, int id_hilo){
    for (int i = min; i <= max; i++)
    {
        arreglo[id_hilo] *= i; // se hace el calculo de factorial
        printf("hilo: %d| arreglo[%d]=%ld\n",id_hilo,id_hilo,arreglo[id_hilo]);
    }
    
}

int main(int argc, char const *argv[])
{
    //defino las variables d elos hilos
    pthread_t hilos[3];
    int id_hilos[] = {0,1,2};
    
    // otras variables
    long total = 1;

    // inicio los hilos
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&hilos[i],NULL,factorial_hilo,(void *)&id_hilos[i]);
    }

    //espero los hilos
    for (int i = 0; i < 3; i++)
    {
        pthread_join(hilos[i],NULL);
    }

    // sumo el resultado final
    for (int i = 0; i < 3; i++)
    {
        total *= arreglo[i];
    }

    printf("el factorial de 12 es : %ld\n",total);
    
    return 0;
}



