#include "headers.h"
#define NUM_THREAD 50
bool AVAILABLE[NUM_THREAD];
int chunks[NUM_THREAD-1];
Control_A* ctr_a;
Control_B* ctr_b;
int fd_a,fd_b;
int get_id()
{
    for(int i=2;;i=(i+1)%NUM_THREAD)
    {
        if(AVAILABLE[i]==true)
        {
            return i;
        }
    }
}
void init_A()
{
   ctr_a->msg_num=0;
   ctr_a->num_client=0;
   pthread_mutex_init(&ctr_a->client_lock,NULL);
   pthread_mutex_init(&ctr_a->msg_lock,NULL);
   for(int i=0;i<CHUNK_NUM;i++)
   {
       ctr_a->available[i]=true;
   } 
   for(int i=0;i<CHUNK_NUM;i++)
   {
       ctr_a->need_service[i]=false;
   }
   for(int i=0;i<CHUNK_NUM;i++)
   {
       ctr_a->id[i]=-1;
   }
   for(int i=2;i<NUM_THREAD;i++)
   {
       AVAILABLE[i]=true;
   }
   for(int i=0;i<NUM_THREAD-1;i++)
   {
       chunks[i]=-1;
   }
}
void init_B()
{
    ctr_b->ans_num=0;
    pthread_mutex_init(&ctr_b->ans_lock,NULL);
    for(int i=0;i<CHUNK_NUM;i++)
    {
        ctr_b->answered[i]=false;
    }
}
void write_ans(int chunk)
{
    char* msg=(char*)mmap(NULL,CHUNK_SIZE,PROT_WRITE|PROT_READ,MAP_SHARED,fd_a,(2+2*chunk)*4096);
    char* ans=(char*)mmap(NULL,CHUNK_SIZE,PROT_WRITE|PROT_READ,MAP_SHARED,fd_b,(1+2*chunk)*4096);
    bzero(ans,CHUNK_SIZE);
    memcpy(ans,up(msg),strlen(msg));
    pthread_mutex_lock(&ctr_b->ans_lock);
    ctr_b->ans_num++;
    pthread_mutex_unlock(&ctr_b->ans_lock);
    munmap(msg,CHUNK_SIZE);
    munmap(ans,CHUNK_SIZE);
}
void* do_all(void* arg)
{
    int* chunk=(int*)arg;
    write_ans(*chunk);
    ctr_b->answered[*chunk]=true;
    AVAILABLE[*chunk]=true;
    pthread_exit(NULL);
}
void retrieve(int chunk)
{
    ctr_a->id[chunk]=-1;
    ctr_a->available[chunk]=true;
    ctr_a->need_service[chunk]=false;
}
void* control(void* arg)
{
    int j=0;
    for(int i=0;i<CHUNK_NUM;i=(i+1)%CHUNK_NUM)
    {
        while (ctr_a->need_service[i]==false && ctr_a->available[i]==false)
        {
            if(j==15)
            {
                retrieve(i);
                break;
            }
            sleep(1);
            j++;
        }
        j=0;
    }
}
void* update(void* arg)
{
    while (1)
    {
        printf("number of clients :%d number of messages:%d\n",ctr_a->num_client,ctr_a->msg_num);
        sleep(5);
    }
}