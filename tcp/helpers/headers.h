#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <syscall.h>
#include <unistd.h>
#include <time.h>
#define BUFFER_SIZE 8192
#define CLOSE_STATE 2
typedef struct Addr Addr;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
typedef struct in_addr in_addr;
struct Addr
{
    unsigned short port;
    unsigned long ip;
};