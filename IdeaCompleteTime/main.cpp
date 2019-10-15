#include <iostream>
#include<set>
#include<vector>
#include<queue>
using namespace std;
struct cmp /*�Ѿ����ڵ������򰴶������ѡ��*/
{
    bool operator()(const vector<int>&v1,const vector<int>&v2)
    {
        if(v1[3]==v2[3])
        {
            if(v1[4]==v2[4])
            {
                if(v1[1]==v2[1])
                {
                    return v1[2]<v2[2];
                }
                else
                    return v1[1]<v2[1];

            }
            else
                return v1[4]<v2[4];
        }
        else
            return v1[3]<v2[3];
    }
};
struct cmp2  /*�������Ȱ����ʱ��˳�������Թ���һ��ѡ��*/
{
    bool operator()(const vector<int>&v1,const vector<int>&v2)
    {
        return v1[2]<v2[2];
    }
};

struct queue_cmp
{
    bool operator()(const vector<int>&v1,const vector<int>&v2)
    {
        if(v1[0]==v2[0])  /*����Ա�´ο���ʱ��*/
        {
            return v1[1]>v2[1]; /*����Ա���*/
        }
        else
            return v1[0]>v2[0];
    }
};
/*�����⣬����ֻ��vector��������*/
int main()
{
    int N,M,P;
    /*�����һ��������N��M��P���ֱ��ʾ��N��PM��M������Ա��P��idea��
      �����P�У�ÿ����4�����֣��ֱ���PM��š����ʱ�䡢���ȵȼ�������ʱ�䡣
      ȫ�����ݷ�Χ [1, 3000]��*/
    cin>>N>>M>>P;
    multiset<vector<int>,cmp2>idea;
    for(int i=0;i<P;i++)
    {
        vector<int>ide(5);
        ide[0]=i;
        cin>>ide[1]>>ide[2]>>ide[3]>>ide[4];
        idea.insert(ide);
    }
    cout<<"�������= "<<idea.size()<<",������˳��"<<endl;
    for(auto e:idea)
        cout<<e[0]<<' '<<e[1]<<' '<<e[2]<<' '<<e[3]<<' '<<e[4]<<endl;
    priority_queue<vector<int>,vector<vector<int>>,queue_cmp>q2;
    for(int i=0;i<M;i++)
    {
        vector<int>vv(2);
        vv[0]=1; /*����Ա�´��ܿ��е�ʱ��*/
        vv[1]=i; /*����Ա���*/
        q2.push(vv);
    }
    priority_queue<vector<int>,vector<vector<int>>,queue_cmp>q;
    while(!q2.empty())
    {
        auto e=q2.top();
        q2.pop();
        q.push(e);
        cout<<"��ʼ����Ա���="<<e[1]<<",�´ο���ʱ��="<<e[0]<<endl;
    }

    multiset<vector<int>,queue_cmp>t;
    while(! idea.empty())
    {
        cout<<"idea ���� "<<idea.size()<<" ��"<<endl;
        auto it2=idea.begin();
        vector<int>tt(2,0);/*��¼�����ţ����ʱ��*/
        auto vv=q.top(); /*����һ������Ա*/
        q.pop();
        set<vector<int>,cmp>ExistIdea;
        if((*it2)[2]>vv[0])
        {
           ExistIdea.insert(*it2);
           tt[1]=(*it2)[2]+(*it2)[4];
           idea.erase(it2);
        }
        else
            {
                bool flag=true;
                while(flag && ! idea.empty() )
                {
                    if((*it2)[2]<=vv[0])
                    {
                        ExistIdea.insert(*it2);
                        idea.erase(it2);
                        it2=idea.begin();
                    }
                    else
                    {
                        flag=false;
                    }
                }
                tt[1]=vv[0]+(*ExistIdea.begin())[4];
            }
        auto it=ExistIdea.begin();
        tt[0]=(*it)[0]; /*������*/
        t.insert(tt);
cout<<"����Ա="<<vv[1]<<",����ʱ��="<<vv[0]<<",���������="<<tt[0]<<",���ʱ��="<<(*it2)[2]<<",���ʱ��="<<tt[1]<<endl;
        ExistIdea.erase(it);
        for(auto e:ExistIdea)
            idea.insert(e);
        ExistIdea.clear();

        vv[0]=tt[1];
        q.push(vv);
    }
    for(auto e:t)
        cout<<e[1]<<endl;

    return 0;
}
