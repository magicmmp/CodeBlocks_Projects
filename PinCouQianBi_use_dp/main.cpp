#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int>v(6,1);
    v[1]=5;
    v[2]=10;
    v[3]=20;
    v[4]=50;
    v[5]=100;
    int n;
    cin>>n;
    vector<vector<long>> rec(6,vector<long>(n+1,0));
    for(int i=0;i<n+1;i++)
        rec[0][i]=1;
    for(int i=1;i<6;i++)
        rec[i][0]=1;
    for(int i=1;i<6;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int k=j/v[i];k>=0;k--)
                rec[i][j]=rec[i][j]+rec[i-1][j-k*v[i]];
        }

    }

    for(int i=0;i<6;i++)
    {
        for(int j=0;j<=n;j++)
            cout<<rec[i][j]<<"  ";
        cout<<endl;
    }

     cout<<rec[5][n];



    return 0;
}
