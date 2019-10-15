#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

void printMap(vector<vector<int>>& Map)
{
    for(int i=0;i<Map.size();i++)
    {
        for(int j=0;j<Map[0].size();j++)
            cout<<Map[i][j]<<"  ";
        cout<<endl;
    }
}

int main()
{
    cout << "Please input : row , colum, and K" << endl;
    int m,n,k;
    cin>>m;
    cin>>n;
    cin>>k;
    vector<vector<int>>Add(k,vector<int>(2,0));
    for(int i=0;i<k;i++)
        cin>>Add[i][0]>>Add[i][1];
    vector<vector<int>>Map(m,vector<int>(n,-1));//记录该点属于哪块陆地，陆地编号0~k-1,-1表示水域。
    vector<int>result(k,0);
    unordered_map<int,set<pair<int,int>>>LandSet;
    int TotalLandNum=0;
    cout<<"Before Addland:"<<endl;
    printMap(Map);
    for(int i=0;i<k;i++)
    {
        if(Map[Add[i][0]][Add[i][1]]!=-1 || Add[i][0]>=m || Add[i][1]>=n) /*无效数据不用处理，结果与上次相等*/
        {
            result[i]=result[i-1];
            continue;
        }
        Map[Add[i][0]][Add[i][1]]=i;
        LandSet[i].insert(pair<int,int>(Add[i][0],Add[i][1]));
        int addnum=1;
        set<int> s;       //数一数这个点周边有几个不同的陆地。
        if(Add[i][0]==0)  //最上那行
        {
            if(Add[i][1]==0) //左上角那点
            {
                if(n>1 && Map[0][1]!=-1) //不止一列就检查右边的点是否是陆地
                {
                    if(s.find(Map[0][1])==s.end())
                        s.insert(Map[0][1]);
                }
                if(m>1 && Map[1][0]!=-1) //不止一行就检查下边的点
                {
                    if(s.find(Map[1][0])==s.end())
                        s.insert(Map[1][0]);
                }
            }
             else if(Add[i][1]==n-1) //右上角那点
            {
                if(n>1 && Map[0][n-2]!=-1) //不止一列就检查左边的点
                {
                    if(s.find(Map[0][n-2])==s.end())
                        s.insert(Map[0][n-2]);
                }
                if(m>1 && Map[1][n-1]!=-1) //不止一行就检查下边的点
                {
                    if(s.find(Map[1][n-1])==s.end())
                        s.insert(Map[1][0]);
                }
            }
            else //不是上边的两个角，同时说明列数n>2。
            {
                if(Map[0][Add[i][1]-1]!=-1)
                if(s.find(Map[0][Add[i][1]-1])==s.end())
                    s.insert(Map[0][Add[i][1]-1]);
                if(Map[0][Add[i][1]+1]!=-1)
                if(s.find(Map[0][Add[i][1]+1])==s.end())
                    s.insert(Map[0][Add[i][1]+1]);
                if(m>1 && Map[1][Add[i][1]]!=-1) //不止一行就检查下边的点
                {
                    if(s.find(Map[1][Add[i][1]])==s.end())
                        s.insert(Map[1][Add[i][1]]);
                }
            }

        }
        else if(Add[i][0]==m-1) //最下面那行
        {
            if(Add[i][1]==0) //左下角那点
            {
                if(n>1 && Map[m-1][1]!=-1) //不止一列就检查右边的点
                {
                    if(s.find(Map[m-1][1])==s.end())
                        s.insert(Map[m-1][1]);
                }
                if(Map[m-2][0]!=-1) //不止一行就检查上边的点
                {
                    if(s.find(Map[m-2][0])==s.end())
                        s.insert(Map[m-2][0]);
                }
            }
             else if(Add[i][1]==n-1) //右下角那点
            {
                if(n>1 && Map[m-1][n-2]!=-1) //不止一列就检查左边的点
                {
                    if(s.find(Map[m-1][n-2])==s.end())
                        s.insert(Map[m-1][n-2]);
                }
                if(Map[m-2][n-1]!=-1) //不止一行就检查上边的点
                {
                    if(s.find(Map[m-2][n-1])==s.end())
                        s.insert(Map[m-2][n-1]);
                }
            }
            else //不是下边的两个角，同时说明列数n>2。
            {
                if(Map[m-1][Add[i][1]-1]!=-1)
                if(s.find(Map[m-1][Add[i][1]-1])==s.end())
                    s.insert(Map[m-1][Add[i][1]-1]);
                if(Map[m-1][Add[i][1]+1]!=-1)
                if(s.find(Map[m-1][Add[i][1]+1])==s.end())
                    s.insert(Map[m-1][Add[i][1]+1]);
                if(Map[m-2][Add[i][1]]!=-1) //不止一行就检查上边的点
                {
                    if(s.find(Map[m-2][Add[i][1]])==s.end())
                        s.insert(Map[m-2][Add[i][1]]);
                }
            }
        }
        else   //不是上下两行，同时说明行数>2。
        {
            if(Add[i][1]==0)//如果在第一列但不是左上角和左下角
            {
               if(n>1 && Map[Add[i][0]][1]!=-1) //不止一列就检查右边的点
                {
                    if(s.find(Map[Add[i][0]][1])==s.end())
                        s.insert(Map[Add[i][0]][1]);
                }
                if(Map[Add[i][0]-1][0]!=-1) //检查上边的点
                {
                    if(s.find(Map[Add[i][0]-1][0])==s.end())
                        s.insert(Map[Add[i][0]-1][0]);
                }
                if(Map[Add[i][0]+1][0]!=-1) //检查下边的点
                {
                    if(s.find(Map[Add[i][0]+1][0])==s.end())
                        s.insert(Map[Add[i][0]+1][0]);
                }
            }
            else if(Add[i][1]==n-1) //如果在右边界的列，但不在右上角和右下角
            {
               if(n>1 && Map[Add[i][0]][n-2]!=-1) //不止一列就检查左边的点
                {
                    if(s.find(Map[Add[i][0]][n-2])==s.end())
                        s.insert(Map[Add[i][0]][n-2]);
                }
                if(Map[Add[i][0]-1][n-1]!=-1) //检查上边的点
                {
                    if(s.find(Map[Add[i][0]-1][n-1])==s.end())
                        s.insert(Map[Add[i][0]-1][n-1]);
                }
                if(Map[Add[i][0]+1][n-1]!=-1) //检查下边的点
                {
                    if(s.find(Map[Add[i][0]+1][n-1])==s.end())
                        s.insert(Map[Add[i][0]+1][n-1]);
                }
            }
            else  //不在边界上
            {
                if(Map[Add[i][0]-1][Add[i][1]]!=-1) //检查上边的点
                {
                    if(s.find(Map[Add[i][0]-1][Add[i][1]])==s.end())
                        s.insert(Map[Add[i][0]-1][Add[i][1]]);
                }
                if(Map[Add[i][0]+1][Add[i][1]]!=-1) //检查下边的点
                {
                    if(s.find(Map[Add[i][0]+1][Add[i][1]])==s.end())
                        s.insert(Map[Add[i][0]+1][Add[i][1]]);
                }
                if(Map[Add[i][0]][Add[i][1]-1]!=-1) //检查左边的点
                {
                    if(s.find(Map[Add[i][0]][Add[i][1]-1])==s.end())
                        s.insert(Map[Add[i][0]][Add[i][1]-1]);
                }
                if(Map[Add[i][0]][Add[i][1]+1]!=-1) //检查右边的点
                {
                    if(s.find(Map[Add[i][0]][Add[i][1]+1])==s.end())
                        s.insert(Map[Add[i][0]][Add[i][1]+1]);
                }
            }
        }
        addnum=addnum-s.size();

        TotalLandNum=TotalLandNum+addnum;
        result[i]=TotalLandNum;
        for(set<int>::iterator it=s.begin();it!=s.end();it++)
        {
            LandSet[i].insert(LandSet[*it].begin(),LandSet[*it].end());
            for(auto e:LandSet[*it])
                Map[e.first][e.second]=i;
            LandSet.erase(*it);
        }
        cout<<"After addland,i="<<i<<",addnum="<<addnum<<",TotalLandNum="<<TotalLandNum<<",s.size()="<<s.size()<<endl;
        for(set<int>::iterator it=s.begin();it!=s.end();it++)
        {
            cout<<"land: "<<i<<" is adjacent to "<<"land: "<<*it<<endl;
        }
        printMap(Map);
    }
    cout<<"The number of land:"<<endl;
    for(auto e:result)
        cout<<e<<" ";
    cout<<endl;

    return 0;
}








