#include <iostream>
#include <vector>
#include <string>
using namespace std;
string BigIntMultiply(string &lf,string &rh)
{
    int llen=lf.size();
    int rlen=rh.size();
    vector<int> v(llen+rlen-1,0);
    for(int i=0;i<llen;i++)
    {
        int lint=lf[i]-'0';
        for(int j=0;j<rlen;j++)
        {
            int rint=rh[j]-'0';
            v[i+j]=v[i+j]+rint*lint;
        }
    }
    for(int i=v.size()-1;i>0;i--)
    {
        int tmp=v[i]/10;
        v[i]=v[i]%10;
        v[i-1]=v[i-1]+tmp;
    }
    if(v[0]>10)
    {
        int tmp=v[0]/10;
        v[0]=v[0]%10;
        v.insert(v.begin(),tmp);
    }
    string res;
    for(unsigned int i=0;i<v.size();i++)
        res.push_back((char)(v[i])+'0');
    return res;
}

int main()
{
    string R;
    int n;
    cout<<"please input R ,n:"<<endl;
    cin>>R>>n;
    for(int i=R.size()-1;i>0 && (R[i]=='0'||R[i]=='.');i--)
        R.erase(i);
    int dotpos=-1;
    int dotnum;
    for(int i=0;i<R.size()-1;i++)
        if(R[i]=='.')
            dotpos=i;
    if(dotpos!=-1)
    {
       dotnum=R.size()-1-dotpos;
       dotnum=dotnum*n;
    }
    else
        dotnum=0;
    if(dotnum>0)
    {
        R.erase(dotpos,1);
        while(R[0]=='0')
            R.erase(0,1);
    }

    string res=R;
    for(int i=0;i<n-1;i++)
        res=BigIntMultiply(res,R);
    cout<<res<<endl;
    if(res.size()<dotnum)
        res.insert(0,dotnum-res.size()+1,'0');
    if(dotnum>0)
    {
        res.insert(res.size()-dotnum,1,'.');
        int i=res.size()-1;
    }
    cout<<"R^n="<<res<<endl;



    return 0;
}
