#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int pid = fork();

    if (pid < 0)
    {
        perror("hubo un error para crear el proceso");
        return 1;
    }else if (pid == 0)
    {
        // proceso hijo
        printf("soy el proceso hijo, el PID de mi padre es %d, y mi PID es %d\n", getppid(),getpid());
    }else{
        //proceso padre
        printf("soy el proceso padre, el PID del abuelo es %d, y mi PID es %d", getppid(), getpid());
    }
    
    
    return 0;
}
