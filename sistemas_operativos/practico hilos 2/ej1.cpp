#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100

int array[SIZE]; // arreglo global con numeros del 1 al 100
int suma1 = 0, suma2 = 0; // variables globales para que los hilos sumen

// estructura para pasarle lso indices a los que pueden acceder los hilos
typedef struct Rango
{
    int inicio;
    int fin;
    int id_hilo;
};

void llenar_vector();

// funcion a la que acceden los hilos
void *sumar_segmento(void *param){
    Rango *rango = (Rango *)param;

    int sum_local = 0;

    for (int i = rango->inicio; i < rango->fin; i++)
    {
        sum_local += array[i];
    }

    if (rango->id_hilo == 1)
    {
        suma1 = sum_local;
    }else{
        suma2 = sum_local;
    }
    
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    llenar_vector();

    pthread_t hilos[2];
    int total;
    // defino los 2 rangos
    Rango rangos[2] = {
        {0 , SIZE / 2 , 1}, // 0, 49
        {SIZE /2 , SIZE, 2} // 50, 99
    };

    // creo los hilos
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&hilos[i],NULL,sumar_segmento,(void *)&rangos[i]);
    }

    //espero los hilos
    for (int i = 0; i < 2; i++)
    {
        pthread_join(hilos[i],NULL);
    }

    //hago la suma y la muestro
    total = suma1 + suma2;
    printf("la sumatoria desde uno hasta 100 es: %d\n",total);
    
    
    
    return 0;
}

void llenar_vector(){
    // cargo el arreglo
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = i + 1;
    }
    
    //leo el arreglo
    for (int i = 0; i < 100; i++)
    {
        printf("%d\n",array[i]);
    }
}


