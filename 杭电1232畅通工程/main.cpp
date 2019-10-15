#include <iostream>
#include<vector>

using namespace std;

int FindRoot(vector<int>v,int node)
{
    int root=node;
    while(v[root]!=root)
        root=v[root];
    while(v[node]!=root)
    {
        int tmpPre=v[node];
        v[node]=root;
        node=tmpPre;
    }
    return root;
}





int main()
{
    int N,M;
    bool flag=true;
    while(flag)
    {
        cin>>N;
        if(N>0)
        {
            vector<int>v(N+1);
            for(int i=1;i<=N;i++)
                v[i]=i;
            cin>>M;
            int RoadNum=N-1;
            while(M>0)
            {
                int x,y;
                cin>>x>>y;
                int xRoot=FindRoot(v,x);
                int yRoot=FindRoot(v,y);
                if(xRoot!=yRoot)
                {
                    v[xRoot]=yRoot;
                    RoadNum--;
                }
                M--;
            }
            cout<<RoadNum<<endl;
        }
        else
            flag=false;
    }




    return 0;
}
