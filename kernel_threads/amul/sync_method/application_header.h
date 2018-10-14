
#ifndef _APPLICATION_HEADER_H 
#define _APPLICATION_HEADER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include <assert.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>

#define BUF_LEN 100
#define LISTENBACKLOG 10

#define handle_error(msg) do { perror (msg) ; exit ( EXIT_FAILURE ) ; }\
    while(0) ; 

#define display_msg(stream,...) if ((fprintf(stream , ##__VA_ARGS__))<0)\
    handle_error("fprintf");

int create_unlock_mutex(void *) ; 

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[100];    /* message data */
};

int mutex_lock(int) ;
int mutex_unlock(int) ;
int get_msg_Id(void*) ;


#endif 
