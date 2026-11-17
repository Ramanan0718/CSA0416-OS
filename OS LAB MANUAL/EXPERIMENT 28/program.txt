#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

/* Simulates the UNIX 'grep' command: print every line containing the pattern. */
int main() {
    char pattern[100], filename[100], line[MAX_LINE];
    int lineno = 0;

    printf("Enter pattern to search: "); scanf("%99s", pattern);
    printf("Enter file name: ");         scanf("%99s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) { perror("Error opening file"); exit(1); }

    while (fgets(line, sizeof(line), file)) {
        lineno++;
        if (strstr(line, pattern) != NULL)
            printf("%d:%s", lineno, line);
    }
    fclose(file);
    return 0;
}
