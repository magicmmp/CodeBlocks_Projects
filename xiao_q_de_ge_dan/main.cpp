#include <iostream>

using namespace std;
int f(int n,int m)
{
    if(n<=0 || n<m)
        return 0;
    if(m==0 || m==n)
        return 1;
    int N=1;
    int M=1;
    for(int i=n;i>n-m;i--)
        N=N*i; /*很可能溢出了*/
    for(int i=m;i>1;i--)
        M=M*i;
    return N/M;

}


int main()
{
    int K;
    int alen,anum,blen,bnum;
    cout<<"Please input:"<<endl;
    cin>>K;
    cin>>alen>>anum>>blen>>bnum;
    int anum_max=K/alen;
    int result=0;

    for(int i=0;i<=anum_max&&i<=anum;i++)
    {
        int j=K-i*alen;
        if(j%blen)
            continue;
        else
        {
            j=j/blen;
            if(j<=bnum)
            result=result+f(anum,i)*f(bnum,j);
        }
    }
/*
    for(int i=0;i<15;i++)
        cout<<"C("<<10<<","<<i<<")="<<f(10,i)<<endl;
*/
    cout<<"The result:"<<endl;
    cout<<result<<endl;

}
