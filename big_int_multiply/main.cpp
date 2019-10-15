#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string lf,rh;
    cout<<"please input :"<<endl;
    cin>>lf>>rh;
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
    for(int i=0;i<v.size();i++)
        res.push_back((char)(v[i])+'0');
    cout<<lf<<"*"<<rh<<"="<<res<<endl;

    return 0;
}
