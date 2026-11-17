#include <stdio.h>
#include <string.h>

/* Contiguous (sequential) allocation simulated: the records of the file are
   stored one after another. Reading record k means reading records 1..k first. */
#define MAX_RECORDS 50

struct Record { char data[64]; };
struct Record file[MAX_RECORDS];
int nrec = 0;

int main() {
    int n, k;
    printf("Enter number of records to write: ");
    scanf("%d", &n);
    for (int i = 0; i < n && i < MAX_RECORDS; i++) {
        printf("Record %d data: ", i + 1);
        scanf("%63s", file[i].data);
        nrec++;
    }
    printf("\nBlock layout (physically and logically sequential):\n");
    for (int i = 0; i < nrec; i++)
        printf("  position %d -> %s\n", i + 1, file[i].data);

    printf("\nRecord number to access: ");
    scanf("%d", &k);
    if (k < 1 || k > nrec) { printf("No such record.\n"); return 0; }

    printf("Reading records from the beginning to reach record %d:\n", k);
    for (int i = 0; i < k; i++)
        printf("  read record %d (%s)\n", i + 1, file[i].data);
    printf("Access cost = %d record reads. Target record = %s\n", k, file[k - 1].data);
    return 0;
}
