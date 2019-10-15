#include <stdio.h>
#include <stdlib.h>
typedef struct {
    /*Header*/
    unsigned int STATUS_BITS;/*is 0*/
    unsigned int LOCAL_L1_COUNT; /*Increment by 1*/
    unsigned int HIT_COUNT;
    unsigned int Timestamp;
    /*data*/
    unsigned int TIGER_ID;
    unsigned int LAST_TIGER_FRAME_NUMBER;
    long RAW_DATA;
    /*Tailer*/
    unsigned int LOCAL_L1_FRAMENUM;
    unsigned int GEMROC_ID;
    unsigned int CH_ID;
    unsigned int LAST_COUNT_WORD_FROM_TIGER_DATA;
    /*UDP Sequence Counter*/
    long UDP_packet_count;
}para;
void f(para* p)
{
    printf("p->TIGER_ID= %d\n",p->TIGER_ID);
}


int main()
{
    para Pa;
    para* p;
    p=&Pa;
    p->TIGER_ID=2;
    f(p);
    return 0;
}
