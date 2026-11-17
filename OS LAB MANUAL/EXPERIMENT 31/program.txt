#include <stdio.h>

/* FIFO page replacement with 3 frames. */
#define FRAMES 3

void show(int f[]) {
    for (int i = 0; i < FRAMES; i++)
        if (f[i] == -1) printf(" -"); else printf(" %d", f[i]);
    printf("\n");
}

int main() {
    int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(ref) / sizeof(ref[0]);
    int frames[FRAMES], next = 0, faults = 0;
    for (int i = 0; i < FRAMES; i++) frames[i] = -1;

    printf("Reference string:");
    for (int i = 0; i < n; i++) printf(" %d", ref[i]);
    printf("\n\n");

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < FRAMES; j++) if (frames[j] == ref[i]) hit = 1;
        printf("Ref %d: ", ref[i]);
        if (!hit) {
            frames[next] = ref[i];               /* replace the oldest page */
            next = (next + 1) % FRAMES;
            faults++;
            printf("FAULT ->");
        } else printf("hit   ->");
        show(frames);
    }
    printf("\nTotal page faults (FIFO) = %d\n", faults);
    return 0;
}
