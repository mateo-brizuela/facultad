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
        printf("soy el proceso hijo, ejecutando tarea...\n");
        sleep(2);
        printf("proceso terminado, volviendo a proceso padre\n");
        exit(45); // el parametro es arbitrario, solo es un parametro que puede recibir el padre atraves de wait o los macros
    }else{
        printf("soy el proceso padre, voy a esperar al proceso hijo\n");
        wait(&status);
        printf("espera finalizada\n");

        if (WIFEXITED(status))
        {
            printf("el hijo termino normalmente y retorno el codigo: %d\n", WEXITSTATUS(status));
        }else{
            printf("el hijo no termino correctamente\n");
        }
        
    }
    
    
    return 0;
}
