#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *funcion_hilo(void *numero){
    int *x = (int *) numero;
    printf("hola acabo de ser creado! soy el hilo: %d\n",*x);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    printf("hola, soy la funcion main y voy a crear mi primer hilo\n");
    pthread_t hilo; //variable para el hilo
    int valor = 1; // valor que se le pasa al hilo por parametro

    printf("direccion de memoria de la variable parametro: %d\n", &valor);
    printf("direccion de memoria del hilo(?): %d\n", hilo);

    pthread_create(
        &hilo,
        NULL, //no queremos atributos especiales
        funcion_hilo, // funcion donde se ejecuta el hilo
        (void *) &valor //pasamos un valor por direccion
    );

    pthread_join(hilo, NULL); // esperamos a que termine el hilo

    printf("direccion de memoria del hilo(asignado?): %d\n", hilo);
    return 0;
}
