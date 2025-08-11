#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *funcion_hilo(void * numero){
    int *numero_hilo = (int *) numero;
    printf("hola soy el hilo: %d\n", *numero_hilo);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    printf("soy la funcion main y voy a crear 5 hilos\n");

    pthread_t hilos[5];
    int rc; //parametro que recibe lo que retorna pthread_create
    int t; //valor que le vamos a pasar a los hilos por parametros

    // se crean los hilos y se les asigna un numero
    for (t = 0; t < 5; t++)
    {
        printf("en el main: estoy creando el hilo %d\n", t);

        rc = pthread_create(&hilos[t],NULL,funcion_hilo,(void *) &t);

        sleep(1);

        if (rc != 0)
        {
            printf("hubo un error al crear el hilo %d\n",t);
            exit(-1);
        }

        if (rc == 0)
        {
            printf("el hilo se creo corretamente\n");
        }
        
        
    }

    // esperamos a que terminen todos los hilos
    for (int i = 0; i < 5; i++)
    {
        pthread_join(hilos[i],NULL);
    }


    
    
    // finaliza el programa
    return 0;
}
