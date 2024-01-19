#ifndef THREADED_SOCKET_IO_H
#define THREADED_SOCKET_IO_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <pthread.h>

#define PORT 1920
#define BACKLOG 3
#define BUFFER_SIZE 2048


void default_callback(char * input, char * output, ssize_t i_sz, ssize_t *o_sz);

//Definition for callback function type.
typedef void(*IOFUNC)(char *, char *, ssize_t, ssize_t*);

//Helper function, checks functions have error.
void check(int val, char * errorMsg);
//Function that used in thread to handle socket input-output.
void * handleConnection(void* sock_desc);
//Function that create socket.
int createSocket(int port, IOFUNC adapter_function);

#endif
