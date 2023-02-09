#include "helpers/client.h"
#include "helpers/utility.h"

int main(int argc,char** argv)
{
    char action[128];
    bzero(action,128);
    if(argc<1)
    {
        printf("no message was given!\n");
        exit(0);
    }
    if(argc>2)
    {
        printf("too many arguments  were given ignoring some o them!\n");
    }
    clock_t start, end;
    char state,f,flag;
    double time_passed;
    bzero(msg,CHUNK_SIZE);
    bzero(ans,CHUNK_SIZE);
    memcpy(msg,argv[1],(CHUNK_SIZE<=strlen(argv[1])?CHUNK_SIZE-1:strlen(argv[1])));
    int chunk;
    fd_a=shm_open("A",O_RDWR,0666);
    error_check("could not open the shared memory A!\n",fd_a); 
    fd_b=shm_open("B",O_RDWR,0666);
    error_check("could not open the shared memory A!\n",fd_b); 
    ctr_a=(Control_A*)mmap(NULL,sizeof(Control_A),PROT_WRITE|PROT_READ,MAP_SHARED,fd_a,0);
    ctr_b=(Control_B*)mmap(NULL,sizeof(Control_B),PROT_WRITE|PROT_READ,MAP_SHARED,fd_b,0);
    chunk=get_chunk();
    while (1)
    {
        write_msg(chunk);
        start=clock();
        while(!ctr_b->answered[chunk]);
        read_msg(chunk);
        end=clock();
        time_passed=(double)(end-start)/CLOCKS_PER_SEC;
        printf("there server replied with %s after %f seconds!\n",ans,time_passed);
        printf("would you like to send another message(yes/no)?\n");
        while (1)
        {
            fgets(action,128,stdin);
            if(action[strlen(action)-1]=='\n')
            {
                action[strlen(action)-1]='\0';
            }
            if(strcmp("YES",up(action))==0)
            {
                printf("please enter your message:\n");
                fgets(msg,CHUNK_SIZE,stdin);
                if(msg[strlen(msg)-1]=='\n')
                {
                     msg[strlen(msg)-1]='\0';
                }
                state='C';
                break;
            }
            else if (strcmp("NO",up(action))==0)
            {
                state='B';
                break;
            }
            else
            {
                printf("plaese choose between no and yes!\n");
            }
        }
        if(state=='C')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    cleanup(chunk);
}