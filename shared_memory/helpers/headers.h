#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#define CHUNK_NUM 1000
#define CHUNK_SIZE 8192
typedef struct Control_A Control_A;
typedef struct Control_B Control_B;
typedef struct Arg Arg;
struct Control_A
{
    bool available[CHUNK_NUM];
    bool need_service[CHUNK_NUM];  
    int msg_num;
    int num_client;
    int id[CHUNK_NUM];
    pthread_mutex_t client_lock;
    pthread_mutex_t msg_lock;
};
struct Control_B
{
    bool answered[CHUNK_NUM];
    int ans_num;
    pthread_mutex_t ans_lock;
};
