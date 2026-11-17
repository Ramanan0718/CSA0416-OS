#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
pthread_mutex_t chopstick[N];

/* Deadlock avoidance: at most N-1 philosophers may try to pick up
   chopsticks at once (a counting semaphore), so a circular wait cannot form. */
#include <semaphore.h>
sem_t room;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id, right = (id + 1) % N;
    for (int meal = 1; meal <= 2; meal++) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);
        sem_wait(&room);                          /* ask to enter the dining room */
        pthread_mutex_lock(&chopstick[left]);
        pthread_mutex_lock(&chopstick[right]);
        printf("Philosopher %d is eating (meal %d)\n", id, meal);
        sleep(1);
        pthread_mutex_unlock(&chopstick[right]);
        pthread_mutex_unlock(&chopstick[left]);
        sem_post(&room);
    }
    printf("Philosopher %d is done\n", id);
    return NULL;
}

int main() {
    pthread_t ph[N];
    int ids[N];
    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++) pthread_mutex_init(&chopstick[i], NULL);
    for (int i = 0; i < N; i++) { ids[i] = i; pthread_create(&ph[i], NULL, philosopher, &ids[i]); }
    for (int i = 0; i < N; i++) pthread_join(ph[i], NULL);
    for (int i = 0; i < N; i++) pthread_mutex_destroy(&chopstick[i]);
    sem_destroy(&room);
    return 0;
}
