#include <stdio.h>
#include <pthread.h>

/* Thread concepts: (i) create (ii) join (iii) equal (iv) exit. */
void *worker(void *arg) {
    printf("(i) Thread created and running (arg = %d)\n", *(int *)arg);
    pthread_exit((void *)42);                   /* (iv) exit with a value */
}

int main() {
    pthread_t tid;
    int value = 7;
    void *ret;

    if (pthread_create(&tid, NULL, worker, &value) != 0) {   /* (i) create */
        printf("create failed\n");
        return 1;
    }

    /* (iii) equal: compare thread IDs */
    printf("(iii) pthread_equal(tid, pthread_self()) = %d (0 means not equal)\n",
           pthread_equal(tid, pthread_self()));

    pthread_join(tid, &ret);                    /* (ii) join: wait for thread */
    printf("(ii) Joined thread; its exit value = %ld\n", (long)ret);   /* (iv) */
    return 0;
}
