#include <stdio.h>
#include <string.h>

/* Single-level directory: one flat list of files shared by all users. */
#define MAX_FILES 50
#define NAME_LEN 32

char files[MAX_FILES][NAME_LEN];
int count = 0;

void create_file(const char *name) {
    for (int i = 0; i < count; i++)
        if (strcmp(files[i], name) == 0) { printf("File '%s' already exists.\n", name); return; }
    if (count == MAX_FILES) { printf("Directory is full.\n"); return; }
    strcpy(files[count++], name);
    printf("File '%s' created.\n", name);
}

void list_files(void) {
    printf("Directory (%d files):\n", count);
    for (int i = 0; i < count; i++) printf("  %s\n", files[i]);
}

void delete_file(const char *name) {
    for (int i = 0; i < count; i++)
        if (strcmp(files[i], name) == 0) {
            for (int j = i; j < count - 1; j++) strcpy(files[j], files[j + 1]);
            count--;
            printf("File '%s' deleted.\n", name);
            return;
        }
    printf("File '%s' not found.\n", name);
}

int main() {
    int choice;
    char name[NAME_LEN];
    do {
        printf("\n1. Create  2. List  3. Delete  4. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1: printf("File name: "); scanf("%31s", name); create_file(name); break;
            case 2: list_files(); break;
            case 3: printf("File name: "); scanf("%31s", name); delete_file(name); break;
            case 4: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
    return 0;
}
