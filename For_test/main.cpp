#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct node
{
    unsigned int beg;
    unsigned int ed;
};

bool cmp(const node &n1,const node  &n2)
{
    return n1.beg<n2.beg;
}
/*
6
1 2
1 3
2 3
2 6
3 5
8 9
*/

int main()
{
  //  sort(v.begin(),v.end(),cmp);
    int N;
    cin>>N;
    vector<node>v(N);
    vector<bool>flag(N,true);
    for(int i=0;i<N;i++)
        cin>>v[i].beg>>v[i].ed;
    sort(v.begin(),v.end(),cmp);
    int i,j;
    i=0;
    j=1;
    while(j<N)
    {
       if(v[i].ed<v[j].beg)
       {
           i=j;j++;
       }
       else if(v[i].ed>=v[j].ed)
       {
           v[j].ed=v[i].ed;
           flag[j]=false;
           j++;
       }
       else
       {
          v[j].beg=v[i].beg;
          flag[i]=false;
          i=j;j++;
       }
    }
    cout<<"The result:"<<endl;
    for(int i=0;i<N;i++)
    {
        if(flag[i])
            cout<<v[i].beg<<' '<<v[i].ed<<endl;
    }




    return 0;
}
