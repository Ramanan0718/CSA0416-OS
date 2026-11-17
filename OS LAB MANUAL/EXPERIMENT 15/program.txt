#include <stdio.h>
#include <string.h>

/* Two-level directory: a master file directory (MFD) with one
   user directory (UFD) per user; each UFD holds that user's files. */
#define MAX_USERS 10
#define MAX_FILES 20
#define NAME_LEN 32

struct UFD { char user[NAME_LEN]; char files[MAX_FILES][NAME_LEN]; int nfiles; };
struct UFD mfd[MAX_USERS];
int nusers = 0;

int find_user(const char *u) {
    for (int i = 0; i < nusers; i++) if (strcmp(mfd[i].user, u) == 0) return i;
    return -1;
}

int add_user(const char *u) {
    if (nusers == MAX_USERS) return -1;
    strcpy(mfd[nusers].user, u);
    mfd[nusers].nfiles = 0;
    return nusers++;
}

void create_file(const char *u, const char *f) {
    int i = find_user(u);
    if (i < 0) { i = add_user(u); printf("New user directory created for '%s'.\n", u); }
    for (int k = 0; k < mfd[i].nfiles; k++)
        if (strcmp(mfd[i].files[k], f) == 0) { printf("'%s' already exists in %s.\n", f, u); return; }
    strcpy(mfd[i].files[mfd[i].nfiles++], f);
    printf("File '%s' created in directory of %s.\n", f, u);
}

void list_dir(const char *u) {
    int i = find_user(u);
    if (i < 0) { printf("No directory for user '%s'.\n", u); return; }
    printf("Directory of %s (%d files):\n", u, mfd[i].nfiles);
    for (int k = 0; k < mfd[i].nfiles; k++) printf("  %s\n", mfd[i].files[k]);
}

void delete_file(const char *u, const char *f) {
    int i = find_user(u);
    if (i < 0) { printf("No directory for user '%s'.\n", u); return; }
    for (int k = 0; k < mfd[i].nfiles; k++)
        if (strcmp(mfd[i].files[k], f) == 0) {
            for (int j = k; j < mfd[i].nfiles - 1; j++) strcpy(mfd[i].files[j], mfd[i].files[j + 1]);
            mfd[i].nfiles--;
            printf("File '%s' deleted from %s.\n", f, u);
            return;
        }
    printf("File '%s' not found in %s.\n", f, u);
}

int main() {
    int choice;
    char user[NAME_LEN], file[NAME_LEN];
    do {
        printf("\n1. Create file  2. List user directory  3. Delete file  4. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1:
                printf("User: "); scanf("%31s", user);
                printf("File: "); scanf("%31s", file);
                create_file(user, file); break;
            case 2:
                printf("User: "); scanf("%31s", user);
                list_dir(user); break;
            case 3:
                printf("User: "); scanf("%31s", user);
                printf("File: "); scanf("%31s", file);
                delete_file(user, file); break;
            case 4: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
    return 0;
}
