#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/* Readers-writers (readers' preference) using semaphores. */
sem_t mutex, writeBlock;
int data = 0, readersCount = 0;

void *reader(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 3; i++) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) sem_wait(&writeBlock);   /* first reader locks writers out */
        sem_post(&mutex);

        printf("Reader %d reads data: %d\n", id, data);  /* reading */

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) sem_post(&writeBlock);    /* last reader lets writers in */
        sem_post(&mutex);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 3; i++) {
        sem_wait(&writeBlock);                            /* exclusive access */
        data++;
        printf("Writer %d writes data: %d\n", id, data);
        sem_post(&writeBlock);
    }
    return NULL;
}

int main() {
    pthread_t r[2], w[2];
    int rid[2] = {1, 2}, wid[2] = {1, 2};
    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);
    for (int i = 0; i < 2; i++) pthread_create(&r[i], NULL, reader, &rid[i]);
    for (int i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, &wid[i]);
    for (int i = 0; i < 2; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);
    sem_destroy(&mutex);
    sem_destroy(&writeBlock);
    return 0;
}
