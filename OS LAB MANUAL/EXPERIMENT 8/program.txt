#include <stdio.h>

/* Round Robin scheduling with a fixed time quantum. */
int main() {
    int n, i, quantum, time = 0, remaining;
    int at[20], bt[20], rem[20], ct[20], wt[20], tat[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("P%d arrival time and burst time: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rem[i] = bt[i];
    }
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    remaining = n;
    printf("\nGantt chart: ");
    while (remaining > 0) {
        int ran = 0;
        for (i = 0; i < n; i++) {
            if (rem[i] > 0 && at[i] <= time) {
                ran = 1;
                int slice = rem[i] < quantum ? rem[i] : quantum;
                printf("[P%d %d-%d] ", i + 1, time, time + slice);
                time += slice;
                rem[i] -= slice;
                if (rem[i] == 0) {
                    ct[i] = time;
                    remaining--;
                }
            }
        }
        if (!ran) time++;                     /* CPU idle */
    }

    printf("\n\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time    = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);
    return 0;
}
