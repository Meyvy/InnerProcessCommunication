#include "helpers/utility.h"
#include "helpers/server.h"
int main()
{   
    pthread_t id[NUM_THREAD];
    pid_t pid;
    int j=0,i=0;
    fd_a=shm_open("A",O_CREAT|O_RDWR,0666);
    error_check("could not create the shared memory A!\n",fd_a); 
    fd_b=shm_open("B",O_CREAT|O_RDWR,0666);
    error_check("could not create the shared memory B!\n",fd_b); 
    error_check("could not allocate the desired memory to A!\n",ftruncate(fd_a,2*4096+CHUNK_NUM*CHUNK_SIZE)); 
    error_check("could not allocate the desired memory to B!\n",ftruncate(fd_b,4096+CHUNK_NUM*CHUNK_SIZE));
    ctr_a=(Control_A*)mmap(NULL,sizeof(Control_A),PROT_WRITE|PROT_READ,MAP_SHARED,fd_a,0);
    ctr_b=(Control_B*)mmap(NULL,sizeof(Control_B),PROT_WRITE|PROT_READ,MAP_SHARED,fd_b,0);
    init_A(ctr_a);
    init_B(ctr_b);
    printf("listeing to the clients!\n");
    pthread_create(&id[0],NULL,control,NULL);
    pthread_create(&id[1],NULL,update,NULL);
    while (1)
    {
        if(ctr_a->need_service[j]==true)
        {   
            ctr_a->need_service[j]=false;
            i=get_id();
            AVAILABLE[i]=false;
            chunks[i]=j;
            pthread_create(&id[i],NULL,do_all,(void*)&chunks[i]);
        }
        j=(j+1)%CHUNK_NUM;
    }
}