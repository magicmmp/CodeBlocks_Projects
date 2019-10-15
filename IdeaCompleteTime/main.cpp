#include <iostream>
#include<set>
#include<vector>
#include<queue>
using namespace std;
struct cmp /*已经存在的任务则按多个规则选择*/
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
struct cmp2  /*总任务先按提出时间顺序排序，以供进一步选择*/
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
        if(v1[0]==v2[0])  /*程序员下次空闲时间*/
        {
            return v1[1]>v2[1]; /*程序员编号*/
        }
        else
            return v1[0]>v2[0];
    }
};
/*有问题，试试只用vector加排序函数*/
int main()
{
    int N,M,P;
    /*输入第一行三个数N、M、P，分别表示有N个PM，M个程序员，P个idea。
      随后有P行，每行有4个数字，分别是PM序号、提出时间、优先等级和所需时间。
      全部数据范围 [1, 3000]。*/
    cin>>N>>M>>P;
    multiset<vector<int>,cmp2>idea;
    for(int i=0;i<P;i++)
    {
        vector<int>ide(5);
        ide[0]=i;
        cin>>ide[1]>>ide[2]>>ide[3]>>ide[4];
        idea.insert(ide);
    }
    cout<<"任务个数= "<<idea.size()<<",任务处理顺序："<<endl;
    for(auto e:idea)
        cout<<e[0]<<' '<<e[1]<<' '<<e[2]<<' '<<e[3]<<' '<<e[4]<<endl;
    priority_queue<vector<int>,vector<vector<int>>,queue_cmp>q2;
    for(int i=0;i<M;i++)
    {
        vector<int>vv(2);
        vv[0]=1; /*程序员下次能空闲的时间*/
        vv[1]=i; /*程序员编号*/
        q2.push(vv);
    }
    priority_queue<vector<int>,vector<vector<int>>,queue_cmp>q;
    while(!q2.empty())
    {
        auto e=q2.top();
        q2.pop();
        q.push(e);
        cout<<"初始程序员编号="<<e[1]<<",下次空闲时间="<<e[0]<<endl;
    }

    multiset<vector<int>,queue_cmp>t;
    while(! idea.empty())
    {
        cout<<"idea 还有 "<<idea.size()<<" 个"<<endl;
        auto it2=idea.begin();
        vector<int>tt(2,0);/*记录任务编号，完成时间*/
        auto vv=q.top(); /*弹出一个程序员*/
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
        tt[0]=(*it)[0]; /*任务编号*/
        t.insert(tt);
cout<<"程序员="<<vv[1]<<",空闲时间="<<vv[0]<<",处理任务号="<<tt[0]<<",提出时间="<<(*it2)[2]<<",完成时间="<<tt[1]<<endl;
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
