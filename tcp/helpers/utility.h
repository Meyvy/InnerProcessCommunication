#pragma once
#include "headers.h"
void welcome_S(Addr addr)
{
  in_addr in;
  in.s_addr=addr.ip;
  printf("a server with a passive socket has been created successfully!\n");
  printf("listening on ip address %s on the  port %hu \n",inet_ntoa(in),ntohs(addr.port));  
} 
void validate_S(int argc,char** argv,Addr* addr)
{
    if(argc<5)
    {
       printf("too few arguments to start the server!\n");
       exit(0);
    }
    else if(argc>5)
    {
       printf("too many arguments some of the arguments will be ignored!\n");
    }
    short int port_index=-1;
    short int ip_index=-1;
    for(short int i=1;i<argc;i++)
    {
        if(port_index!=-1 && ip_index!=-1)
        {
            break;
        }
        if(strcmp("-h",argv[i])==0 && i!=argc-1)
        {
            ip_index=i+1;
        }
        if(strcmp("-p",argv[i])==0  && i!=argc-1)
        {
            port_index=i+1;
        }
    }
    if(port_index==-1 && ip_index==-1)
    {
        printf("port and ip address could not be found!\n");
        exit(0);       
    }
    if(port_index==-1)
    {
        printf("port address could not be found!\n");
        exit(0);     
    }
    if(ip_index==-1)
    {
        printf("ip address could not be found!\n");
        exit(0); 
    }
    unsigned short port;
    port=atoi(argv[port_index]); 
    if(port<1024)
    {
        printf("the port is well known or invalid!\n");
        exit(0);
    }
    addr->port=htons(port);
    if(strcmp("any",argv[ip_index])==0)
    {
        addr->ip=INADDR_ANY;
    }
    else
    {
        if(inet_addr(argv[ip_index])==INADDR_NONE)
        {
            printf("invalid ip address!\n");
            exit(0);
        }
        addr->ip=inet_addr(argv[ip_index]);
    }
}
void validate_C(int argc,char** argv,Addr* addr,char* msg)
{
  if(argc<7)
    {
       printf("too few arguments to start the server!\n");
       exit(0);
    }
    else if(argc>7)
    {
       printf("too many arguments some of the arguments will be ignored!\n");
    }
  short int port_index=-1;
  short int ip_index=-1;
  short int msg_index=-1;
  for(short int i=1;i<argc;i++)
  {
     if(port_index!=-1 && ip_index!=-1 && msg_index!=-1)
        {
            break;
        }
     if(strcmp("-h",argv[i])==0 && i!=argc-1)
        {
            ip_index=i+1;
        }
     if(strcmp("-p",argv[i])==0  && i!=argc-1)
        {
            port_index=i+1;
        }
    if(strcmp("-m",argv[i])==0  && i!=argc-1)
        {
            msg_index=i+1;
        }   
  }
  unsigned short port;
  port=atoi(argv[port_index]); 
  if(port<1024)
    {
        printf("the port is well known or invalid!\n");
        exit(0);
    }
  addr->port=htons(port);
  if(inet_addr(argv[ip_index])==INADDR_NONE)
  {
     printf("invalid ip address!\n");
     exit(0);
  }
  addr->ip=inet_addr(argv[ip_index]);
  int msg_size=strlen(argv[msg_index]);
  memcpy(msg,argv[msg_index],(msg_size<BUFFER_SIZE)?msg_size:BUFFER_SIZE-1);
}
void welcome_C(Addr addr,char* msg)
{
  in_addr in;
  in.s_addr=addr.ip;
  printf("connection has been established successfully(ip=%s and port=%hu)!\n",inet_ntoa(in),ntohs(addr.port));
  printf("awaiting response!\n"); 
}
void error_check(char* msg,int state)
{
    if(state<0)
    {
        printf("exiting with the error code %d and the explanation:\n",state);
        printf("%s",msg);
        exit(0);
    }
}
char* up(char* msg)
{
    int j=0;
    while(msg[j])
    {
        msg[j]=toupper(msg[j]);
        j++;
    }
    return msg;
}