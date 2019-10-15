#include <iostream>
#include<vector>
#include<set>
#include<unordered_map>
#include<queue>
using namespace std;
/*�ǵݹ�������ȱ�������k������ܴﵽ��������*/
void bfs(const int &k, unordered_map<int,set<int>>&mp, vector<set<int>>&chu)
{
    queue<int>q;
    q.push(k);
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        chu[k].insert(tmp);
        for(auto e:mp[tmp])
        {
            if(chu[k].find(e)==chu[k].end())
                q.push(e);
        }
    }
    chu[k].erase(k);
    cout<<endl;
}


/*
�����������룺
5 5
0 2
1 2
1 3
3 0
3 4
*/

int main()
{
    int n,m;
    cin>>n>>m;/*���б�Ŵ�0��ʼ��*/
    unordered_map<int,set<int>>mp;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        mp[u].insert(v);
    }
    set<int>s0;
    vector<set<int>>chu(n,s0);/*��i��������Ե�����ٸ�����*/
    vector<set<int>>ru(n,s0);/*�ж��ٸ����п��Ե����i*/
    for(int i=0;i<n;i++)
    {
        if(mp[i].empty())
            continue;
        bfs(i,mp,chu);
    }
    for(int i=0;i<n;i++)
    {
        if(chu[i].empty())
            continue;
        for(auto e:chu[i])
            if(ru[e].find(i)==ru[e].end())
                ru[e].insert(i);
    }
    for(int i=0;i<n;i++)
    {
        cout<<"��  "<<i<<"  �������Ե���  "<<chu[i].size()<<"  �����У�"<<endl;
        for(auto e:chu[i])
            cout<<' '<<e;
        cout<<endl;

        cout<<"������  "<<ru[i].size()<<"  ������ "<<"���Դﵽ  "<<i<<"  :"<<endl;
        for(auto e:ru[i])
            cout<<' '<<e;
        cout<<endl;
        cout<<endl;
    }
    int num=0;
    for(int i=0;i<n;i++)
    if(ru[i].size()>chu[i].size())
    {
            num++;
            s0.insert(i);
    }
    cout<<"��Ҫ������ "<<s0.size()<<" ���������ǣ�"<<endl;
    for(auto e:s0)
        cout<<' '<<e;
    cout<<endl;

    return 0;
}
