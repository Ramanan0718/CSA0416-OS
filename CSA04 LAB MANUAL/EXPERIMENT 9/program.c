#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

/* Parent writes into a shared memory segment; child reads it. */
int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); exit(EXIT_FAILURE); }

    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) { perror("shmat"); exit(EXIT_FAILURE); }

    pid_t pid = fork();
    if (pid == 0) {                              /* child: reader */
        sleep(1);                                /* let parent write first */
        printf("Child  : read from shared memory -> \"%s\"\n", shm_ptr);
        shmdt(shm_ptr);
        exit(0);
    }

    strcpy(shm_ptr, "Hello, shared memory!");    /* parent: writer */
    printf("Parent : wrote to shared memory  -> \"%s\"\n", shm_ptr);

    wait(NULL);
    shmdt(shm_ptr);
    if (shmctl(shmid, IPC_RMID, NULL) == -1) { perror("shmctl"); exit(EXIT_FAILURE); }
    return 0;
}
