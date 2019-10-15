#include <iostream>
#include<vector>
#include <cstdlib>
#include<cstdio>
#include <ctime>

using namespace std;


class SortMethod
{
public:
    void merge_sort(vector<int>&v)  /* �鲢������ýӿ� */
    {
        vector<int>tmp(v.size());
        MergeSort(v,tmp,0,v.size()-1);
    }

    /*�������Ԫ���������ţ�����ȫ��������ʾ*/
    void heap_sort(vector<int>&v)   /* ��������ýӿ� */
    {
        for(int i=(v.size()-1)/2;i>=0;i--)
            PercDown(v,i,v.size());  /* ���к��ӵĽڵ㿪ʼ�������󶥶� */
        for(int i=v.size()-1;i>0;i--)  /*����ӶѶ�ȡ�����ֵ���൱�ڵ����Ѷ�Ԫ�أ������������*/
        {
            swap(v[0],v[i]);
            PercDown(v,0,i);  /*��ԶѶ�Ԫ�ر����������¹�������ѣ���Ԫ���𽥼���*/
        }
    }
    /*������д�㷨�ֲᣬд�ݹ��*/
    void quick_sort(vector<int>&v)
    {
        q_sort(v,0,v.size()-1);
    }




private:
    void MergeSort(vector<int>&v,vector<int>&tmp,int left,int right)
    {
        if(left<right)
        {
            int mid=(left+right)/2;
            MergeSort(v,tmp,left,mid);
            MergeSort(v,tmp,mid+1,right);
            Merge(v,tmp,left,mid+1,right);
        }
    }
    void Merge(vector<int>&v,vector<int>&tmp,int LeftPos,int RightPos,int RightEnd)
    {
        int LeftEnd=RightPos-1;
        int tmppos=LeftPos;
        int NumElements=RightEnd-LeftPos+1;

        while(LeftPos<=LeftEnd && RightPos<=RightEnd)
        {
            if(v[LeftPos]<v[RightPos])
                tmp[tmppos++]=v[LeftPos++];
            else
                tmp[tmppos++]=v[RightPos++];
        }
        while(LeftPos<=LeftEnd)
            tmp[tmppos++]=v[LeftPos++];
        while(RightPos<=RightEnd)
            tmp[tmppos++]=v[RightPos++];
        for(int i=0;i<NumElements;i++,RightEnd--)
            v[RightEnd]=tmp[RightEnd];
    }
   /*��λ��Ϊidx��Ԫ���³�������λ�ã�ʹ��idxΪ���ڵ����������󶥶ѵ�Ҫ��*/
   /*���������� n �ǵ�ǰҪ����Ķ�Ԫ�ظ���*/
    void PercDown(vector<int>&v, int idx, int n)
    {
        int tmp;  /*��ʱ���Ŀ��ڵ�ֵ*/
        int child;
        /*��idxԪ��������һ������ʱ�����п�����Ҫ�³�*/
        for(tmp=v[idx]; (idx<<1)+1 < n; idx=child)
        {
            child=(idx<<1)+1;  /*idx������*/
            if(child<n-1 && v[child]<v[child+1])
                ++child; /*������Һ������Һ��ӱ����Ӵ󣬾�ѡ���Һ���*/
            if(tmp<v[child])  /*idx�ڵ������ĺ��ӱȽ�*/
                v[idx]=v[child];
            else
                break;
        }
        v[idx]=tmp;  /*ԭidxֵ���·ŵ�����λ��*/
    }

    /* �ݹ�棬��Ҫ3�������Ŀ���������   */
    void q_sort(vector<int>&v,int Start,int End)
    {
        if(Start<End)
        {
            int pv=part(v,Start,End);
            q_sort(v,Start,pv-1);
            q_sort(v,pv+1,End);
        }
    }

   /* ��������Ļ��ֺ��� */
    int part(vector<int>&v,int Start,int End)
    {
        int tmp=v[Start];
        while(Start<End)
        {
            while(Start<End && v[End]>=tmp)
                End--;
            v[Start]=v[End];
            while(Start<End && v[Start]<=tmp)
                Start++;
            v[End]=v[Start];
        }
        v[Start]=tmp;
        return Start;
    }

};
/*����c �⺯���������������������*/
/* C���ʱ�亯��Ҳ�����õ� */


int main()
{
    const int n=10000000;
    int M=20;
    int step=n>>5;
    cout << "Array size= "<<n << endl;
    vector<int>v;
    time_t tt=time( NULL );
    tm* t= localtime(&tt);
    printf("The time now :  %d-%02d-%02d %02d:%02d:%02d\n",
    t->tm_year + 1900,
    t->tm_mon + 1,
    t->tm_mday,
    t->tm_hour,
    t->tm_min,
    t->tm_sec);

    srand( tt );/* �õ�ǰʱ�䣨unsigned int���ͣ�������������� */

    for(int i=0;i<n;i++)
    {
        int tmp;
        tmp=rand();
        v.push_back(tmp);
    }
    SortMethod sm;

    vector<int>v1(v);
    cout<<"Before sort :"<<endl;
    for(int i=0,j=0;i<M;i++,j=j+step)
        cout<<' '<<v1[j];
    cout<<endl;

    unsigned int t1,t2;

    t1=time( NULL );
    sm.merge_sort(v1);
    t2=time( NULL );
    cout<<"�鲢���� "<<n<<" ��Ԫ������ "<<t2-t1<<" �� ��"<<endl;
    for(int i=0,j=0;i<M;i++,j=j+step)
        cout<<' '<<v1[j];
    cout<<endl;


    vector<int>v2(v);
    t1=time( NULL );
    sm.heap_sort(v2);
    t2=time( NULL );
    cout<<"������  "<<n<<" ��Ԫ������ "<<t2-t1<<" �� ��"<<endl;
    for(int i=0,j=0;i<M;i++,j=j+step)
        cout<<' '<<v2[j];
    cout<<endl;

    vector<int>v3(v);
    t1=time( NULL );
    sm.quick_sort(v3);
    t2=time( NULL );
    cout<<"�������� "<<n<<" ��Ԫ������ "<<t2-t1<<" �� ��"<<endl;
    for(int i=0,j=0;i<M;i++,j=j+step)
        cout<<' '<<v3[j];
    cout<<endl;

  //  cout<<INT_MAX<<endl;





    return 0;
}
