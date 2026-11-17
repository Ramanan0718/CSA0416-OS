#include <stdio.h>

/* WORST FIT: give each process the LARGEST free hole that fits it. */
int main() {
    int nh, np, hole[20], proc[20], i, j, idx;
    printf("Number of memory holes: "); scanf("%d", &nh);
    printf("Hole sizes: ");
    for (i = 0; i < nh; i++) scanf("%d", &hole[i]);
    printf("Number of processes: "); scanf("%d", &np);
    printf("Process sizes: ");
    for (i = 0; i < np; i++) scanf("%d", &proc[i]);

    printf("\nWorst fit allocation:\n");
    for (i = 0; i < np; i++) {
        idx = -1;
        for (j = 0; j < nh; j++)
            if (hole[j] >= proc[i] && (idx == -1 || hole[j] > hole[idx])) idx = j;
        if (idx == -1) printf("P%d (%d) must wait\n", i + 1, proc[i]);
        else {
            printf("P%d (%d) -> hole %d (size %d)\n", i + 1, proc[i], idx + 1, hole[idx]);
            hole[idx] -= proc[i];
        }
    }
    return 0;
}
