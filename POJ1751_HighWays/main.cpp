#include <iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<set>
using namespace std;

struct edge
{
    int nd1;
    int nd2;
    int len;
    edge(int a=-1,int b=-1,int c=-1):nd1(a),nd2(b),len(c){}
};

struct cmp
{

    bool operator()(const edge &a,const edge &b) const
    {
        return a.len > b.len;
    }
};

set<int> bfs(int node,vector<vector<bool> >&mp)
{
    set<int>res;
    queue<int>q;
    q.push(node);
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        if(res.find(tmp)==res.end())
            res.insert(tmp);
        for(int j=0;j<mp.size();j++)
        {
            if(mp[tmp][j] && res.find(j)==res.end())
                q.push(j);
        }
    }
    return res;
}
/*超时，需要寻找更好的算法
**使用prim算法。
HDU支持C++11,
但是POJ不支持c++11，尽量不用auto,unordered_set之类的。
测试数据输入：
9
1 5
0 0
3 2
4 5
5 1
0 4
5 2
1 2
5 3
3
1 3
9 7
1 2
样例输出
1 6
3 7
4 9
5 7
8 3
*/
int main()
{
    int N;
    cin>>N;
    vector<vector<int> >pos;
    for(int i=0;i<N;i++)
    {
        int x,y;
        vector<int>tmp(2);
        cin>>x>>y;
        tmp[0]=x;
        tmp[1]=y;
        pos.push_back(tmp);
    }
    int M;
    cin>>M;
    vector<vector<bool> >mp(N,vector<bool>(N,false));
    for(int i=0;i<M;i++)
    {
        int a,b;
        cin>>a>>b;
        a--;b--;
        mp[a][b]=true;
        mp[b][a]=true;
    }
    vector<bool>visited(N,false);
    priority_queue<edge,vector<edge>,cmp>eq;
    set<int> st=bfs(0,mp);
    for(set<int>::iterator e=st.begin();e!=st.end();e++)
        visited[*e]=true;
    for(set<int>::iterator e=st.begin();e!=st.end();e++)
    {
        for(int j=0;j<N;j++)
        if(!visited[j])
        {
            int dx=pos[*e][0]-pos[j][0];
            int dy=pos[*e][1]-pos[j][1];
            int d=dx*dx+dy*dy;
            edge eg(*e,j,d);
            eq.push(eg);
        }
    }
    st.clear();
    vector<edge>res;
    while(!eq.empty())
    {
        edge eg=eq.top();
        eq.pop();
        int node=-1;
        if(visited[eg.nd1] && !visited[eg.nd2])
            node=eg.nd2;
        if(!visited[eg.nd1] && visited[eg.nd2])
            node=eg.nd1;
        if(node!=-1)
        {
            res.push_back(eg);
            set<int> stt=bfs(node,mp);
            for(set<int>::iterator e=stt.begin();e!=stt.end();e++)
            {
                for(int j=0;j<N;j++)
                {
                    if(visited[j] || stt.find(j)!=stt.end())
                        continue;
                    int dx=pos[*e][0]-pos[j][0];
                    int dy=pos[*e][1]-pos[j][1];
                    int d=dx*dx+dy*dy;
                    edge eg(*e,j,d);
                    eq.push(eg);
                }
            }
            mp[eg.nd1][eg.nd2]=true;
            mp[eg.nd2][eg.nd1]=true;
            for(set<int>::iterator e=stt.begin();e!=stt.end();e++)
                visited[*e]=true;
        }
    }
    cout<<"The roads need to build:"<<endl;
    for(int i=0;i<res.size();i++)
        cout<<res[i].nd1+1<<' '<<res[i].nd2+1<<endl;

    return 0;
}
