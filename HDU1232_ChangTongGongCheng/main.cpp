#include <iostream>
#include<vector>
using namespace std;
/*并查集，找出城镇节点node属于哪个连通分量*/
int findroot(vector<int>&v,int node)
{
    int root;
    root=node;
    while(root !=v[root] )
        root=v[root];
    while(node!=v[node]) /*这些节点直接改为属于root*/
    {
        int tmp=v[node];
        v[node]=root;
        node=tmp;
    }
    return root;
}
/**
测试数据输入：
4 2
1 3
4 3
3 3
1 2
1 3
2 3
5 2
1 2
3 5
999 0
0

**/
int main()
{
    int N,M;
    bool flag=true;
    while(flag)
    {
        cin>>N;
        if(N)
        {
            cin>>M;
            vector<int>v(N+1,0);
            for(int i=1;i<=N;i++)
                v[i]=i;
            int RoadNum=N-1;  /*一开始要修的总道路数*/
            while(M)
            {
                int x,y;
                cin>>x>>y; /*现在添加一条路，连接城镇x,y*/
                int root1=findroot(v,x);
                int root2=findroot(v,y);
                if(root1 != root2)  /*如果节点x,y属于不同的连通分量，则这条路会使当前连通分量数目减1*/
                {
                    v[root1]=root2;
                    RoadNum--;
                }
                M--;
            }
            cout<<"还要修 "<<RoadNum<<" 条路"<<endl;
         //   cout<<RoadNum<<endl;
        }
        else
            flag=false;
    }



    return 0;
}
