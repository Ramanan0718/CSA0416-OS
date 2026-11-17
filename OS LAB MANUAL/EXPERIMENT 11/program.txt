#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    char *msg = (char *)arg;
    printf("%s\n", msg);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    char *m1 = "Hello from Thread 1!";
    char *m2 = "Hello from Thread 2!";

    pthread_create(&t1, NULL, threadFunction, m1);
    pthread_create(&t2, NULL, threadFunction, m2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Main thread: both threads finished.\n");
    return 0;
}
