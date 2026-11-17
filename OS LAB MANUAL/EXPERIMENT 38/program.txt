#include <stdio.h>
#include <stdlib.h>

/* SCAN (elevator) disk scheduling on tracks 0..199: head moves toward
   the higher tracks, serves requests, reverses at the end, serves the rest. */
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main() {
    int n, head, i, total = 0, q[50], sorted[50], cur, maxtrack = 199;
    printf("Number of requests: "); scanf("%d", &n);
    printf("Request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &q[i]);
    printf("Initial head position: "); scanf("%d", &head);

    for (i = 0; i < n; i++) sorted[i] = q[i];
    qsort(sorted, n, sizeof(int), cmp);

    /* split into requests below and above the head */
    int lo[50], nlo = 0, hi[50], nhi = 0;
    for (i = 0; i < n; i++) {
        if (sorted[i] < head) lo[nlo++] = sorted[i];
        else hi[nhi++] = sorted[i];
    }

    cur = head;
    printf("\nHead movement (moving toward higher tracks first): %d", cur);
    for (i = 0; i < nhi; i++) {                        /* up to highest request */
        total += abs(hi[i] - cur); cur = hi[i];
        printf(" -> %d", cur);
    }
    /* reverse: go to the end of the disk, then serve lower requests downward */
    total += abs(maxtrack - cur); cur = maxtrack;
    printf(" -> %d (end of disk)", cur);
    for (i = nlo - 1; i >= 0; i--) {
        total += abs(lo[i] - cur); cur = lo[i];
        printf(" -> %d", cur);
    }
    printf("\nTotal head movement = %d\n", total);
    printf("Average seek = %.2f\n", (float)total / n);
    return 0;
}
