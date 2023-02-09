#include "helpers/utility.h"
void do_all(int);
int main(int argc,char** argv)
{
    Addr addr;
    sockaddr_in sock_addr_ser,sock_addr_cli;
    pid_t pid;
    int sock_hdl,cli_len,new_sock_hdl;
    int cli_num=0;
    bzero((Addr*)&addr,sizeof(addr));
    bzero((sockaddr_in*)&sock_addr_ser,sizeof(sock_addr_ser));
    bzero((sockaddr_in*)&sock_addr_cli,sizeof(sock_addr_cli));
    cli_len=sizeof(sock_addr_cli);
    validate_S(argc,argv,(Addr*)&addr);
    sock_addr_ser.sin_addr.s_addr=addr.ip;
    sock_addr_ser.sin_family=AF_INET;
    sock_addr_ser.sin_port=addr.port;
    sock_hdl=socket(AF_INET,SOCK_STREAM,0);
    error_check("socket creation has failed!\n",sock_hdl);
    error_check("binding has failed!\n",bind(sock_hdl,(sockaddr*)&sock_addr_ser,sizeof(sock_addr_ser)));
    error_check("listeing has failed!\n",listen(sock_hdl,10));
    welcome_S(addr);
    while(1)
    {
        new_sock_hdl=accept(sock_hdl,(sockaddr*)&sock_addr_cli,&cli_len);
        error_check("there was a problem in accepting the connection!\n",new_sock_hdl);
        printf("%d total clients have been serviced.\n",++cli_num);
        pid=fork();
        error_check("there was a problem in forking!\n",pid);
        if(pid==0)
        {
            do_all(new_sock_hdl);
            exit(0);
        }
    }
    shutdown(sock_hdl,CLOSE_STATE);
}
void do_all(int sock_hdl)
{
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    bzero(response,BUFFER_SIZE);
    bzero(buffer,BUFFER_SIZE);
    int com_state;
    while(1)
    {
        com_state=recv(sock_hdl,buffer,BUFFER_SIZE-1,0);
        if(strlen(buffer)==0)
            break;
        error_check("could not read the msg from the clinet!\n",com_state);
        if(!strcmp(buffer,"exit"))
        {
            break;
        }
        strcpy(response,up(buffer));
        com_state=send(sock_hdl,response,BUFFER_SIZE-1,0); 
        error_check("could not send the msg from the clinet!\n",com_state);
        bzero(buffer,BUFFER_SIZE);
        bzero(response,BUFFER_SIZE);
    }
    shutdown(sock_hdl,CLOSE_STATE);
}