#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;


int main()
{
    int m,n,k=0;
    cin>>m;
    n=m;
    vector<vector<int>>Add;
    for(int i=0;i<m;i++)
    for(int j=0;j<m;j++)
    {
        vector<int>ad(2,0);
        int c;
        cin>>c;
        if(c)
        {
            ad[0]=i;
            ad[1]=j;
            Add.push_back(ad);
            k++;
        }
    }
    vector<vector<int>>Map(m,vector<int>(n,-1));
    vector<int>result(k,0);
    unordered_map<int,set<pair<int,int>>>LandSet;
    int TotalLandNum=0;


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
        set<int> s;
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
    }
    cout<<result[k-1];

    return 0;
}








