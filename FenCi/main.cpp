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

/*深度优先，递归的方法获得最大平方和，当子节点的值知道时，父节点的最大值也就知道了*/
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
            if(rec[e.first]==-1) /*如果有单词的分数还没算好，就递归计算*/
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
    unordered_map<int,set<pair<int,int>,cmp>>mp;/*单词在字串的位置作为键值；在单词数组的索引；该单词长度*/
                                                /*起始位置+单词长度=下个单词的位置*/
    unordered_map<int,int>res;/*从这个起始点的单词集合中；使其获得最大值的单词索引*/
    vector<int>rec(n,-1);     /*记录从这个索引的单词到最后的最大得分，-1表示单词没有被计算到*/
    set<int> star;  /*有几个起始点*/

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<s.size()-v[i].size()+1;j++)
        {  /*如果v[i]只在一处被分割，但是语句在不分割的地方也出现这个字串时，要考虑一下*/
            if(s.substr(j,v[i].size())==v[i])
            {
                mp[j].insert(pair<int,int>(i,v[i].size()));
                res[j]=-1; /*索引值先赋为-1，说明还没有算好这个起始点的最大值*/
                if(star.find(j)==star.end())
                    star.insert(j);
            }
        }
    }

    cout<<"check map:"<<endl;
    for(auto p:star)
    {
        cout<<"起始点= "<<p<<" 的单词："<<endl;
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
