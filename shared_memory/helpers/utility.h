#include "headers.h"
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