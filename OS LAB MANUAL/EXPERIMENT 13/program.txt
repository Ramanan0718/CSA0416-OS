#include <stdio.h>

/* Memory allocation strategies on a list of free holes.
   Choose: 1 = First fit, 2 = Best fit, 3 = Worst fit. */
#define MAX 20

int main() {
    int holes[MAX], hsz[MAX], nh, np, procs[MAX], choice, i, j, idx;
    int alloc[MAX];

    printf("Enter number of free memory holes: ");
    scanf("%d", &nh);
    printf("Enter size of each hole: ");
    for (i = 0; i < nh; i++) { scanf("%d", &hsz[i]); holes[i] = i; }

    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter size of each process: ");
    for (i = 0; i < np; i++) scanf("%d", &procs[i]);

    printf("Choose strategy (1 = First fit, 2 = Best fit, 3 = Worst fit): ");
    scanf("%d", &choice);

    printf("\nProcess\tSize\tHole allocated\n");
    for (i = 0; i < np; i++) {
        idx = -1;
        for (j = 0; j < nh; j++) {
            if (hsz[j] < procs[i]) continue;
            if (choice == 1) { idx = j; break; }                          /* first fit */
            if (idx == -1) idx = j;
            else if (choice == 2 && hsz[j] < hsz[idx]) idx = j;         /* best  */
            else if (choice == 3 && hsz[j] > hsz[idx]) idx = j;         /* worst */
        }
        if (idx == -1) {
            printf("P%d\t%d\tWAIT (no hole big enough)\n", i + 1, procs[i]);
        } else {
            printf("P%d\t%d\tHole %d (size %d) -> remaining %d\n",
                   i + 1, procs[i], idx + 1, hsz[idx], hsz[idx] - procs[i]);
            hsz[idx] -= procs[i];
        }
    }
    return 0;
}
