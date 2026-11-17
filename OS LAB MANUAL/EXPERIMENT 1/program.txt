#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();              /* create a new process */

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {                  /* child */
        printf("[Child]  PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {                         /* parent */
        printf("[Parent] PID = %d, Parent PID = %d, Child PID = %d\n",
               getpid(), getppid(), pid);
        wait(NULL);
    }
    return 0;
}
