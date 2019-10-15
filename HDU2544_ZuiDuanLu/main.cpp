#include <iostream>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include<stack>

using namespace std;

struct Node
{
    int id;   /*当前点ID*/
    int dmin; /*到目前为止，点 1 到 点 ID 的最小距离*/
    int pre;  /*使其获得最小值的前一个点*/
    Node(int a=-1,int b=INT_MAX,int c=-1):id(a),dmin(b),pre(c){}
};
/*为优先队列自定义比较函数*/
struct cmp
{
    /*定义 > 得到的是小顶堆 */
    bool operator()(const Node &a,const Node &b) const
    {
        return a.dmin > b.dmin;
    }
};

/* 该算法求出单源点S到图其余所有点的最短路径。按路径长度递增次序产生结果。
   可以认为，S到自身的距离为0，所以第一个结果为点S，而次小值在与S相连的点中得出。
   其他的结果则需要依据距离值排序。
 */

int dijkstra(vector<vector<int>>&d)
{
    priority_queue<Node,vector<Node>,cmp>q;
    vector<int>dist(d.size(),INT_MAX);
    dist[0]=0;
    vector<int>path(d.size(),-1);
    vector<bool>visited(d.size(),false);
    Node node(0,0,-1);
    q.push(node);
    while(!q.empty())
    {
        auto e=q.top();
        q.pop();
        if(!visited[e.id])
        {
            visited[e.id]=true;   /*点 e.id 求出了最小距离*/
            dist[e.id]=e.dmin;
            path[e.id]=e.pre;
            for(int j=0;j<d.size();j++)
            {
                if(d[e.id][j]!=INT_MAX && !visited[j])
                {
                    if(dist[j]>dist[e.id]+d[e.id][j])   /*对与点 e.id 相邻的点进行检查*/
                    {
                        dist[j]=dist[e.id]+d[e.id][j];
                        Node nd(j,dist[j],e.id);
                        q.push(nd);
                    }
                }
            }

        }

    }
    for(int i=0;i<dist.size();i++)
    {
        cout<<"从 1 到 "<<i+1<<"  的最小距离是："<<dist[i]<<endl;
    }
    cout<<endl;
    return dist[d.size()-1];
}
/*
输入数据测试
5 9
1 2 2
1 4 8
2 4 5
2 3 8
3 4 7
3 5 2
4 5 6
1 5 100
1 3 1
*/
/*已通过测试*/
int main()
{
    int N,M;
    bool flag=true;

    while(flag)
    {
        cin>>N>>M;
        if(!N || !M)
            flag=false;
        else
        {
            vector<vector<int>>d(N,vector<int>(N,INT_MAX));
            int x,y,c;
            for(int i=0;i<M;i++)
            {
                cin>>x>>y>>c;
                x--;
                y--;
                d[x][y]=c;
                d[y][x]=c;
            }
            int res=dijkstra(d);
            cout<<"最短距离是： "<<res<<endl;
        }
    }



    return 0;
}
