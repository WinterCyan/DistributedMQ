#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include "../Msg.hpp"
#include "../param.hpp"

#define PERMS 0644
//struct my_msgbuf {
//    long msgType;
//    char msgText[20];
//};

int main(void) {
    struct Msg buf;
    int msqid;
    int len;
    key_t key; // for message queue file
    system("touch msgq.txt");

    // create msgq file
    if ((key = ftok("msgq.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    printf("key: %d\n", key);

    // get msgq
    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
     }
    printf("msgid: %d\n", msqid);
    printf("message queue: ready to send messages.\n");
    printf("Enter lines of text, ^D to quit:\n");
    buf.msgType = 1; /* we don't really care in this case */

    // loop when running, re-loop when input '\n'
    for (int i = 0; i < 3; i++) {
        fgets(buf.msgText, sizeof buf.msgText, stdin);
        len = strlen(buf.msgText); // number of chars + 1, for '\n'
        printf("len: %d\n",len);
        // replace '\n' with '\0'
        if (buf.msgText[len - 1] == '\n') buf.msgText[len - 1] = '\0';
        // send msg
        if (msgsnd(msqid, &buf, MSG_SZ, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
//        printf("input in the loop: [%s]\n", buf.mtext);
    }

    // send "end" when Command^D
//    strcpy(buf.msgText, "end");
//    len = strlen(buf.msgText);
//    if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
//        perror("msgsnd");
//    // send "msgrcv: Identifier removed"
//    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
//        perror("msgctl");
//        exit(1);
//    }
//    printf("message queue: done sending messages.\n");

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
        int toend = strcmp(buf.msgText,"end");
        if (toend == 0)
            break;
    }
    printf("message queue: done receiving messages.\n");
    system("rm msgq.txt");
    return 0;
}

