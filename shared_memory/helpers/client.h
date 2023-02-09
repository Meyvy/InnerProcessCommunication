#include "headers.h"
char msg[CHUNK_SIZE];
char ans[CHUNK_SIZE];
int fd_a,fd_b;
Control_A* ctr_a;
Control_B* ctr_b;
void validate_chunk(int chunk)
{
    if(getpid()!=ctr_a->id[chunk])
    {
        printf("accessing invalid chunk!\n");
        exit(0);
    }
}
int get_chunk()
{
    pthread_mutex_lock(&ctr_a->client_lock);
    for(int i=0;i<CHUNK_NUM;i++)
    {
        if(ctr_a->available[i]==true)
        {
            ctr_a->num_client++;
            ctr_a->id[i]=getpid();
            ctr_a->available[i]=false;
            pthread_mutex_unlock(&ctr_a->client_lock);
            return i;
        }
    }
    pthread_mutex_unlock(&ctr_a->client_lock);
    printf("no available chunk to allocate!\n");
    exit(0);
}
void write_msg(int chunk)
{
    validate_chunk(chunk);
    char* temp=(char*)mmap(NULL,CHUNK_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd_a,(2+2*chunk)*4096);
    bzero(temp,CHUNK_SIZE);
    memcpy(temp,msg,strlen(msg));
    munmap(temp,CHUNK_SIZE);
    ctr_a->need_service[chunk]=true;
    pthread_mutex_lock(&ctr_a->msg_lock);
    ctr_a->msg_num++;
    pthread_mutex_unlock(&ctr_a->msg_lock);
}
void read_msg(int chunk)
{
    validate_chunk(chunk);
    char* temp=(char*)mmap(NULL,CHUNK_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd_b,(1+2*chunk)*4096);
    bzero(ans,CHUNK_SIZE);
    memcpy(ans,temp,strlen(temp));
    ctr_b->answered[chunk]=false;
    munmap(temp,CHUNK_SIZE);
}
void cleanup(int chunk)
{
    validate_chunk(chunk);
    ctr_a->id[chunk]=-1;
    ctr_a->available[chunk]=true;
    ctr_a->need_service[chunk]=false;
    munmap(ctr_a,sizeof(Control_A));
    munmap(ctr_a,sizeof(Control_B));
    close(fd_a);
    close(fd_b);    
}