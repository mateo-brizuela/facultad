#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int resultado;

void *funcion_hilo(void *param){
    int n = *(int *) param; // casteo la variable y la desreferencio
    resultado = resultado + n;
    printf("soy el hilo %d y sume el numero\n");
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int arreglo[100];
    pthread_t hilos[100];
    int rc;
    int n;

    // escribo el arreglo
    for ( n = 0; n < 100; n++)
    {
        arreglo[n] = n+1; 
    }

    // leo el arreglo
    for (int i = 0; i < 100; i++)
    {
        printf("%d\n",arreglo[i]);
    }

    // genero los hilos
    for ( n = 0; n < 100; n++)
    {
        rc = pthread_create(&hilos[n],NULL,funcion_hilo,(void *)&arreglo[n]);

        if (rc != 0)
        {
            printf("no se pudo crear el hilo\n");
            exit(-1);
        }
    }

    
    

    
    


    return 0;
}
