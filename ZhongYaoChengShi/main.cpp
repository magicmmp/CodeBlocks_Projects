#include <iostream>
#include<vector>
#include<set>
#include<unordered_map>
#include<queue>
using namespace std;
/*非递归版广度优先遍历，从k点出发能达到几个城市*/
void bfs(const int &k, unordered_map<int,set<int>>&mp, vector<set<int>>&chu)
{
    queue<int>q;
    q.push(k);
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        chu[k].insert(tmp);
        for(auto e:mp[tmp])
        {
            if(chu[k].find(e)==chu[k].end())
                q.push(e);
        }
    }
    chu[k].erase(k);
    cout<<endl;
}


/*
测试数据输入：
5 5
0 2
1 2
1 3
3 0
3 4
*/

int main()
{
    int n,m;
    cin>>n>>m;/*城市编号从0开始。*/
    unordered_map<int,set<int>>mp;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        mp[u].insert(v);
    }
    set<int>s0;
    vector<set<int>>chu(n,s0);/*从i点出发可以到达多少个城市*/
    vector<set<int>>ru(n,s0);/*有多少个城市可以到达点i*/
    for(int i=0;i<n;i++)
    {
        if(mp[i].empty())
            continue;
        bfs(i,mp,chu);
    }
    for(int i=0;i<n;i++)
    {
        if(chu[i].empty())
            continue;
        for(auto e:chu[i])
            if(ru[e].find(i)==ru[e].end())
                ru[e].insert(i);
    }
    for(int i=0;i<n;i++)
    {
        cout<<"从  "<<i<<"  出发可以到达  "<<chu[i].size()<<"  个城市："<<endl;
        for(auto e:chu[i])
            cout<<' '<<e;
        cout<<endl;

        cout<<"从其他  "<<ru[i].size()<<"  个城市 "<<"可以达到  "<<i<<"  :"<<endl;
        for(auto e:ru[i])
            cout<<' '<<e;
        cout<<endl;
        cout<<endl;
    }
    int num=0;
    for(int i=0;i<n;i++)
    if(ru[i].size()>chu[i].size())
    {
            num++;
            s0.insert(i);
    }
    cout<<"重要城市有 "<<s0.size()<<" 个，它们是："<<endl;
    for(auto e:s0)
        cout<<' '<<e;
    cout<<endl;

    return 0;
}
