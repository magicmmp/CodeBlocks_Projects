#ifndef SHELL_SORT_H_INCLUDED
#define SHELL_SORT_H_INCLUDED
void swapInt(int * a,int*b)
{
    int c=*a;
    *a=*b;
    *b=c;
}
void shell(int*data,int len)
{
    if(len<=1||data==NULL)
      return;
    for(int div=len/2;div>=1;div=div/2)//������div�������ϼ�С
    {
      for(int i=0;i<=div;++i)//�����div��
      {
        for(int j=i;j<len-div;j+=div)//��ÿ����в�������
          for(int k=j;k<len;k+=div)
            if(data[j]>data[k])
              swapInt(data+j,data+k);//������������ֵ
      }
    }
}


#endif // SHELL_SORT_H_INCLUDED
