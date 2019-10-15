#include <iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<unordered_map>
#include<set>
#include<unordered_set>

using namespace std;
int f(string s)
{
    int res=0; /*结果应该用long,否则可能数值溢出*/
    int k;
    int i,j;
    i=0;
    while(i<s.size() && s[i]!='#')
        i++;
    string sk=s.substr(0,i); /*K进制*/
    k=atoi(sk.c_str());
    string sn=s.substr(i+1); /*K进制的数值部分*/
    int tmp=1;
    for(j=sn.size()-1;j>=0;j--)
    {
        res=res+(sn[j]-'0')*tmp;
        tmp=tmp*k;
    }
    return res;
}


int main()
{
    string s;
    vector<string>v;
    while(1)
    {
        cin>>s;
        if(s=="END")
            break;
        else
            v.push_back(s);
    }
    unordered_map<int,unordered_set<int>>mp;
    set<int>re;
    for(int i=0;i<v.size();i++)
    {
        int n=f(v[i]);
        mp[n].insert(i);
    }
    for(auto it=mp.begin();it!=mp.end();it++)
    {
        if((it->second).size()==1)
        {
            auto p=(it->second).begin();
            re.insert(*p);
        }
    }
    if(re.size()==0)
        cout<<"None"<<endl;
    else
        for(auto e:re)
            cout<<v[e]<<endl;


    return 0;
}
