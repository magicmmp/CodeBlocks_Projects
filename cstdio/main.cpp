#include <iostream>
#include <cstdio>
#include<iomanip>
#include <errno.h>
#include <string.h>
#include <math.h>
using namespace std;
/*
char buff[48];
struct DAQ_para*DAQ,
struct g_reg_para* g_reg,
struct ch_reg_para* ch_reg,
struct gemroc_para* gemroc,

struct DAQ
{
    int buff[5];
};
*/
int main()
{
    int tmp = 0;
    for(tmp = 0; tmp <=256; tmp++)
    {
        printf("errno: %2d\t%s\n",tmp,strerror(tmp));
    }
    char *str="abcd";
    char bf[]="abcd";
    printf("%d,%d,%d\n",sizeof(str),sizeof(bf),sizeof("abcd"));
    double y;
    for(tmp=40;tmp<70;tmp+=5)
    {

        printf("Õñ·ù1=%d Õñ·ù2 = %d\n",tmp,sqrt(tmp));
    }


    return 0;
}
