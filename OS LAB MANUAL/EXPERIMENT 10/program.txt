#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct message {
    long msg_type;
    char msg_text[100];
};

/* Child (producer) sends a message; parent (consumer) receives it. */
int main() {
    key_t key = ftok("msgqfile", 65);
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) { perror("msgget"); exit(EXIT_FAILURE); }

    pid_t pid = fork();
    if (pid == 0) {                                  /* producer */
        struct message msg;
        msg.msg_type = 1;
        strcpy(msg.msg_text, "Hello, message queue!");
        if (msgsnd(msgid, &msg, strlen(msg.msg_text) + 1, 0) == -1) {
            perror("msgsnd"); exit(EXIT_FAILURE);
        }
        printf("Producer (child): sent    -> \"%s\"\n", msg.msg_text);
        exit(0);
    }

    wait(NULL);                                      /* consumer */
    struct message rcv;
    if (msgrcv(msgid, &rcv, sizeof(rcv.msg_text), 1, 0) == -1) {
        perror("msgrcv"); exit(EXIT_FAILURE);
    }
    printf("Consumer (parent): received -> \"%s\"\n", rcv.msg_text);

    if (msgctl(msgid, IPC_RMID, NULL) == -1) { perror("msgctl"); exit(EXIT_FAILURE); }
    return 0;
}
