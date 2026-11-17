#include <stdio.h>

/* Preemptive priority scheduling (higher number = higher priority).
   Simulated one time unit at a time. */
struct Proc { int pid, at, bt, rem, pr, ct, wt, tat; };

int main() {
    int n, i, time = 0, done = 0, best;
    struct Proc p[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time, burst time, priority for each process:\n");
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d (arrival burst priority): ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rem = p[i].bt;
    }

    printf("\nGantt chart (time unit : process):\n");
    while (done < n) {
        best = -1;
        for (i = 0; i < n; i++)               /* pick arrived, unfinished, highest priority */
            if (p[i].at <= time && p[i].rem > 0 &&
                (best == -1 || p[i].pr > p[best].pr))
                best = i;

        if (best == -1) { time++; continue; } /* CPU idle */

        printf("%d:P%d ", time, p[best].pid);
        p[best].rem--;
        time++;
        if (p[best].rem == 0) {
            p[best].ct = time;
            done++;
        }
    }
    printf("\n\nPID\tAT\tBT\tPR\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].pr, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time    = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);
    return 0;
}
