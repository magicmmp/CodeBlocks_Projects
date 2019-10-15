#include <iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
bool cmp(const pair<int,int>&p1,const pair<int,int>&p2)
{
    return p1.first<p2.first;
}

int main()
{
    int n;
    cout<<"�������������Ŀ n �͸�������:"<<endl;
    cin>>n;
    vector<pair<int,int>>p;
    stack<pair<int,int>>res;
    for(int i=0;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        p.push_back(pair<int,int>(x,y));
    }
    sort(p.begin(),p.end(),cmp);
    int Ymax=p[n-1].second;
    res.push(p[n-1]);
    for(int i=n-2;i>=0;i--)
    {
        if(p[i].second>=Ymax)
        {
            Ymax=p[i].second;
            res.push(p[i]);
        }
    }
    cout<<"�������Ϸ�û��������ĵ㼯����:"<<endl;
    while(!res.empty())
    {
        cout<<res.top().first<<' '<<res.top().second<<endl;
        res.pop();
    }


    return 0;
}
