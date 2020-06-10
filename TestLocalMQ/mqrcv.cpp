#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include "../Msg.hpp"
#include "../param.hpp"

#define PERMS 0644
//struct my_msgbuf {
//    long mtype;
//    char mtext[20];
//};

int main(void) {
    struct Msg buf;
    int msqid;
    int toend;
    key_t key;

    printf("size of mtext: %d\n",sizeof(buf.msgText));

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
        // this program ends wuth string of end
        if (msgrcv(msqid, &buf, MSG_SZ, 0, 0) == -1) {
            // print error "msgrcv: Identifier removed"
            perror("msgrcv");
            exit(1);
        }
        printf("rcved: %s\n", buf.msgText);
        // compare with "end"
        toend = strcmp(buf.msgText,"end");
        if (toend == 0)
            break;
    }
    printf("message queue: done receiving messages.\n");
    system("rm msgq.txt");
    return 0;
}
