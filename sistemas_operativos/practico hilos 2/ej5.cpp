#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1;
pthread_cond_t escribio_hilo1;
pthread_cond_t escribio_hilo2;
int turno = 1;  // variable para sincronizar los hilos 1 le toca al hilo de impares, 2 al hilo de pares

void *imprimir_impares(void *arg){
    int num = -1;

    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex1); //bloqueo el mutex
        num += 2;

        // verifica que sea su turno antesde escribir
        while (turno != 1)
        {
            pthread_cond_wait(&escribio_hilo2,&mutex1); // espero a que escriba el hilo 2
        }   
        printf("%d\t",num); // escribe el numero
        turno = 2; // cede el turno
        pthread_cond_signal(&escribio_hilo1); // envia la señal
        pthread_mutex_unlock(&mutex1); // libera el mutex
    }
    pthread_exit(NULL);
    
}

void *imprimir_pares(void *arg){
    int num = 0;

    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutex1);
        num += 2;
        while (turno != 2)
        {
            pthread_cond_wait(&escribio_hilo1,&mutex1);
        }
        
        printf("%d\t",num);
        turno = 1;
        pthread_cond_signal(&escribio_hilo2);
        pthread_mutex_unlock(&mutex1);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t hilo_pares, hilo_impares; //declaro las variables que guarda los hilos

    //mutex y conds
    pthread_mutex_init(&mutex1,NULL);
    pthread_cond_init(&escribio_hilo1,NULL);
    pthread_cond_init(&escribio_hilo2,NULL);

    //declaro los hilos
    pthread_create(&hilo_impares,NULL,imprimir_impares,NULL);
    pthread_create(&hilo_pares,NULL,imprimir_pares,NULL);

    //espero los hilos
    pthread_join(hilo_pares,NULL);
    pthread_join(hilo_impares,NULL);

    //cierro las cosas
    pthread_mutex_destroy(&mutex1);
    pthread_cond_destroy(&escribio_hilo1);
    pthread_cond_destroy(&escribio_hilo2);

    printf("\nfinalizo el programa\n");

    return 0;
}



