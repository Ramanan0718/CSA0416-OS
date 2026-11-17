#include <stdio.h>

/* LRU page replacement with 3 frames: replace the page unused for the longest time. */
#define FRAMES 3

void show(int f[]) {
    for (int i = 0; i < FRAMES; i++)
        if (f[i] == -1) printf(" -"); else printf(" %d", f[i]);
    printf("\n");
}

int main() {
    int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(ref) / sizeof(ref[0]);
    int frames[FRAMES], last[FRAMES], faults = 0;
    for (int i = 0; i < FRAMES; i++) { frames[i] = -1; last[i] = -1; }

    printf("Reference string:");
    for (int i = 0; i < n; i++) printf(" %d", ref[i]);
    printf("\n\n");

    for (int i = 0; i < n; i++) {
        int hit = -1;
        for (int j = 0; j < FRAMES; j++) if (frames[j] == ref[i]) hit = j;
        printf("Ref %d: ", ref[i]);
        if (hit != -1) {
            last[hit] = i;                       /* record recent use */
            printf("hit   ->");
        } else {
            int victim = 0;
            for (int j = 0; j < FRAMES; j++) {
                if (frames[j] == -1) { victim = j; break; }
                if (last[j] < last[victim]) victim = j;   /* least recently used */
            }
            frames[victim] = ref[i];
            last[victim] = i;
            faults++;
            printf("FAULT ->");
        }
        show(frames);
    }
    printf("\nTotal page faults (LRU) = %d\n", faults);
    return 0;
}
