#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF 4096

int main() {
    int src, dst;
    char buf[BUF];
    ssize_t n;

    src = open("source.txt", O_RDONLY);                       /* open source  */
    if (src < 0) { perror("open source"); return 1; }

    dst = open("copy.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); /* open dest */
    if (dst < 0) { perror("open destination"); return 1; }

    while ((n = read(src, buf, BUF)) > 0)                     /* read  */
        write(dst, buf, n);                                   /* write */

    close(src);
    close(dst);
    printf("File copied from source.txt to copy.txt successfully.\n");
    return 0;
}
