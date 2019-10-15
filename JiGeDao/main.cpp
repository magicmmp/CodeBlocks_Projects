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
    vector<vector<int>>Map(m,vector<int>(n,-1));//��¼�õ������Ŀ�½�أ�½�ر��0~k-1,-1��ʾˮ��
    vector<int>result(k,0);
    unordered_map<int,set<pair<int,int>>>LandSet;
    int TotalLandNum=0;
    cout<<"Before Addland:"<<endl;
    printMap(Map);
    for(int i=0;i<k;i++)
    {
        if(Map[Add[i][0]][Add[i][1]]!=-1 || Add[i][0]>=m || Add[i][1]>=n) /*��Ч���ݲ��ô���������ϴ����*/
        {
            result[i]=result[i-1];
            continue;
        }
        Map[Add[i][0]][Add[i][1]]=i;
        LandSet[i].insert(pair<int,int>(Add[i][0],Add[i][1]));
        int addnum=1;
        set<int> s;       //��һ��������ܱ��м�����ͬ��½�ء�
        if(Add[i][0]==0)  //��������
        {
            if(Add[i][1]==0) //���Ͻ��ǵ�
            {
                if(n>1 && Map[0][1]!=-1) //��ֹһ�оͼ���ұߵĵ��Ƿ���½��
                {
                    if(s.find(Map[0][1])==s.end())
                        s.insert(Map[0][1]);
                }
                if(m>1 && Map[1][0]!=-1) //��ֹһ�оͼ���±ߵĵ�
                {
                    if(s.find(Map[1][0])==s.end())
                        s.insert(Map[1][0]);
                }
            }
             else if(Add[i][1]==n-1) //���Ͻ��ǵ�
            {
                if(n>1 && Map[0][n-2]!=-1) //��ֹһ�оͼ����ߵĵ�
                {
                    if(s.find(Map[0][n-2])==s.end())
                        s.insert(Map[0][n-2]);
                }
                if(m>1 && Map[1][n-1]!=-1) //��ֹһ�оͼ���±ߵĵ�
                {
                    if(s.find(Map[1][n-1])==s.end())
                        s.insert(Map[1][0]);
                }
            }
            else //�����ϱߵ������ǣ�ͬʱ˵������n>2��
            {
                if(Map[0][Add[i][1]-1]!=-1)
                if(s.find(Map[0][Add[i][1]-1])==s.end())
                    s.insert(Map[0][Add[i][1]-1]);
                if(Map[0][Add[i][1]+1]!=-1)
                if(s.find(Map[0][Add[i][1]+1])==s.end())
                    s.insert(Map[0][Add[i][1]+1]);
                if(m>1 && Map[1][Add[i][1]]!=-1) //��ֹһ�оͼ���±ߵĵ�
                {
                    if(s.find(Map[1][Add[i][1]])==s.end())
                        s.insert(Map[1][Add[i][1]]);
                }
            }

        }
        else if(Add[i][0]==m-1) //����������
        {
            if(Add[i][1]==0) //���½��ǵ�
            {
                if(n>1 && Map[m-1][1]!=-1) //��ֹһ�оͼ���ұߵĵ�
                {
                    if(s.find(Map[m-1][1])==s.end())
                        s.insert(Map[m-1][1]);
                }
                if(Map[m-2][0]!=-1) //��ֹһ�оͼ���ϱߵĵ�
                {
                    if(s.find(Map[m-2][0])==s.end())
                        s.insert(Map[m-2][0]);
                }
            }
             else if(Add[i][1]==n-1) //���½��ǵ�
            {
                if(n>1 && Map[m-1][n-2]!=-1) //��ֹһ�оͼ����ߵĵ�
                {
                    if(s.find(Map[m-1][n-2])==s.end())
                        s.insert(Map[m-1][n-2]);
                }
                if(Map[m-2][n-1]!=-1) //��ֹһ�оͼ���ϱߵĵ�
                {
                    if(s.find(Map[m-2][n-1])==s.end())
                        s.insert(Map[m-2][n-1]);
                }
            }
            else //�����±ߵ������ǣ�ͬʱ˵������n>2��
            {
                if(Map[m-1][Add[i][1]-1]!=-1)
                if(s.find(Map[m-1][Add[i][1]-1])==s.end())
                    s.insert(Map[m-1][Add[i][1]-1]);
                if(Map[m-1][Add[i][1]+1]!=-1)
                if(s.find(Map[m-1][Add[i][1]+1])==s.end())
                    s.insert(Map[m-1][Add[i][1]+1]);
                if(Map[m-2][Add[i][1]]!=-1) //��ֹһ�оͼ���ϱߵĵ�
                {
                    if(s.find(Map[m-2][Add[i][1]])==s.end())
                        s.insert(Map[m-2][Add[i][1]]);
                }
            }
        }
        else   //�����������У�ͬʱ˵������>2��
        {
            if(Add[i][1]==0)//����ڵ�һ�е��������ϽǺ����½�
            {
               if(n>1 && Map[Add[i][0]][1]!=-1) //��ֹһ�оͼ���ұߵĵ�
                {
                    if(s.find(Map[Add[i][0]][1])==s.end())
                        s.insert(Map[Add[i][0]][1]);
                }
                if(Map[Add[i][0]-1][0]!=-1) //����ϱߵĵ�
                {
                    if(s.find(Map[Add[i][0]-1][0])==s.end())
                        s.insert(Map[Add[i][0]-1][0]);
                }
                if(Map[Add[i][0]+1][0]!=-1) //����±ߵĵ�
                {
                    if(s.find(Map[Add[i][0]+1][0])==s.end())
                        s.insert(Map[Add[i][0]+1][0]);
                }
            }
            else if(Add[i][1]==n-1) //������ұ߽���У����������ϽǺ����½�
            {
               if(n>1 && Map[Add[i][0]][n-2]!=-1) //��ֹһ�оͼ����ߵĵ�
                {
                    if(s.find(Map[Add[i][0]][n-2])==s.end())
                        s.insert(Map[Add[i][0]][n-2]);
                }
                if(Map[Add[i][0]-1][n-1]!=-1) //����ϱߵĵ�
                {
                    if(s.find(Map[Add[i][0]-1][n-1])==s.end())
                        s.insert(Map[Add[i][0]-1][n-1]);
                }
                if(Map[Add[i][0]+1][n-1]!=-1) //����±ߵĵ�
                {
                    if(s.find(Map[Add[i][0]+1][n-1])==s.end())
                        s.insert(Map[Add[i][0]+1][n-1]);
                }
            }
            else  //���ڱ߽���
            {
                if(Map[Add[i][0]-1][Add[i][1]]!=-1) //����ϱߵĵ�
                {
                    if(s.find(Map[Add[i][0]-1][Add[i][1]])==s.end())
                        s.insert(Map[Add[i][0]-1][Add[i][1]]);
                }
                if(Map[Add[i][0]+1][Add[i][1]]!=-1) //����±ߵĵ�
                {
                    if(s.find(Map[Add[i][0]+1][Add[i][1]])==s.end())
                        s.insert(Map[Add[i][0]+1][Add[i][1]]);
                }
                if(Map[Add[i][0]][Add[i][1]-1]!=-1) //�����ߵĵ�
                {
                    if(s.find(Map[Add[i][0]][Add[i][1]-1])==s.end())
                        s.insert(Map[Add[i][0]][Add[i][1]-1]);
                }
                if(Map[Add[i][0]][Add[i][1]+1]!=-1) //����ұߵĵ�
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








