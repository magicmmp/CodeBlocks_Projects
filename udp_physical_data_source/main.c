#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

/** hit count=10 **/
/** need 106 of int length **/
#define N     2  /*HIT_COUNT, 0~255*/
#define M     ((N<<1)+6)
#define rocNo 32  /*32个ROC都在发数据*/
/*cgem ROC number，1<=rocNo<=32，应该设置2个rocNo，
  假设发送端有send_rocNo个ROC在工作，而接收端只处理列表里的rocID*/
/*rocID从0开始，rocNO从1开始*/
const int BUFFSIZE=M<<2;  /*根据HIT_CONUT算出来的发送包长度*/
#define eventNo 1024  /*rocBuff缓存事例个数*/
const int maxPacketLen=2096; /*为一个ROC包预留的最大内存*/
/*需要接收这些rocID的UDP数据并拼接在一起*/
const int rocID_List[33]={32,1,3,4,6,30};
/*第一个数表示有效ROC总数，后面是具体的rocID号,为避免0号ID无故被使能，编号从1到32*/
int       rocID_enable[32];/*在列表的rocID对应的值为1，否则为0*/
unsigned int rocFLAG;  /*数据是否有效的标记，对应位1代表现存数据无效，0代表数据有效待发送*/
typedef struct {
    /*Header*/
    unsigned int STATUS_BITS;/*is 0*/
    unsigned int LOCAL_L1_COUNT; /*Increment by 1*/
    unsigned int HIT_COUNT;
    unsigned int Timestamp;
    /*1个HIT的data*/
    unsigned int D_TIGER_ID;
    unsigned int LAST_TIGER_FRAME_NUMBER;
    long long RAW_DATA;
    /*Tailer*/
    unsigned int LOCAL_L1_FRAMENUM;
    unsigned int T_TIGER_ID; /*tailer TIGER_ID*/
    unsigned int GEMROC_ID;
    unsigned int CH_ID;
    unsigned int LAST_COUNT_WORD_FROM_TIGER_DATA;
    /*UDP Sequence Counter*/
    long long UDP_packet_count;
    unsigned int S_GEMROC_ID;
}para;

typedef struct   /*一个事例对应的各个ROC的buffer信息*/
{
    unsigned int trigNo;  /*现在存放的触发号*/
    unsigned int flag;    /*每位对应32个ROC的数据是否有效*/
    unsigned char**rocBuff; /*实际ROC数<=32，如果有些ROC数据过期了，要释放掉内存，地址置0，以后有需要再申请*/
}UDPBUFF_INFO;


UDPBUFF_INFO udpInfo[eventNo]; /* 名字要改为 eventInfo ,预留256个事例的缓存*/

int rocBuff_init()  /*程序开始的时候初始化结构体数组*/
{
    int i,j;
    for(i=0;i<32;i++)
        rocID_enable[i]=0;

    if(rocID_List[0]>=32)
    {
        for(i=0;i<32;i++)
            rocID_enable[i]=1;
        rocFLAG=0xffffffff;
    }
    else
    {
        rocFLAG=0;
        for(i=1;i<=rocID_List[0];i++)
        {
            rocID_enable[rocID_List[i]-1]=1;
            rocFLAG=rocFLAG|(0x1<<rocID_List[i]-1);
        }
        j=0;
        for(i=0;i<32;i++)
            if(rocID_enable[i])
                j++;
        if(j!=rocID_List[0])
        {
            printf("Error,number of ROC enabled is not right.\n");
            return -1;
        }
    }
    for(i=0;i<eventNo;i++)
    {
        udpInfo[i].rocBuff=(unsigned char**)malloc(sizeof(unsigned char*)*32);
        if (udpInfo[i].rocBuff == NULL)
        {
            printf("Couldn't allocate memory for udpInfo[%d].rocBuff !\n",i);
            return -1;
        }
        for(j=0;j<32;j++)
        {
            udpInfo[i].rocBuff[j]=NULL;
            if(rocID_enable[j])
                udpInfo[i].rocBuff[j]=(unsigned char*)malloc(maxPacketLen);
            else
                udpInfo[i].rocBuff[j]=(unsigned char*)malloc(4);
            if (udpInfo[i].rocBuff[j] == NULL)
            {
                printf("Couldn't allocate memory for udpInfo[%d].rocBuff[%d] !\n",i,j);
                return -1;
            }
            *(unsigned int*)udpInfo[i].rocBuff[j]=0;
        }
        udpInfo[i].trigNo=0;
        udpInfo[i].flag=rocFLAG; /*1对应过期数据，0表示有效数据，高位的0也认为有效但用不上*/
    }

    printf("HIT_COUNT=%d, BUFFSIZE=%d\n",N,BUFFSIZE);
    printf("rocFLAG=%08X\n",rocFLAG);
    printf("Receive rocID enable:\n");
    for(i=0;i<32;i++)
    {
        printf("rocID %d : ",i);
        if(rocID_enable[i])
            printf("yes\n");
        else
            printf("no\n");
    }
    for(i=0;i<32;i++)
        if(rocID_enable[i])
            printf("ROC %d is receive enable.\n",i);

    return 0;
}
/*
  （1）进入这个函数的buff被认为是格式正确的，只是还要检查数据是否过期。
  （2）返回0继续接受数据，返回-1表示出错或丢弃了一个不完整的旧事例，
       返回1表示收满一个事例了，要udp循环一次，然后复制给cbltRng*/
int copy_to_rocBuff(unsigned char*udpRecvBuff,unsigned int buffLen,
                unsigned int  trgNo,unsigned int  rocID)
{
    if(rocID_enable[rocID]==0)
    {
        //printf("Recv an extra packet,triggerID=%d, rocID=%d\n",trgNo,rocID);
        return 0;
    }
    unsigned int idx=trgNo%eventNo;
    int i;
    if(trgNo==udpInfo[idx].trigNo)
    {
        if((udpInfo[idx].flag>>rocID)&0x1)
        {
            *(unsigned int*)udpInfo[idx].rocBuff[rocID] =buffLen;
            memcpy(udpInfo[idx].rocBuff[rocID]+4,udpRecvBuff,buffLen);

            udpInfo[idx].flag=udpInfo[idx].flag&(0xffffffff^(0x1<<rocID));
            if(udpInfo[idx].flag==0)  /*发送完整buff后要重置flag*/
                return 1;
            else
                return 0;
        }
        else  /*if receive a duplicate packet*/
        {
            /*把重复的2个roc包打印出来部分看看*/
            printf("Error! Receive a duplicate packet,TrigerID=%d, rocID=%d .\n",trgNo,rocID);
            printf("packet 1, length= %d: ,",*(unsigned int*)udpInfo[idx].rocBuff[rocID]);
            for(i=0;i<*(unsigned int*)udpInfo[idx].rocBuff[rocID] && i<32;i++)
            {
                if(i&0x11==0)
                    printf(" ");
                printf("%02X",udpInfo[idx].rocBuff[rocID][i+4]);
            }
            printf("\npacket 2, length= %d: ,",buffLen);
            for(i=0;i<buffLen && i<32;i++)
            {
                if(i&0x11==0)
                    printf(" ");
                printf("%02X",udpInfo[idx].rocBuff[rocID][i]);
            }
            printf("\n");
            return 0;
        }
    }
    else if(trgNo>udpInfo[idx].trigNo)
    {
        if(udpInfo[idx].flag!=rocFLAG)
            printf("Found a udp packet missed,its triggerNo=%d.\n",udpInfo[idx].trigNo);
        *(unsigned int*)udpInfo[idx].rocBuff[rocID] =buffLen;
        memcpy(udpInfo[idx].rocBuff[rocID]+4,udpRecvBuff,buffLen);
        udpInfo[idx].flag=rocFLAG&(0xffffffff^(0x1<<rocID)); /*更新flag有效标志*/
        udpInfo[idx].trigNo=trgNo; /*更新触发号*/
        if(udpInfo[idx].flag==0)  /*如果只有一个ROC，则已收满*/
            return 1;
        else
            return 0;
    }
    else
    {
        printf("Recv a expired udp packet,triggerNo packet=%d, rocID=%d.\n",trgNo,rocID);
        return 0;
    }
}
void copy_to_sendBuff(unsigned int trgID,unsigned char*outputBuff)
{
    trgID=trgID%eventNo;
   unsigned int sndLen=0;/*仅用于提示本机的udp发送函数，要发送数据的长度*/
   int i,j;
   int idx=4;
   unsigned int rocTmplen;
   for(i=0;i<32;i++)
   if(rocID_enable[i])
   {
       rocTmplen=*(unsigned int*)udpInfo[trgID].rocBuff[i];
       memcpy(outputBuff+idx,udpInfo[trgID].rocBuff[i]+4,rocTmplen);
       idx=idx+rocTmplen;
       sndLen=sndLen+rocTmplen;
   }
   *(unsigned int*)outputBuff=sndLen;
   udpInfo[trgID].flag=rocFLAG;
}

void rocBuff_delete()
{
    int i,j;
    for(i=0;i<eventNo;i++)
    for(j=0;j<32;j++)
        if (udpInfo[i].rocBuff[j])
        {
            free(udpInfo[i].rocBuff[j]);
            udpInfo[i].rocBuff[j]=NULL;
        }
    free(udpInfo[i].rocBuff);
}

/*先在para结构体设置好各个字段的初值。有意义的字段手动递增。再复制到字符数组buff,再由网络发送出去*/
void change_para(para *p,unsigned int*data,int datalen,unsigned char*buff,int buflen)
{

    int i,tmp;
    int Va;  /*test if is little end*/
    for(i=0;i<datalen;i++)
        data[i]=0;

    data[0]=(0x6<<29)+((p->STATUS_BITS & 0x7)<<26)+(p->LOCAL_L1_COUNT>>6);
    data[1]=((p->LOCAL_L1_COUNT & 0x3F)<<24) + ((p->HIT_COUNT & 0xff) <<16) +(p->Timestamp & 0xffff);

    p->Timestamp++;
    for(i=2;i<2*(p->HIT_COUNT)+1;i=i+2)
    {
        p->RAW_DATA++;
        data[i]=((p->D_TIGER_ID & 0x7)<<27 )+( (p->LAST_TIGER_FRAME_NUMBER&0x7) <<24)+((p->RAW_DATA>>30) & 0xffffff);
        data[i+1]=p->RAW_DATA & 0x3fffffff;
    }
    p->LAST_TIGER_FRAME_NUMBER++;

    /*tailer*/
    i=datalen-4;
    data[i]=(0x7<<29)+((p->LOCAL_L1_FRAMENUM &0xffffff)<<5) + (p->GEMROC_ID&0x1f);
    p->LOCAL_L1_FRAMENUM++;
    i++;
    data[i]=((p->D_TIGER_ID &0x7)<<27)+ ((p->LOCAL_L1_COUNT&0x7)<<24)+((p->CH_ID&0x3f)<<18)+ (p->LAST_COUNT_WORD_FROM_TIGER_DATA&0x3ffff);
    p->LAST_COUNT_WORD_FROM_TIGER_DATA++;

    /*sequence*/
    i++;
    data[i]=(0x1<<30) + ((p->GEMROC_ID&0x1f)<<20)+ ((p->UDP_packet_count>>28)&0xfffff);
    i++;
    data[i]=(0x1<<30) + (p->UDP_packet_count & 0xfffffff);
    p->UDP_packet_count++;
    memcpy(buff,(char*)data,buflen);
    Va=1;
    if (*(char*)&Va == 1)
    for(i=0;i<buflen;i=i+4)
    {
        tmp=buff[i];
        buff[i]=buff[i+3];
        buff[i+3]=tmp;
        tmp=buff[i+1];
        buff[i+1]=buff[i+2];
        buff[i+2]=tmp;
    }
}
/*
1、数据8字节一组，肯定是小端模式：数据的高字节保存在内存的高地址中，而数据的低字节保存在内存的低地址中，
  这种存储模式将地址的高低和数据位权有效地结合起来，高地址部分权值高，低地址部分权值低。*/
/*一帧数据的检查，假设从socket接收的data字符数组已经调整为大端模式，高位字节在内存低地址。*/
/*PRE_COUNT上次的数据包计数，会递增，应该是和当前的 LOCAL_L1_COUNT比较*/

int extract_or_print_udp_para(unsigned char*buff,unsigned int buflen,para* p,int print_enable)
{
    unsigned int tmp_idx;
    unsigned int i;

    if(buflen<24)
    {
        printf("buff length =%d,  error .\n",buflen);
        return -1;
    }
    if((buff[0]>>5)!=6)
    {
        printf("header_flag= %d, error .\n",buff[0]>>5);
        return -1;
    }
    p->STATUS_BITS=(buff[0]>>2)&0x7;

    p->LOCAL_L1_COUNT=buff[0]&0x3;
    p->LOCAL_L1_COUNT=p->LOCAL_L1_COUNT<<8;
    p->LOCAL_L1_COUNT=p->LOCAL_L1_COUNT+buff[1];
    p->LOCAL_L1_COUNT=p->LOCAL_L1_COUNT<<8;
    p->LOCAL_L1_COUNT=p->LOCAL_L1_COUNT+buff[2];
    p->LOCAL_L1_COUNT=p->LOCAL_L1_COUNT<<8;
    p->LOCAL_L1_COUNT=p->LOCAL_L1_COUNT+buff[3];
    p->LOCAL_L1_COUNT=p->LOCAL_L1_COUNT<<6;
    p->LOCAL_L1_COUNT=p->LOCAL_L1_COUNT+(buff[4]&0x3f);

    p->HIT_COUNT=buff[5];

    p->Timestamp=buff[6];
    p->Timestamp=p->Timestamp<<8;
    p->Timestamp=p->Timestamp+buff[7];

    if((p->HIT_COUNT<<3)+24 != buflen)
    {
        printf("HIT_COUNT= %d, recv buff length error .\n",p->HIT_COUNT);
        return -1;
    }

    /* tailer part */
    tmp_idx=(p->HIT_COUNT<<3)+8;

    if((buff[tmp_idx]>>5)!=7)
    {
        printf("tailer_flag= %d, error .\n",buff[tmp_idx]>>5);
        return -1;
    }

    p->LOCAL_L1_FRAMENUM=buff[tmp_idx]&0x1f;
    p->LOCAL_L1_FRAMENUM=p->LOCAL_L1_FRAMENUM<<8;
    tmp_idx++;
    p->LOCAL_L1_FRAMENUM=p->LOCAL_L1_FRAMENUM+buff[tmp_idx];
    p->LOCAL_L1_FRAMENUM=p->LOCAL_L1_FRAMENUM<<8;
    tmp_idx++;
    p->LOCAL_L1_FRAMENUM=p->LOCAL_L1_FRAMENUM+buff[tmp_idx];
    p->LOCAL_L1_FRAMENUM=p->LOCAL_L1_FRAMENUM<<3;
    tmp_idx++;
    p->LOCAL_L1_FRAMENUM=p->LOCAL_L1_FRAMENUM+(buff[tmp_idx]>>5);
    p->GEMROC_ID=buff[tmp_idx]&0x1f;

    tmp_idx++;
    p->T_TIGER_ID=(buff[tmp_idx]>>3)&0x7;
    if((buff[tmp_idx] & 0x7) != (p->LOCAL_L1_COUNT & 0x7) )
    {
        printf("buff[tmp_idx]&0x7= %d , ",buff[tmp_idx] & 0x7);
        printf("LOCAL_L1_COUNT & 0x7= %d , error.\n",p->LOCAL_L1_COUNT & 0x7);
        return -1;
    }
    tmp_idx++;
    p->CH_ID=buff[tmp_idx]>>2;

    p->LAST_COUNT_WORD_FROM_TIGER_DATA=buff[tmp_idx]&0x3;
    p->LAST_COUNT_WORD_FROM_TIGER_DATA=p->LAST_COUNT_WORD_FROM_TIGER_DATA<<8;
    tmp_idx++;
    p->LAST_COUNT_WORD_FROM_TIGER_DATA=p->LAST_COUNT_WORD_FROM_TIGER_DATA + buff[tmp_idx];
    p->LAST_COUNT_WORD_FROM_TIGER_DATA=p->LAST_COUNT_WORD_FROM_TIGER_DATA<<8;
    tmp_idx++;
    p->LAST_COUNT_WORD_FROM_TIGER_DATA=p->LAST_COUNT_WORD_FROM_TIGER_DATA + buff[tmp_idx];
    /*UDP Sequence Counter part*/
    tmp_idx++;

    if((buff[tmp_idx]>>4)!=4)
    {
        printf(" sequence_falg1 = %d, sequence_falg1!=4 ,error.\n",buff[tmp_idx]>>4);
        return -1;
    }


    p->S_GEMROC_ID=buff[tmp_idx]&0x1;
    p->S_GEMROC_ID=p->S_GEMROC_ID<<4;
    tmp_idx++;
    p->S_GEMROC_ID=p->S_GEMROC_ID+(buff[tmp_idx]>>4);

    p->UDP_packet_count=buff[tmp_idx]&0xf;
    p->UDP_packet_count=p->UDP_packet_count<<8;
    tmp_idx++;
    p->UDP_packet_count=p->UDP_packet_count+buff[tmp_idx];
    p->UDP_packet_count=p->UDP_packet_count<<8;
    tmp_idx++;
    p->UDP_packet_count=p->UDP_packet_count+buff[tmp_idx];
    tmp_idx++;

    if((buff[tmp_idx]>>4)!=4)
    {
        printf(" sequence_falg2 = %d, sequence_falg2!=4 ,error.\n",buff[tmp_idx]>>4);
        return -1;
    }

    p->UDP_packet_count=p->UDP_packet_count<<4;
    p->UDP_packet_count=p->UDP_packet_count+(buff[tmp_idx]&0xf);
    p->UDP_packet_count=p->UDP_packet_count<<8;
    tmp_idx++;
    p->UDP_packet_count=p->UDP_packet_count+buff[tmp_idx];
    p->UDP_packet_count=p->UDP_packet_count<<8;
    tmp_idx++;
    p->UDP_packet_count=p->UDP_packet_count+buff[tmp_idx];
    p->UDP_packet_count=p->UDP_packet_count<<8;
    tmp_idx++;
    p->UDP_packet_count=p->UDP_packet_count+buff[tmp_idx];

    if(print_enable)
    {
        printf("Header:\n");
        printf( "STATUS_BITS= %01X,  LOCAL_L1_COUNT= %u,  HIT_COUNT= %d,   Timestamp= %04X\n",
               p->STATUS_BITS,p->LOCAL_L1_COUNT,p->HIT_COUNT,p->Timestamp);
        printf("Data:\n");
        for(i=0,tmp_idx=8; i<p->HIT_COUNT; i++)
        {
            p->D_TIGER_ID=(buff[tmp_idx]>>3)&0x7;
            p->LAST_TIGER_FRAME_NUMBER=buff[tmp_idx]&0x7;
            tmp_idx++;
            p->RAW_DATA=buff[tmp_idx];
            tmp_idx++;
            p->RAW_DATA=p->RAW_DATA<<8;
            p->RAW_DATA=p->RAW_DATA+buff[tmp_idx];
            tmp_idx++;
            p->RAW_DATA=p->RAW_DATA<<8;
            p->RAW_DATA=p->RAW_DATA+buff[tmp_idx];

            tmp_idx++;
            p->RAW_DATA=p->RAW_DATA<<6;
            p->RAW_DATA=p->RAW_DATA+(buff[tmp_idx]&0x3f);
            tmp_idx++;
            p->RAW_DATA=p->RAW_DATA<<8;
            p->RAW_DATA=p->RAW_DATA+buff[tmp_idx];
            tmp_idx++;
            p->RAW_DATA=p->RAW_DATA<<8;
            p->RAW_DATA=p->RAW_DATA+buff[tmp_idx];
            tmp_idx++;
            p->RAW_DATA=p->RAW_DATA<<8;
            p->RAW_DATA=p->RAW_DATA+buff[tmp_idx];
            tmp_idx++;
            printf("D_TIGER_ID= %01X,  LAST_TIGER_FRAME_NUMBER= %01X,   RAW_DATA= %06X" ,
                   p->D_TIGER_ID,p->LAST_TIGER_FRAME_NUMBER,(p->RAW_DATA>>32)&0x3fffff);
            printf("%08X\n" ,p->RAW_DATA&0xffffffff);
        }
        printf("Tailer:\n");
        printf("LOCAL_L1_FRAMENUM=%06X, GEMROC_ID=%02d, T_TIGER_ID=%01X,  CH_ID= %02X,  LAST_COUNT_WORD_FROM_TIGER_DATA=%05X\n",
               p->LOCAL_L1_FRAMENUM,p->GEMROC_ID,p->T_TIGER_ID,p->CH_ID,p->LAST_COUNT_WORD_FROM_TIGER_DATA);
        printf("UDP Sequence Counter:\n");
        printf("S_GEMROC_ID= %02X, UDP_packet_count= %04X",p->S_GEMROC_ID,p->UDP_packet_count>>32);
        printf("%08X\n",p->UDP_packet_count&0xffffffff);
        printf("\n");
    }
    return 0;
}



/*20180928,12:36,to test git push if works*/
/*将这个程序改为：
（1）有一个结构体para，包含了所有的字段。可以对结构体成员进行加减。
（2）build_buffer函数，由结构体构造UDP数据包，字符数组，用于模拟数据发送。
（3）extract_para_from_buffer，从收到的UDP数组提取参数，放在结构体para里。
*/


int main()
{
    para PARA,tmp_para;
    unsigned int data[M];
    unsigned char buff[BUFFSIZE];
    unsigned char eventBuff[66560];
    int x,y;


    PARA.STATUS_BITS=2;     /*不变值初始化*/
    PARA.LOCAL_L1_COUNT=0;  /*递增值初始化*/
    PARA.HIT_COUNT=N;       /*不变值初始化*/
    PARA.Timestamp=0;       /*递增值初始化*/

    PARA.D_TIGER_ID=2;        /*不变值初始化*/
    PARA.LAST_TIGER_FRAME_NUMBER=0;  /*递增值初始化*/
    PARA.RAW_DATA=0;    /*递增值初始化*/

    PARA.LOCAL_L1_FRAMENUM=0;   /*递增值初始化*/
    PARA.GEMROC_ID=3;      /*不变值初始化*/
    PARA.CH_ID=8;          /*不变值初始化*/
    PARA.LAST_COUNT_WORD_FROM_TIGER_DATA=0;  /*递增值初始化*/
    PARA.UDP_packet_count=0;  /*递增值初始化*/


    int a,b,trg;
    rocBuff_init();

    for(x=0;x<100;x++)
    {
        for(y=0;y<rocNo;y++)
        {
            PARA.GEMROC_ID=y;
            change_para(&PARA,data,M,buff,BUFFSIZE);
            extract_or_print_udp_para(buff,BUFFSIZE,&tmp_para,0);
            copy_to_rocBuff(buff,BUFFSIZE,tmp_para.LOCAL_L1_COUNT,tmp_para.GEMROC_ID);
        }
        trg=tmp_para.LOCAL_L1_COUNT%eventNo;


        if(udpInfo[trg].flag==0)
        for(a=0;a<rocNo;a++)
        {
            if(rocID_enable[a]&&0)
                extract_or_print_udp_para(udpInfo[trg].rocBuff[a]+4,*(unsigned int*)udpInfo[trg].rocBuff[a],&tmp_para,1);
        }
        copy_to_sendBuff(tmp_para.LOCAL_L1_COUNT,eventBuff);
        PARA.LOCAL_L1_COUNT++;
    }

    rocBuff_delete();
    return 0;
}
