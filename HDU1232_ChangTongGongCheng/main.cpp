#include <iostream>
#include<vector>
using namespace std;
/*���鼯���ҳ�����ڵ�node�����ĸ���ͨ����*/
int findroot(vector<int>&v,int node)
{
    int root;
    root=node;
    while(root !=v[root] )
        root=v[root];
    while(node!=v[node]) /*��Щ�ڵ�ֱ�Ӹ�Ϊ����root*/
    {
        int tmp=v[node];
        v[node]=root;
        node=tmp;
    }
    return root;
}
/**
�����������룺
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
            int RoadNum=N-1;  /*һ��ʼҪ�޵��ܵ�·��*/
            while(M)
            {
                int x,y;
                cin>>x>>y; /*�������һ��·�����ӳ���x,y*/
                int root1=findroot(v,x);
                int root2=findroot(v,y);
                if(root1 != root2)  /*����ڵ�x,y���ڲ�ͬ����ͨ������������·��ʹ��ǰ��ͨ������Ŀ��1*/
                {
                    v[root1]=root2;
                    RoadNum--;
                }
                M--;
            }
            cout<<"��Ҫ�� "<<RoadNum<<" ��·"<<endl;
         //   cout<<RoadNum<<endl;
        }
        else
            flag=false;
    }



    return 0;
}
