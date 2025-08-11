#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

// PID del hijo
pid_t child_pid;

// Manejador de señales en el padre
void signal_handler(int sig) {
    if (child_pid > 0) {
        printf("\nPadre recibió señal %d, reenviándola al hijo (PID: %d)...\n", sig, child_pid);
        kill(child_pid, sig);  // Reenviar la señal al hijo
    }
}

// Manejador de señales en el hijo
void child_signal_handler(int sig) {
    if (sig == SIGINT) {  // Ctrl+C
        printf("\nHijo (PID: %d) recibió SIGINT (Ctrl+C), pero sigo ejecutando.\n", getpid());
    } else if (sig == SIGTSTP) {  // Ctrl+Z
        printf("\nHijo (PID: %d) recibió SIGTSTP (Ctrl+Z), terminando...\n", getpid());
        exit(0);  // Hijo termina
    }
}

int main() {
    child_pid = fork();  // Crear proceso hijo

    if (child_pid < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    if (child_pid == 0) {
        // Código del hijo
        signal(SIGINT, child_signal_handler);   // Captura Ctrl+C
        signal(SIGTSTP, child_signal_handler);  // Captura Ctrl+Z

        while (1) {
            printf("Hijo ejecutándose... (PID: %d)\n", getpid());
            sleep(2);
        }
    } else {
        // Código del padre
        signal(SIGINT, signal_handler);   // Captura Ctrl+C y lo reenvía
        signal(SIGTSTP, signal_handler);  // Captura Ctrl+Z y lo reenvía

        // Esperar a que el hijo termine
        int status;
        wait(&status);
        printf("Hijo terminó, el padre también finaliza.\n");
    }

    return 0;
}
