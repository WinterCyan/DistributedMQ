//
// Created by Winter Cyan on 2020/6/7.
//

#ifndef DISTRIBUTEDMQ_PARAM_HPP
#define DISTRIBUTEDMQ_PARAM_HPP

#define DEFAULT_DEST_QM "QM3"
#define CHAR_SET "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define MSG_SZ 40
#define QM_NAME_SZ 20
#define DEST_QM_SIZE 4
#define PORT 9090
#define BUFFER_SIZE 1024

enum MCA_STATUS {RUNNING, SUSPENDED, STOPPED};
//static const std::string DEST_QM_ARRAY[DEST_QM_SIZE] {"QM1","QM2","QM3","QM4","QM5"};
static const std::string DEST_QM_ARRAY[DEST_QM_SIZE] {"QM1","QM2","QM3","QM4"};


#endif //DISTRIBUTEDMQ_PARAM_HPP
