#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS   10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty_slots, full_slots;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    for (int i = 1; i <= MAX_ITEMS; i++) {
        sem_wait(&empty_slots);                  /* wait for a free slot */
        pthread_mutex_lock(&lock);
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", i);
        pthread_mutex_unlock(&lock);
        sem_post(&full_slots);                   /* one more full slot */
        usleep(100000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= MAX_ITEMS; i++) {
        sem_wait(&full_slots);                   /* wait for an item */
        pthread_mutex_lock(&lock);
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);
        pthread_mutex_unlock(&lock);
        sem_post(&empty_slots);
        usleep(200000);
    }
    return NULL;
}

int main() {
    pthread_t p, c;
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    return 0;
}
