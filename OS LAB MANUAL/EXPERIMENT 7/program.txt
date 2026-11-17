#include <stdio.h>

/* Non-preemptive SJF: when the CPU is free, run the arrived process
   with the smallest burst time; runs to completion. */
struct Proc { int pid, at, bt, ct, wt, tat, done; };

int main() {
    int n, i, time = 0, completed = 0, best;
    struct Proc p[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d (arrival burst): ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = 0;
    }

    printf("\nExecution order: ");
    while (completed < n) {
        best = -1;
        for (i = 0; i < n; i++)
            if (!p[i].done && p[i].at <= time &&
                (best == -1 || p[i].bt < p[best].bt))
                best = i;
        if (best == -1) { time++; continue; }      /* CPU idle */

        time += p[best].bt;                        /* run to completion */
        p[best].ct = time;
        p[best].done = 1;
        completed++;
        printf("P%d ", p[best].pid);
    }
    printf("\n\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time    = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);
    return 0;
}
