#include <stdio.h>
#include <stdlib.h>

/* C-SCAN (circular SCAN): head moves toward higher tracks serving requests;
   at the end it jumps back to the lowest track (jump not counted as a seek)
   and serves the remaining requests in the same direction. */
int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main() {
    int n, head, i, total = 0, q[50], sorted[50], cur, maxtrack = 199;
    printf("Number of requests: "); scanf("%d", &n);
    printf("Request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &q[i]);
    printf("Initial head position: "); scanf("%d", &head);

    for (i = 0; i < n; i++) sorted[i] = q[i];
    qsort(sorted, n, sizeof(int), cmp);

    int lo[50], nlo = 0, hi[50], nhi = 0;
    for (i = 0; i < n; i++) {
        if (sorted[i] < head) lo[nlo++] = sorted[i];
        else hi[nhi++] = sorted[i];
    }

    cur = head;
    printf("\nHead movement: %d", cur);
    for (i = 0; i < nhi; i++) { total += abs(hi[i] - cur); cur = hi[i]; printf(" -> %d", cur); }
    total += abs(maxtrack - cur); cur = maxtrack;
    printf(" -> %d (end)", cur);
    total += maxtrack;                               /* jump back to track 0 */
    cur = 0;
    printf(" => jump to 0 (+%d)", maxtrack);
    for (i = 0; i < nlo; i++) { total += abs(lo[i] - cur); cur = lo[i]; printf(" -> %d", cur); }
    printf("\nTotal head movement = %d\n", total);
    printf("Average seek = %.2f\n", (float)total / n);
    return 0;
}
