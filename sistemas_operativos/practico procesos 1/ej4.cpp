#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int pid, status;
    pid = fork();

    if (pid < 0)
    {
        perror("hubo un error al crear al proceso hijo\n");
        return 1;
    } else if (pid == 0)
    {
        printf("soy el hijo(mi PID es : %d), me quedare en espera indefinida, hasta que hagas kill en la terminal\n", getpid());
        while(1); //espera infinita
        
    }else{
        printf("soy el proceso padre, voy a esperar al proceso hijo\n");
        wait(&status);
        printf("espera finalizada\n");

        if (WIFEXITED(status))
        {
            printf("el hijo termino normalmente y retorno el codigo: %d\n", WEXITSTATUS(status));
        }else if (WIFSIGNALED(status))
        {
            printf("el hijo a sido eliminado o terminado por la señal %d\n",WTERMSIG(status));
        }else{
            printf("el hijo no termino correctamente\n");
        }

        // WIFEXITED(status) : devuelve true si el hijotermino de forma normal con exit(n)
        // WEXITSTATUS(status): si WIFEXITED es true, devuelve el codigo que el hjo paso atraves de exit(n)
        // WIFSIGNALED: devuelve true si el hijo fue terminado por una señal (ejemplo kill)
        // WTERMSIG: si WIFSIGNALED es true, retorna la señal que termino al proceso hijo
        
        
    }
    
    
    return 0;
}
