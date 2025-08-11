#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

// PID del hijo
pid_t pid_hijo;

//manejador de señales del padre
void signal_hadler(int sig){
    if (pid_hijo > 0)
    {
        printf("soy el padre(PID: %d) y recibi la señal %d se la envio a mi hijo\n",getpid(),sig);
        kill(pid_hijo,sig);
    }
}

// manejadorde señales del hijo
void child_signal_hadler(int sig){
    if (sig == SIGINT) // pregunta si recibio Ctrl + c
    {
        printf("soy el hijo (PID: %d), recibi Ctrl + C per no voy a hacer nada\n",getpid());
    }else if (sig == SIGTSTP) // pregunta si recibio Ctrl + Z
    {
        printf("soy el hijo(PID: %d) y recibi Ctrl + Z, voy a finalizar el proceso\n",getpid());
        exit(0); // hijo termina
    }
}

int main(int argc, char const *argv[])
{
    // creo al proceso hijo
    pid_hijo = fork();

    if (pid_hijo < 0)
    {
        printf("hubo un error al crear al proceso hijo\n");
        return 1;
    }


    if (pid_hijo == 0)// lo que ejecuta el proceso hijo
    {
        signal(SIGINT,child_signal_hadler); // Ctrl + C
        signal(SIGTSTP,child_signal_hadler); // Ctrl + Z

        while (true)
        {
            printf("soy el proceso hijo (PID: %d) ejecutando...\n",getpid());
            sleep(2);
        }
    }else{ // lo que ejecuta el padre
        signal(SIGINT,signal_hadler); // Ctrl + C
        signal(SIGTSTP,signal_hadler); // Ctrl + Z

        // espero a que el hijo termine
        int status;
        wait(&status);
        printf("el hijo temrino, el padre finaliza\n");
        
    }
    
    
    return 0;
}
