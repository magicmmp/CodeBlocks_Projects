#include <iostream>

using namespace std;

int main()
{
    int N;
    cout<<"Please input Yuan:"<<endl;
    int num5,num10,num20,num50,num100;
while(cin>>N)
{
    unsigned int res=0;
    num100=N/100;
    int K;
    K=N;
    for(int a=0,k100=K;a<=num100;a++)
    {
        K=k100-a*100;
        if(K<0)
        {
            a=N;
            continue;
        }
        if(K==0)
        {
            res++;
            cout<<"res= "<<res<<" ,num100= "<<a<<endl;
            a=N;
            continue;
        }
        num50=K/50;
        for(int b=0,k50=K;b<=num50;b++)
        {
            K=k50-b*50;
            if(K<0)
            {
                b=N;
                continue;
            }
            if(K==0)
            {
                b=N;
                res=res+1;
                cout<<"res= "<<res<<" ,num100= "<<a<<", num50= "<<b<<endl;
                continue;
            }
            num20=K/20;
            for(int c=0,k20=K;c<=num20;c++)
            {
                K=k20-c*20;
                if(K<0)
                {
                    c=N;
                    continue;
                }
                if(K==0)
                {
                    c=N;
                    res++;
                    cout<<"res= "<<res<<" ,num100= "<<a<<", num50= "<<b<<",num20= "<<c<<endl;
                    continue;
                }
                num10=K/10;
                for(int d=0,k10=K;d<=num10;d++)
                {
                    K=k10-d*10;
                    if(K<0)
                    {
                        d=N;
                        continue;
                    }
                    if(K==0)
                    {
                        res++;
                        cout<<"res= "<<res<<" ,num100= "<<a<<", num50= "<<b<<",num20= "<<c<<",num10="<<d<<endl;
                        d=N;
                        continue;
                    }
                    num5=K/5;
                    for(int e=0,k5=K;e<=num5;e++)
                    {
                        K=k5-e*5;
                        if(K<0)
                        {
                            e=N;
                            continue;
                        }
                        else if(K==0)
                        {
                            res++;
            cout<<"res= "<<res<<" ,num100= "<<a<<", num50= "<<b<<",num20= "<<c<<",num10= "<<d<<",num5= "<<e<<endl;
                            e=N;
                            continue;
                        }
                        else
                        {
                            res++;
    cout<<"res= "<<res<<" ,num100= "<<a<<", num50= "<<b<<",num20= "<<c<<",num10= "<<d<<",num5= "<<e<<"num1="<<K<<endl;
                        }
                    }
                }
            }
         }
    }

    cout<<"N= "<<N<<",  result= "<<res<<endl;
}
    return 0;
}
