#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "common.h"

int main() {
    char *buff;

    // Obtener memoria compartida
    int shm_id = shmget(SHM_KEY, MAX_LEN, 0);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    buff = shmat(shm_id, NULL, 0);
    if (buff == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Obtener semáforo
    int sem_id = semget(SEM_KEY, 1, 0);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    printf("Esperando datos del escritor...\n");

    while (1) {
        // Esperar señal del escritor
        struct sembuf wait = {0, -1, 0}; // decrementar semáforo
        semop(sem_id, &wait, 1);

        printf("Lector recibió: %s", buff);
    }

    shmdt(buff);
    return 0;
}

