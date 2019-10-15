#include <iostream>
#include<vector>
using namespace std;
/**用Floyd算法更新任意两点之间的距离**/
void floyd(vector<vector<int> >&d)
{
    int n=d.size();
    for(int k=0;k<n;k++)
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
        if(d[i][j]>d[i][k]+d[k][j])
            d[i][j]=d[i][k]+d[k][j];
}
/**
Sample Input

3
2 2 4 3 5
2 1 2 3 6
2 1 2 2 2
5
3 4 4 2 8 5 3
1 5 8
4 1 6 4 10 2 7 5 2
0
2 2 5 1 5
0
Sample Output

3 2
3 10
**/

int main()
{
    int n;
    bool flag=true;
    while(flag)
    {
        cin>>n;
        if(!n)
            flag=false;
        else
        {
            vector<vector<int> >d(n,vector<int>(n,10000000));
            for(int i=0;i<n;i++)
                d[i][i]=0;
            for(int i=0;i<n;i++)
            {
                int m;
                cin>>m;
                for(int j=0;j<m;j++)
                {
                    int x,t;
                    cin>>x>>t;
                    x--;
                    d[i][x]=t;
                }
            }
            floyd(d);
            int num,tmin=10000000;
            for(int i=0;i<n;i++)
            {
                int tmax=0;
                for(int j=0;j<n;j++)
                    if(d[i][j]>tmax)
                        tmax=d[i][j];
                if(tmax<tmin)
                {
                    tmin=tmax;
                    num=i+1;
                }
            }
            cout<<"结果："<<endl;
            if(tmin<10000000)
                cout<<num<<' '<<tmin<<endl;
            else
                cout<<"disjoint"<<endl;
            cout<<endl;
        }
    }



    return 0;
}
