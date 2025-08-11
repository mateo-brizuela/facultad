#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Manejador de señales
void sigmanager(int sig_num) {
    if (sig_num == SIGINT) {  // Ctrl+C
        printf("\nRecibí SIGINT (Ctrl+C), pero no voy a cerrar.\n");
        fflush(stdout);
    } else if (sig_num == SIGTSTP) {  // Ctrl+Z
        printf("\nRecibí SIGTSTP (Ctrl+Z), terminando el programa.\n");
        exit(0);
    }
}

int main() {
    // Captura señales con signal()
    signal(SIGINT, sigmanager);   // Ctrl+C (SIGINT)
    signal(SIGTSTP, sigmanager);  // Ctrl+Z (SIGTSTP)

    // Bucle infinito
    while (1) {
        printf("Ejecutando... (PID: %d)\n", getpid());
        sleep(2);  // Espera para evitar saturar la CPU
    }

    return 0;
}
