#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int n,k,t;
    cin>>n>>k>>t;
    vector<int>v(n,0);
    for(int i=0;i<n;i++)
        cin>>v[i];
    int res=0;
    map<int,int>mp;
    for(int i=0;i<v.size()-k+1;i++)
    {
        if(i==0)
        for(int j=i;j<i+k;j++)
            mp[v[j]]++;
        else
            mp[v[i+k-1]]++;
        for(int j=i;j<i+k;j++)
        if(mp[v[j]]>=t)
        {
           res++;
           break;
        }
        mp[v[i]]--;
    }
    cout<<res;
    return 0;
}
