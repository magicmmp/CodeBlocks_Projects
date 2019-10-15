#include "vxWorks.h"
#include "taskLib.h"
#include "sockLib.h"
#include "stdioLib.h"
#include "inetLib.h"
#define TASK_STACK_SIZE 20000
    int tcpLoop;
    int cmd_fd;
    int txt_fd;
    int data_fd;
    char *buff;
    char *buffTmp;

void cmd_send()
{
    send(cmd_fd,"I am cmd send thread of vxworks.",22,MSG_DONTWAIT);
    taskDelay(3600);
    send(cmd_fd,"stop",4,MSG_DONTWAIT);
    taskDelay(30);
    tcpLoop=0;
    close(cmd_fd);
    printf("exit cmd send thread.\n");
}


void get_txt()
{
    unsigned int Len;
    unsigned char tcpBuffHeader[4];
    recv(txt_fd,tcpBuffHeader,4,0) ;
    Len=*(unsigned int*)tcpBuffHeader;
    printf("*(unsigned int*)tcpBuffHeader= %X\n",Len);

    send(txt_fd,"I am txt get thread.",21,MSG_DONTWAIT);
    close(txt_fd);
    printf("exit get txt thread.\n");
}



void dataRecv()
{
    int len;
    int i;
    int nPacket=0;
    int tmpLen;
    unsigned int eventLen;
    char chTmp;
    while(tcpLoop)
    {
        len=recv(data_fd,buff,4,0) ;
        if(len>0)
        {
            chTmp=buff[0];
            buff[0]=buff[3];
            buff[3]=chTmp;
            chTmp=buff[1];
            buff[1]=buff[2];
            buff[2]=chTmp;
            eventLen=*(int*)buff;
            eventLen=*(unsigned int*)buff;
            *(unsigned int*)buff=0;
            tmpLen=0;
            while(tmpLen<eventLen && tcpLoop)
            {
                len=recv(data_fd,buff+tmpLen+4,eventLen-tmpLen,0) ;
                if(len>0)
                {
                    tmpLen=tmpLen+len;
                }
                else if(len==0)
                {
                    tcpLoop=0;
                    printf("tcp socket closed by remote end.\n");
                }
                else
                {
                    printf("tcp socket return len =-1.\n");
                }
            }

        }
        else if(len==0)
        {
            tcpLoop=0;
            printf("tcp socket closed by remote end.\n");
        }
        else
        {
            printf("tcp socket return len =-1.\n");
        }
        if(tmpLen==eventLen && tmpLen>20)
        {
           for(i=0;i<5;i++)
              memcpy(buffTmp, buff, eventLen);
           nPacket++;
           tmpLen=0;
        }
    }
    close(data_fd);
    printf("%d events received.\n",nPacket);
    printf("exit data recv thread.\n");
}

int mainFun()
{
    int  cmd_tid;
    int  txt_tid;
    int  data_tid;
    struct sockaddr_in    servaddr;
    buff=malloc(66056);
    buffTmp=malloc(66056);
    cmd_fd = socket(AF_INET, SOCK_STREAM, 0);
    txt_fd = socket(AF_INET, SOCK_STREAM, 0);
    data_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(56898);
    servaddr.sin_addr.s_addr=inet_addr("192.168.1.200");
    tcpLoop=1;
    connect(cmd_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    connect(txt_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    connect(data_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));



        txt_tid=taskSpawn("txt_get_task", 150, 0, TASK_STACK_SIZE, (FUNCPTR)get_txt,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        cmd_tid=taskSpawn("cmd_send_task", 150, 0, TASK_STACK_SIZE, (FUNCPTR)cmd_send,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        data_tid=taskSpawn("TCP_data_recv_task", 150, 0, TASK_STACK_SIZE, (FUNCPTR)dataRecv,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        while(tcpLoop)
        {
            taskDelay(60);
        }

        free(buff);
        free(buffTmp);

        printf("Vxworks shutdown.\n");
}











