#include <stdio.h>
#include <stdlib.h>

/* Classical producer-consumer with mutex, empty and full counters,
   driven by menu choices (1 = produce, 2 = consume, 3 = exit). */
int mutex = 1;
int full = 0;
int empty = 10;
int x = 0;            /* item counter */

void producer() {
    mutex--; full++; empty--; x++;
    printf("Producer produces item %d (full=%d, empty=%d)\n", x, full, empty);
    mutex++;
}

void consumer() {
    mutex--; full--; empty++;
    printf("Consumer consumes item %d (full=%d, empty=%d)\n", x, full, empty);
    x--;
    mutex++;
}

int main() {
    int n;
    printf("1. Producer   2. Consumer   3. Exit\n");
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &n) != 1) break;
        switch (n) {
            case 1:
                if (mutex == 1 && empty != 0) producer();
                else printf("Buffer is full!\n");
                break;
            case 2:
                if (mutex == 1 && full != 0) consumer();
                else printf("Buffer is empty!\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
