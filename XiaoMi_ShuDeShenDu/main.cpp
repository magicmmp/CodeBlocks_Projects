#include <iostream>
#include<set>
#include<map>
using namespace std;
int depth( map<int,set<int>>&mp,int i)
{
    if(mp.find(i)==mp.end())/*说明i是叶子节点*/
        return 1;
    int dep=0;
    for(auto e:mp[i])
    {
        int tmp=depth(mp,e);
        if(dep<tmp)
            dep=tmp;
    }
    return 1+dep;
}


int main()
{
    int n;
    map<int,set<int>>mp;
    cin>>n;
    set<int>head;
    for(int i=0;i<n;i++)
        head.insert(i);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        cin>>u>>v;
        if(head.find(v)!=head.end())
            head.erase(v);
        mp[u].insert(v);
    }
    auto p=head.begin();
    cout<<depth(mp,*p)<<endl;

    return 0;
}
