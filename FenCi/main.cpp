#include <iostream>
#include<string>
#include<set>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;
class cmp
{
public:
    bool operator()(const pair<int,int> &pr1,const pair<int,int>&pr2)
    {
        return pr1.second>pr2.second;
    }

};

/*������ȣ��ݹ�ķ���������ƽ���ͣ����ӽڵ��ֵ֪��ʱ�����ڵ�����ֵҲ��֪����*/
int f(int &strlen,int pos, vector<string>&v,   unordered_map<int,set<pair<int,int>,cmp>>&mp,
        unordered_map<int,int>&res,vector<int>&rec)
{
    if(res[pos]!=-1)
        return rec[res[pos]];
    else
    {
        int idx,sum=0;
        for(auto e:mp[pos])
        {
            if(rec[e.first]==-1) /*����е��ʵķ�����û��ã��͵ݹ����*/
            {
                if(pos+e.second==strlen)
                    rec[e.first]=e.second*e.second;
                else
                    rec[e.first]=e.second*e.second+f(strlen,pos+e.second,v,mp,res,rec);
            }
            if(rec[e.first]>sum)
            {
                sum=rec[e.first];
                idx=e.first;
            }
        }
        res[pos]=idx;
        return sum;
    }

}
int main()
{
    int n;
    string s;
 //   cin>>s>>n;
while(cin>>s>>n)
{
    vector<string>v;
    for(int i=0;i<n;i++)
    {
        string ss;
        cin>>ss;
        v.push_back(ss);
    }
    unordered_map<int,set<pair<int,int>,cmp>>mp;/*�������ִ���λ����Ϊ��ֵ���ڵ���������������õ��ʳ���*/
                                                /*��ʼλ��+���ʳ���=�¸����ʵ�λ��*/
    unordered_map<int,int>res;/*�������ʼ��ĵ��ʼ����У�ʹ�������ֵ�ĵ�������*/
    vector<int>rec(n,-1);     /*��¼����������ĵ��ʵ��������÷֣�-1��ʾ����û�б����㵽*/
    set<int> star;  /*�м�����ʼ��*/

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<s.size()-v[i].size()+1;j++)
        {  /*���v[i]ֻ��һ�����ָ��������ڲ��ָ�ĵط�Ҳ��������ִ�ʱ��Ҫ����һ��*/
            if(s.substr(j,v[i].size())==v[i])
            {
                mp[j].insert(pair<int,int>(i,v[i].size()));
                res[j]=-1; /*����ֵ�ȸ�Ϊ-1��˵����û����������ʼ������ֵ*/
                if(star.find(j)==star.end())
                    star.insert(j);
            }
        }
    }

    cout<<"check map:"<<endl;
    for(auto p:star)
    {
        cout<<"��ʼ��= "<<p<<" �ĵ��ʣ�"<<endl;
        for(auto pr:mp[p])
            cout<<"    "<<v[pr.first]<<" , len="<<pr.second<<endl;
    }
    int strlen=s.size();
    int sum;
    sum=f(strlen,0,v,mp,res,rec);
    cout<<"sum= "<<sum<<endl;
    for(int i=0;mp.find(i)!=mp.end();i=i+v[res[i]].size())
    {
        cout<<v[res[i]]<<' ';

    }
    cout<<endl;

}









    return 0;
}
