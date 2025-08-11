#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int contador = 0;
pthread_mutex_t mutex1;

void *funcion_hilo(void *arg){
    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&mutex1); // bloqueo mutex
        contador++; //seccion critica
        pthread_mutex_unlock(&mutex1); // desbloqueo mutex
    }

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t hilos[2];

    // inicio el mutex
    pthread_mutex_init(&mutex1,NULL);
    
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&hilos[i],NULL,funcion_hilo,NULL);
    }

    //espero a los hilos
    for (int i = 0; i < 2; i++)
    {
        pthread_join(hilos[i],NULL);
    }

    //muestro el resultado

    printf("el contador es: %d\n",contador);

    //cierro el mutex
    pthread_mutex_destroy(&mutex1);
    
    
    return 0;
}
