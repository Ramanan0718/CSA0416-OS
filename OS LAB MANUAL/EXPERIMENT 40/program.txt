#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* Shows the permission bits of a file (owner/group/others) and changes them with chmod. */
void print_perm(const char *name) {
    struct stat st;
    if (stat(name, &st) != 0) { perror("stat"); exit(1); }
    printf("%s  ", S_ISDIR(st.st_mode) ? "d" : "-");
    printf("%c%c%c", st.st_mode & S_IRUSR ? 'r' : '-', st.st_mode & S_IWUSR ? 'w' : '-', st.st_mode & S_IXUSR ? 'x' : '-');
    printf("%c%c%c", st.st_mode & S_IRGRP ? 'r' : '-', st.st_mode & S_IWGRP ? 'w' : '-', st.st_mode & S_IXGRP ? 'x' : '-');
    printf("%c%c%c", st.st_mode & S_IROTH ? 'r' : '-', st.st_mode & S_IWOTH ? 'w' : '-', st.st_mode & S_IXOTH ? 'x' : '-');
    printf("  (octal %o)  owner uid=%d\n", st.st_mode & 0777, (int)st.st_uid);
}

int main() {
    const char *name = "file.txt";
    int fd = open(name, O_WRONLY | O_CREAT, 0600);   /* owner rw only */
    if (fd == -1) { perror("open"); return 1; }
    write(fd, "permission demo\n", 16);
    close(fd);

    printf("Before chmod (owner=user, group=group, others=other):\n");
    print_perm(name);

    /* rw-rw-r--: owner and group read/write, others read only */
    if (chmod(name, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH) != 0) {
        perror("chmod"); return 1;
    }
    printf("After chmod 664 (rw-rw-r--):\n");
    print_perm(name);

    printf("\nPermission meaning: r=4 read, w=2 write, x=1 execute; "
           "digits are owner, group, others.\n");
    return 0;
}
