#include "helpers/utility.h"
int main(int argc,char** argv)
{
    Addr addr;
    sockaddr_in serv_addr;
    clock_t start, end;
    double time_passed;
    char state;
    int sock_hdl,con,com_state;
    char f;
    char msg[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    char action[128];
    bzero((Addr*)&addr,sizeof(addr));
    bzero(msg,BUFFER_SIZE);
    bzero(buffer,BUFFER_SIZE);
    bzero(action,128);
    validate_C(argc,argv,(Addr*)&addr,msg);
    serv_addr.sin_addr.s_addr=addr.ip;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=addr.port;
    sock_hdl=socket(AF_INET,SOCK_STREAM,0);
    error_check("socket creation has failed!\n",sock_hdl);
    welcome_C(addr,msg);
    con=connect(sock_hdl,(sockaddr*)&serv_addr,sizeof(serv_addr));
    error_check("connection to the server failed!\n",con);
    while(1)
    {
        com_state=send(sock_hdl,msg,BUFFER_SIZE-1,0);
        start=clock();
        error_check("could not send the msg to the server!\n",com_state); 
        bzero(msg,BUFFER_SIZE);
        com_state=recv(sock_hdl,buffer,BUFFER_SIZE-1,0);
        end=clock();
        error_check("could not read the msg from the server!\n",com_state); 
        time_passed=(double)(end-start)/CLOCKS_PER_SEC;
        printf("the response is %s and it took %lfseconds!\n",buffer,time_passed);
        bzero(buffer,BUFFER_SIZE);
        printf("would you like to send another messaage(Yes/No)?\n");
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
                fgets(msg,BUFFER_SIZE,stdin);
                if(msg[strlen(msg)-1]=='\n')
                {
                     msg[strlen(msg)-1]='\0';
                }
                state='C';
                break;
            }
            else if (strcmp("NO",up(action))==0)
            {
                com_state=send(sock_hdl,"exit",BUFFER_SIZE-1,0);
                error_check("could not send the msg to the server!\n",com_state); 
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
    shutdown(sock_hdl,CLOSE_STATE); 
}