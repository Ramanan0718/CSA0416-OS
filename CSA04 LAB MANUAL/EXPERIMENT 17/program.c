#include <stdio.h>

/* Banker's algorithm: check safety and grant resource requests safely. */
#define P 5   /* processes */
#define R 3   /* resource types */

int available[R];
int max[P][R], alloc[P][R], need[P][R];

/* returns 1 if state is safe, fills seq[] with a safe sequence */
int is_safe(int seq[]) {
    int work[R], finish[P] = {0}, count = 0;
    for (int r = 0; r < R; r++) work[r] = available[r];
    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (finish[i]) continue;
            int ok = 1;
            for (int r = 0; r < R; r++) if (need[i][r] > work[r]) { ok = 0; break; }
            if (ok) {
                for (int r = 0; r < R; r++) work[r] += alloc[i][r];
                finish[i] = 1;
                seq[count++] = i;
                found = 1;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main() {
    printf("Enter available instances of each resource (%d values): ", R);
    for (int r = 0; r < R; r++) scanf("%d", &available[r]);

    printf("Enter MAX matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++) for (int r = 0; r < R; r++) scanf("%d", &max[i][r]);

    printf("Enter ALLOCATION matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++) for (int r = 0; r < R; r++) scanf("%d", &alloc[i][r]);

    for (int i = 0; i < P; i++)
        for (int r = 0; r < R; r++) need[i][r] = max[i][r] - alloc[i][r];

    int seq[P];
    printf("\nNeed matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("P%d: ", i);
        for (int r = 0; r < R; r++) printf("%d ", need[i][r]);
        printf("\n");
    }
    if (is_safe(seq)) {
        printf("\nSystem is in a SAFE state. Safe sequence: ");
        for (int i = 0; i < P; i++) printf("P%d ", seq[i]);
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state.\n");
    }

    int pid, req[R];
    printf("\nEnter process number and its request (%d values): ", R + 1);
    scanf("%d", &pid);
    for (int r = 0; r < R; r++) scanf("%d", &req[r]);

    /* step 1: request must not exceed need; step 2: must not exceed available */
    for (int r = 0; r < R; r++) {
        if (req[r] > need[pid][r]) { printf("Error: request exceeds declared maximum need.\n"); return 0; }
        if (req[r] > available[r]) { printf("Request must wait: resources not available.\n"); return 0; }
    }

    /* step 3: tentatively allocate, test safety, roll back if unsafe */
    for (int r = 0; r < R; r++) {
        available[r] -= req[r]; alloc[pid][r] += req[r]; need[pid][r] -= req[r];
    }
    if (is_safe(seq)) {
        printf("Request GRANTED. New safe sequence: ");
        for (int i = 0; i < P; i++) printf("P%d ", seq[i]);
        printf("\n");
    } else {
        for (int r = 0; r < R; r++) {
            available[r] += req[r]; alloc[pid][r] -= req[r]; need[pid][r] += req[r];
        }
        printf("Request DENIED: granting it would lead to an unsafe state.\n");
    }
    return 0;
}
