#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "common.h"

int main() {
    char *buff;

    // Crear memoria compartida
    int shm_id = shmget(SHM_KEY, MAX_LEN, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    buff = shmat(shm_id, NULL, 0);
    if (buff == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Crear semáforo
    int sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Inicializar semáforo en 0
    semctl(sem_id, 0, SETVAL, 0);

    printf("Escribe texto para enviar al lector (Ctrl+D para salir):\n");

    while (fgets(buff, MAX_LEN, stdin) != NULL) {
        // Notificar al lector que hay nuevo contenido
        struct sembuf signal = {0, 1, 0}; // incrementar semáforo
        semop(sem_id, &signal, 1);
    }

    shmdt(buff);
    printf("Memoria compartida liberada\n");

    return 0;
}

