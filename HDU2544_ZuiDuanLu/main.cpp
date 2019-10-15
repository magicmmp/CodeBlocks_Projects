#include <iostream>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include<stack>

using namespace std;

struct Node
{
    int id;   /*��ǰ��ID*/
    int dmin; /*��ĿǰΪֹ���� 1 �� �� ID ����С����*/
    int pre;  /*ʹ������Сֵ��ǰһ����*/
    Node(int a=-1,int b=INT_MAX,int c=-1):id(a),dmin(b),pre(c){}
};
/*Ϊ���ȶ����Զ���ȽϺ���*/
struct cmp
{
    /*���� > �õ�����С���� */
    bool operator()(const Node &a,const Node &b) const
    {
        return a.dmin > b.dmin;
    }
};

/* ���㷨�����Դ��S��ͼ�������е�����·������·�����ȵ���������������
   ������Ϊ��S������ľ���Ϊ0�����Ե�һ�����Ϊ��S������Сֵ����S�����ĵ��еó���
   �����Ľ������Ҫ���ݾ���ֵ����
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
            visited[e.id]=true;   /*�� e.id �������С����*/
            dist[e.id]=e.dmin;
            path[e.id]=e.pre;
            for(int j=0;j<d.size();j++)
            {
                if(d[e.id][j]!=INT_MAX && !visited[j])
                {
                    if(dist[j]>dist[e.id]+d[e.id][j])   /*����� e.id ���ڵĵ���м��*/
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
        cout<<"�� 1 �� "<<i+1<<"  ����С�����ǣ�"<<dist[i]<<endl;
    }
    cout<<endl;
    return dist[d.size()-1];
}
/*
�������ݲ���
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
/*��ͨ������*/
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
            cout<<"��̾����ǣ� "<<res<<endl;
        }
    }



    return 0;
}
