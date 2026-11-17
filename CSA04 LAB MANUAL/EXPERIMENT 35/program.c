#include <stdio.h>
#include <string.h>

/* Indexed allocation: the index block holds one pointer (here: a block
   number) for each data block; entry i points to the i-th block of the file. */
#define MAX_BLOCKS 16

int index_block[MAX_BLOCKS];       /* index_block[i] = disk block holding file block i */
char disk[64][64];                 /* simulated disk */
int nblocks = 0;

int main() {
    int n, i, k;
    for (i = 0; i < MAX_BLOCKS; i++) index_block[i] = -1;

    printf("Enter number of file blocks: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        char data[64];
        int disk_no = 10 + i * 3;         /* scattered disk blocks */
        printf("Data for file block %d: ", i);
        scanf("%63s", data);
        strcpy(disk[disk_no], data);
        index_block[i] = disk_no;          /* index entry i -> block */
        nblocks++;
    }

    printf("\nIndex block:\n");
    for (i = 0; i < nblocks; i++)
        printf("  entry %d -> disk block %d\n", i, index_block[i]);

    printf("\nFile block to read: ");
    scanf("%d", &k);
    if (k < 0 || k >= nblocks) { printf("Invalid block.\n"); return 0; }
    printf("Index entry %d -> disk block %d -> data = %s\n",
           k, index_block[k], disk[index_block[k]]);
    return 0;
}
