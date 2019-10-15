#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*支持有符号的大数相乘*/
string Multiply(string num1, string num2)
{
        if(num1=="0"||num2=="0")
            return "0";
        int f1,f2;  /*标记乘数的正负，正数为1，负数为-1*/
        f1=1;
        f2=1;
        if(num1[0]=='-')
        {
            f1=-1;
            num1=num1.substr(1);
        }
        else if(num1[0]=='+')
        {
            num1=num1.substr(1);
        }

        if(num2[0]=='-')
        {
            f2=-1;
            num2=num2.substr(1);
        }
        else if(num2[0]=='+')
        {
            num2=num2.substr(1);
        }

        int len1=num1.size();
        int len2=num2.size();
        vector<int> v(len1+len2-1,0);
        for(int i=0;i<len1;i++)
        {
            int Lint=num1[i]-'0';
            for(int j=0;j<len2;j++)
            {
                int Rint=num2[j]-'0';
                v[i+j]=v[i+j]+Lint*Rint;
            }
        }
        for(int i=v.size()-1;i>0;i--)
        {
            v[i-1]=v[i-1]+v[i]/10;
            v[i]=v[i]%10;
        }
        if(v[0]>9)
        {
            int tmp=v[0]/10;
            v[0]=v[0]%10;
            v.insert(v.begin(),tmp);
        }
        string res;
        for(int i=0;i<v.size();i++)
            res.push_back((char)v[i]+'0');
        if(f1*f2<0) /*如果乘数一正一负，则结果为负值*/
            res.insert(res.begin(),'-');
        return res;
}


int main()
{
    string lf,rh;
    while(1)
    {
        cout<<"please input :"<<endl;
        cin>>lf>>rh;
        string res=Multiply(lf,rh);
        cout<<lf<<"*"<<rh<<"="<<res<<endl;
        cout<<endl;
    }


    return 0;
}
