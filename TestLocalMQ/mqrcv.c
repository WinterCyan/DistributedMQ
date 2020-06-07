#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define PERMS 0644
struct my_msgbuf {
    long mtype;
    char mtext[200];
};

int main(void) {
    struct my_msgbuf buf;
    int msqid;
    int toend;
    key_t key;

    // get msq file
    if ((key = ftok("msgq.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    printf("key: %d\n", key);

    // get msgq
    if ((msqid = msgget(key, PERMS)) == -1) { /* connect to the queue */
        perror("msgget");
        exit(1);
    }
    printf("msgid: %d\n", msqid);
    printf("message queue: ready to receive messages.\n");
    for(;;) {
        // normally receiving never ends but just to make conclusion 
        // this program ends with string of end
        // rcv 200 chars
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            // print error "msgrcv: Identifier removed"
            perror("msgrcv");
            exit(1);
        }
        printf("rcved: %s\n", buf.mtext);
        // compare with "end"
        toend = strcmp(buf.mtext,"end");
        if (toend == 0)
            break;
    }
    printf("message queue: done receiving messages.\n");
    system("rm msgq.txt");
    return 0;
}
