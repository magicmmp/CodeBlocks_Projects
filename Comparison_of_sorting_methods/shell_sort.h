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
    for(int div=len/2;div>=1;div=div/2)//定增量div，并不断减小
    {
      for(int i=0;i<=div;++i)//分组成div组
      {
        for(int j=i;j<len-div;j+=div)//对每组进行插入排序
          for(int k=j;k<len;k+=div)
            if(data[j]>data[k])
              swapInt(data+j,data+k);//交换两个数的值
      }
    }
}


#endif // SHELL_SORT_H_INCLUDED
