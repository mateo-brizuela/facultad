#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TRHEADS 5

// arreglo global donde se almacena el resultado
int resultados[NUM_TRHEADS];

//funcion no recursiva para calcular fibonacci
int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// funcion que ejecuta cada hilo
void *calcular_fibonacci(void *param){
    int indice = *(int *) param;
    resultados[indice] = fibonacci(indice);
    pthread_exit(NULL);
}

//MAIN
int main(int argc, char const *argv[])
{
    pthread_t hilos[NUM_TRHEADS];
    int n;
    int rc;

    for ( n = 0; n < NUM_TRHEADS; n++)
    {
        rc = pthread_create(&hilos[n],NULL,calcular_fibonacci,(void *) &n);

        if (rc != 0)
        {
            printf("hubo un error al crear el hilo\n");
            exit(-1);
        }
        
    }

    //esperar a que los hilos terminen
    for (int i = 0; i < NUM_TRHEADS; i++)
    {
        pthread_join(hilos[i],NULL);
    }

    //mostrar el resultado

    printf("serie fibonacci\n");
    for (int i = 0; i < NUM_TRHEADS; i++)
    {
        printf("%d\n",resultados[i]);
    }
    
    return 0;
}
