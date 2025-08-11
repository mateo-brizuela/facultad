#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// manejador de señales
void manejador_señales(int numero_señal){
    if (numero_señal == SIGINT) // pregunta si recibio Ctrl+C
    {
        printf("recibi Ctrl+c, pero no voy a cerrar el programa\n");
    }else if (numero_señal == SIGTSTP) // pregunta si recibio Ctrl+Z
    {
        printf("recibi Ctrl + Z, terminando el programa");
        exit(0);
    }
    
    
}


int main(int argc, char const *argv[])
{
    // creo que las señales se declaran una unica vez, para que una vez el programa las reciba las pueda tratar
    // se capturan las señales con signal()
    signal(SIGINT,manejador_señales);
    signal(SIGTSTP,manejador_señales);

    //genero un bucle infinito
    while (true)
    {
        printf("soy el proceso %d, estoy esperando a que me cierren\n", getpid());
        sleep(2); // hago que el proceso repose para no sobrecargar CPU
    }
    
    
    return 0;
}
