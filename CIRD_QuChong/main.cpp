#include <iostream>
#include <vector>
#include <algorithm> //to use sort()
#include <cstdlib>   //to use atoi()
using namespace std;
struct ADDR
{
    int Min;
    int Max;
};

void IntAddr(const string& s,struct ADDR& addr)
{
    int p1,p2;
    int n,val;
    string sb;
    val=0;
    p1=0;
    p2=0;
    while(s[p2]!='.')
        p2++;
    sb=s.substr(p1,p2-p1);
    n=atoi(sb.c_str());
    val=val|n<<24;

    p1=p2+1;
    p2=p1;
    while(s[p2]!='.')
        p2++;
    sb=s.substr(p1,p2-p1);
    n=atoi(sb.c_str());
    val=val|n<<16;

    p1=p2+1;
    p2=p1;
    while(s[p2]!='.')
        p2++;
    sb=s.substr(p1,p2-p1);
    n=atoi(sb.c_str());
    val=val|n<<8;

    p1=p2+1;
    p2=p1;
    while(s[p2]!='/')
        p2++;
    sb=s.substr(p1,p2-p1);
    n=atoi(sb.c_str());
    val=val|n;
    addr.Min=val;

    sb=s.substr(p2+1);
    n=atoi(sb.c_str());
    n=0xffffffff>>n;
    addr.Max=val+n;
}
int main()
{
    int k;
    vector<string> v;
    vector<string> res;
    cin>>k;
    vector<bool> idx(k,true);//标记那些要被去除的元素下标，true保留，false去除。
    struct ADDR ad;
    vector<struct ADDR> addr(k,ad); //存放每个网址用整数表示时的范围
    for(int i=0;i<k;i++)
    {
        string s;
        cin>>s;
        v.push_back(s);
    }
    for(int i=0;i<v.size();i++)
        IntAddr(v[i],addr[i]);

    for(int i=0;i<v.size();i++)
    {
       if(!idx[i])
            continue;
       for(int j=0;j<v.size();j++)
      {
        if(!idx[j] || i==j)
            continue;
        if(addr[i].Min<=addr[j].Min && addr[i].Max>=addr[j].Max)
            idx[j]=false;
      }
    }
    for(int i=0;i<v.size();i++)
    if(idx[i])
        res.push_back(v[i]);
    cout<<res.size()<<endl;
    for(auto e:res)
        cout<<e<<endl;
    return 0;
}
