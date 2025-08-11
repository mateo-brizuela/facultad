#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int pid;

    pid = fork(); // creando el proceso
    // forkretorna 2 cosas, en el padre retorna el pid de su proceso hijo, y en el hijo retorna 0
    // si hubo un error se retorna -1 en el proceso padre
    // los dos procesos se ejecutan de manera concurrente, por eso da multiples mensajes, porque se esta ejecutando este proceso tanto en el padre como en el hijo
    

    if (pid < 0)
    {
        // error en fork()
        perror("error al crear el proceso");
        return 1;
    } else if (pid == 0)
    {
        // codigo del proceso hijo
        printf("Soy el hijo. Mi PID es %d y el pid de mi padre es %d.\n", getpid(), getppid());
        printf("El PID que me fue asignado es %d", pid);
    } else{
        // codigo del proceso padre
        printf("Soy el padre. Mi PID es %d, y el pid de mi hijo es %d\n",getpid(),pid);
    }
    
    return 0;
}

