#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

/* Simulates the UNIX 'ls' command: list the names in a directory. */
int main() {
    char path[256];
    printf("Enter directory to list (. for current): ");
    scanf("%255s", path);

    DIR *dir = opendir(path);
    if (dir == NULL) { perror("opendir"); return 1; }

    struct dirent *de;
    struct stat st;
    char full[512];
    while ((de = readdir(dir)) != NULL) {
        if (de->d_name[0] == '.') continue;          /* hide dotfiles like ls */
        snprintf(full, sizeof(full), "%s/%s", path, de->d_name);
        stat(full, &st);
        printf("%s%s\n", de->d_name, S_ISDIR(st.st_mode) ? "/" : "");
    }
    closedir(dir);
    return 0;
}
