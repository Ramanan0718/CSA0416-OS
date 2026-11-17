#include <stdio.h>

/* Non-preemptive priority scheduling.
   Here a HIGHER number means HIGHER priority (as in the manual's code).
   All processes arrive at time 0. */
struct Proc { int pid, bt, pr, wt, tat; };

int main() {
    int n, i, j;
    struct Proc p[20], tmp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter burst time and priority of each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d burst: ", i + 1);  scanf("%d", &p[i].bt);
        printf("P%d priority: ", i + 1); scanf("%d", &p[i].pr);
    }

    /* sort by priority, highest first */
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (p[j].pr > p[i].pr) { tmp = p[i]; p[i] = p[j]; p[j] = tmp; }

    p[0].wt = 0;
    for (i = 1; i < n; i++)
        p[i].wt = p[i - 1].wt + p[i - 1].bt;

    printf("\nPID\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        printf("P%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].bt, p[i].pr, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time    = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);
    return 0;
}
