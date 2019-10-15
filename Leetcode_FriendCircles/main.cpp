#include <iostream>
#include<vector>
#include<queue>
using namespace std;
/*������ȱ������ݹ��*/
class Solution_1 {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int res=0;
        const int n=M.size();
        vector<bool>visited(n,false);
        for(int i=0;i<n;i++)
        {
            if(visited[i])
                continue;
            dfs(i,M,visited,n);
            res++;
        }
        return res;
    }
    void dfs(int i,const vector<vector<int>>& M,vector<bool>&visited,const int &n)
    {
        visited[i]=true;
        for(int j=0;j<n;j++)
        {
            if(!M[i][j]||visited[j])
                continue;
            dfs(j,M,visited,n);
        }
    }
};

/*������ȱ������ǵݹ��*/
class Solution_2 {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int res=0; /*����Ȧ����*/
        const int n=M.size();
        vector<bool>visited(n,false); /*��¼�����ʹ�����*/
        for(int i=0;i<n;i++)
        {
            if(visited[i])
                continue;
            queue<int>q;
            q.push(i);
            while(!q.empty())
            {
                int j=q.front();
                q.pop();
                visited[j]=true;
                for(int k=0;k<n;k++)
                {
                    if(!M[j][k] || visited[k])
                        continue;
                    q.push(k);
                }
            }
            res++;
        }
        return res;
    }
};


int main()
{
    cout << "input friend number N and their relationship:" << endl;
    int n;
    cin>>n;
    vector<vector<int>>M;
    for(int i=0;i<n;i++)
    {
        vector<int>tmp(n);
        int b;
        for(int j=0;j<n;j++)
        {
            cin>>b;
            tmp[j]=b;
        }
        M.push_back(tmp);
    }
    Solution_1 s1;
    Solution_2 s2;
    cout<<"friend circle number1 = "<<s1.findCircleNum(M)<<endl;
    cout<<"friend circle number2 = "<<s2.findCircleNum(M)<<endl;

    return 0;
}
