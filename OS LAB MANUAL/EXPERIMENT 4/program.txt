#include <stdio.h>

/* Select the waiting process with the SMALLEST burst (execution) time next.
   All processes arrive at time 0. */
int main() {
    int n, i, j, pos, temp;
    int bt[20], p[20], wt[20], tat[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter burst time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;
    }

    /* selection: at each step pick the smallest remaining burst time */
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++)
            if (bt[j] < bt[pos]) pos = j;
        temp = bt[i];  bt[i] = bt[pos];  bt[pos] = temp;
        temp = p[i];   p[i] = p[pos];    p[pos] = temp;
    }

    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    printf("\nExecution order: ");
    for (i = 0; i < n; i++) printf("P%d ", p[i]);
    printf("\n\nProcess\tBurst\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time    = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);
    return 0;
}
