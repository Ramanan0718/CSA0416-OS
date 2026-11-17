#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

/* Demonstrates: fcntl, lseek, stat, opendir, readdir. */
int main() {
    int fd = open("foo.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) { perror("open"); return 1; }
    write(fd, "0123456789", 10);

    /* fcntl: inspect the file status flags */
    int flags = fcntl(fd, F_GETFL);
    printf("fcntl F_GETFL: access mode = %s\n",
           (flags & O_ACCMODE) == O_RDWR ? "read/write" : "other");

    /* lseek: move the file offset */
    off_t pos = lseek(fd, 3, SEEK_SET);
    char c; read(fd, &c, 1);
    printf("lseek to 3 -> offset %ld, byte there = '%c'\n", (long)pos, c);
    close(fd);

    /* stat: file size and type */
    struct stat st;
    if (stat("foo.txt", &st) == 0)
        printf("stat foo.txt: size = %ld bytes, regular file = %s\n",
               (long)st.st_size, S_ISREG(st.st_mode) ? "yes" : "no");

    /* opendir / readdir: list the current directory */
    DIR *dir = opendir(".");
    if (dir == NULL) { perror("opendir"); return 1; }
    printf("Entries in current directory:\n");
    struct dirent *de;
    while ((de = readdir(dir)) != NULL)
        if (de->d_name[0] != '.') printf("  %s\n", de->d_name);
    closedir(dir);
    return 0;
}
