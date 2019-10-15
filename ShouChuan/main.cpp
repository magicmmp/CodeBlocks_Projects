#include <iostream>
#include<vector>
#include<set>
#include<unordered_set>
using namespace std;
/*方法是记录每种颜色在手串哪些位置出现，然后比较位置的距离是否大于等于m*/
int main()
{
    //cout << "Hello world!" << endl;
    int m,n,c;
    cin>>n>>m>>c;
    vector<vector<int>>v;
    for(int i=0;i<n;i++)
    {
        int num;
        int cc;
        cin>>num;
        vector<int>color;
        for(int j=0;j<num;j++)
        {
            cin>>cc;
            color.push_back(cc);
        }
        v.push_back(color);
    }
    for(int i=0;i<m-1;i++)
        v.push_back(v[i]);
    vector<set<int>>pos(c);
    for(int i=0;i<v.size();i++)
    for(int j=0;j<v[i].size();j++)
    {
        pos[v[i][j]-1].insert(i);
    }
    unordered_set<int>res;
    for(int i=0;i<c;i++)
    {
        int p1,p2;
        auto it=pos[i].begin();
        if(pos[i].size()>1)
        for(int j=0;j<pos[i].size()-1;j++)
        {
            p1=*it;
            it++;
            p2=*it;
            if(p2-p1<m)
            {
                res.insert(i);
                j=pos[i].size();
            }
        }
    }
    cout<<res.size()<<endl;


    return 0;
}
