#include <stdio.h>
#include <stdlib.h>

void test()
{
    static int var=0;//���Գ�ʼ�����ʽ�Ƿ���ִ��һ��
    printf("static����ֵ= %d\n",var);
    var++;
}

int main()
{
    int i;
    for(i=0;i<5;i++)
        test();

    return 0;
}
