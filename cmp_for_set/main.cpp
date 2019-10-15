#include <iostream>
#include <set>
#include<map>
#include<algorithm>
#include<vector>
using namespace std;

bool vec_cmp(const vector<int> &v1,const vector<int> &v2)
{
    return v1[0]>v2[0];
}
class cmp
{
public:
    bool operator()(const pair<int,int> &pr1,const pair<int,int>&pr2)
    {
        return pr1.second>pr2.second;
    }

};
int main()
{
    map<int,int>mp;
    cout<<"map.empty()="<<mp.empty()<<endl;
    mp[1]=12;
    cout<<"map.empty()="<<mp.empty()<<endl;
    set<pair<int,int>,cmp>st;
    st.insert(make_pair(2,6));
    st.insert(make_pair(1,2));
    st.insert(make_pair(20,8));
    st.insert(make_pair(16,100));
    st.insert(make_pair(88,18));
    vector<vector<int>>v;
    for(int i=0;i<5;i++)
    {
        vector<int>vv;
        for(int j=0;j<6;j++)
            vv.push_back(j+i);
        v.push_back(vv);
    }
    sort(v.begin(),v.end(),vec_cmp);
    cout<<"user-defined cmp to sort vector:"<<endl;
    for(int i=0;i<v.size();i++)
    {
        for(int j=0;j<v[i].size();j++)
            cout<<v[i][j]<<' ';
        cout<<endl;
    }
    cout<<"user-defined cmp_class to sort set:"<<endl;
    for(auto e:st)
        cout<<e.first<<','<<e.second<<endl;
    return 0;
}
