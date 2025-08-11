#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int buffer;
int estado = 0; // indica el estado del buffer (1->lleno  0->vacio)

//mutex
pthread_mutex_t mutex_p_c; // mutex para el productor y el consumidor
pthread_cond_t full; // condicion para el consumidor, indicando que el buffer esta lleno
pthread_cond_t empty; // condicion para el productor, indicando que el buffer esta vacio

// hilo productor
void *productor(void *arg){
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex_p_c);

        // si el buffer esta lleno se espera a que se vacie
        while (estado == 1)
        {
            pthread_cond_wait(&empty,&mutex_p_c); //se libera el mutex esperando una señal de que el buffer esta vacio
        }

        buffer = i; // se carga el buffer
        estado = 1; // se dice que el buffer esta cargado
        pthread_cond_signal(&full);
        
        pthread_mutex_unlock(&mutex_p_c); // se libera el mutex
    }
    pthread_exit(NULL);
}


// hilo consumidor
void *consumidor(void *arg){
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex_p_c);

        // si el buffer esta vacio esperamos a que se llene
        while (estado == 0)
        {
            pthread_cond_wait(&full,&mutex_p_c);
        }

        int valor = buffer;
        printf("soy el hilo consumidor, el valor del buffer es: %d\n",valor);

        estado = 0; // pongo el estado del buffer en vacio
        pthread_cond_signal(&empty); // envio la señal de buffer vacio

        pthread_mutex_unlock(&mutex_p_c);

        sleep(1); // simula tiempo de consumo
    }

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    // declaro variables para los hilos
    pthread_t hilo_prod, hilo_cons; // el hilo productor y consumidor

    // inicializo mutex y condiciones
    pthread_mutex_init(&mutex_p_c,NULL);
    pthread_cond_init(&full,NULL);
    pthread_cond_init(&empty,NULL);

    // inicio los hilos
    pthread_create(&hilo_prod,NULL,productor,NULL);
    pthread_create(&hilo_cons,NULL,consumidor,NULL);

    // espero a que terminen los hilos
    pthread_join(hilo_prod,NULL);
    pthread_join(hilo_cons,NULL);

    //cierro las cosas
    pthread_mutex_destroy(&mutex_p_c);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    printf("programa finalizado\n");

    return 0;
}


