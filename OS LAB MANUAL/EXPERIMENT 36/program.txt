#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Linked allocation: each block holds data and a pointer to the next block.
   The directory keeps the first and last block of the file. */
struct Block { char data[64]; struct Block *next; };

struct Directory { struct Block *first, *last; int count; } dir = {NULL, NULL, 0};

int main() {
    int n, k;
    printf("Enter number of blocks to write: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        struct Block *b = malloc(sizeof(struct Block));   /* blocks scattered in memory */
        printf("Data for block %d: ", i + 1);
        scanf("%63s", b->data);
        b->next = NULL;
        if (dir.first == NULL) dir.first = dir.last = b;   /* first block */
        else { dir.last->next = b; dir.last = b; }         /* link to previous last */
        dir.count++;
    }
    printf("\nDirectory: first block = %s, last block = %s\n",
           dir.first->data, dir.last->data);

    printf("Block number to read: ");
    scanf("%d", &k);
    if (k < 1 || k > dir.count) { printf("Invalid block.\n"); return 0; }
    printf("Following pointers from the first block:\n");
    struct Block *cur = dir.first;
    for (int i = 1; i < k; i++) {
        printf("  block %d -> next\n", i);
        cur = cur->next;
    }
    printf("Block %d data = %s\n", k, cur->data);

    /* free all blocks */
    while (dir.first) { struct Block *t = dir.first->next; free(dir.first); dir.first = t; }
    return 0;
}
