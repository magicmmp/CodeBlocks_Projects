#include <iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<queue>
using namespace std;

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {


    }
    void findloop(unordered_map<int,unordered_set<int>>&mp,bool &res)
    {

    }
};

/*׼������������������� �������������������*/
int main()
{
    vector<vector<int>>edges;
    int n;
    cin>>n; /*��˵���м���������*/
    for(int i=0;i<n;i++)
    {
        int u,v;
        vector<int>tmp(2);
        cin>>u>>v;
        if(u<v)
        {
            tmp[0]=u;
            tmp[1]=v;
        }
        else
        {
            tmp[0]=v;
            tmp[1]=u;
        }
        edges.push_back(tmp);
    }



    return 0;
}
