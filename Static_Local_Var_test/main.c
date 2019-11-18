#include <stdio.h>
#include <stdlib.h>

void test()
{
    static int var=0;//测试初始化表达式是否置执行一次
    printf("static变量值= %d\n",var);
    var++;
}

int main()
{
    int i;
    for(i=0;i<5;i++)
        test();

    return 0;
}
