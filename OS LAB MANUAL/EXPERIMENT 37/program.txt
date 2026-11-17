#include <stdio.h>
#include <stdlib.h>

/* FCFS disk scheduling: serve requests in arrival order. */
int main() {
    int n, head, i, total = 0, q[50], cur;
    printf("Number of requests: "); scanf("%d", &n);
    printf("Request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &q[i]);
    printf("Initial head position: "); scanf("%d", &head);

    cur = head;
    printf("\nHead movement: %d", cur);
    for (i = 0; i < n; i++) {
        total += abs(q[i] - cur);
        cur = q[i];
        printf(" -> %d", cur);
    }
    printf("\nTotal head movement = %d\n", total);
    printf("Average seek = %.2f\n", (float)total / n);
    return 0;
}
