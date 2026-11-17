#include <stdio.h>

/* Optimal page replacement with 3 frames: replace the page whose
   next use is farthest in the future (or never used again). */
#define FRAMES 3

void show(int f[]) {
    for (int i = 0; i < FRAMES; i++)
        if (f[i] == -1) printf(" -"); else printf(" %d", f[i]);
    printf("\n");
}

int main() {
    int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(ref) / sizeof(ref[0]);
    int frames[FRAMES], faults = 0;
    for (int i = 0; i < FRAMES; i++) frames[i] = -1;

    printf("Reference string:");
    for (int i = 0; i < n; i++) printf(" %d", ref[i]);
    printf("\n\n");

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < FRAMES; j++) if (frames[j] == ref[i]) hit = 1;
        printf("Ref %d: ", ref[i]);
        if (hit) {
            printf("hit   ->");
        } else {
            int victim = -1, farthest = -1;
            for (int j = 0; j < FRAMES; j++) {
                if (frames[j] == -1) { victim = j; break; }
                int dist = n;                    /* never used again = farthest */
                for (int k = i + 1; k < n; k++)
                    if (ref[k] == frames[j]) { dist = k; break; }
                if (dist > farthest) { farthest = dist; victim = j; }
            }
            frames[victim] = ref[i];
            faults++;
            printf("FAULT ->");
        }
        show(frames);
    }
    printf("\nTotal page faults (Optimal) = %d\n", faults);
    return 0;
}
