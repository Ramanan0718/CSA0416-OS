#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/* File management with UNIX system calls: creat, open, write, read, close, unlink. */
int main() {
    int fd;
    char buf[100];
    ssize_t n;

    fd = creat("sample.txt", S_IRWXU);                 /* create (truncate) */
    if (fd == -1) { perror("creat"); exit(1); }
    printf("File 'sample.txt' created.\n");
    close(fd);

    fd = open("sample.txt", O_WRONLY | O_APPEND);       /* open for writing */
    if (fd == -1) { perror("open"); exit(1); }
    write(fd, "Hello, World!\n", 14);
    printf("Data written.\n");
    close(fd);

    fd = open("sample.txt", O_RDONLY);                  /* open for reading */
    if (fd == -1) { perror("open"); exit(1); }
    n = read(fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("Data read back:\n%s", buf);
    close(fd);

    if (unlink("sample.txt") == -1) { perror("unlink"); exit(1); }
    printf("File 'sample.txt' deleted.\n");
    return 0;
}
