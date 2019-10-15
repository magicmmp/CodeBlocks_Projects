#include <iostream>
#include<vector>
#include <cstdlib>
#include<cstdio>
#include <ctime>

using namespace std;


class SortMethod
{
public:
    void merge_sort(vector<int>&v)  /* 归并排序调用接口 */
    {
        vector<int>tmp(v.size());
        MergeSort(v,tmp,0,v.size()-1);
    }

    /*堆排序的元素用数组存放，用完全二叉树表示*/
    void heap_sort(vector<int>&v)   /* 堆排序调用接口 */
    {
        for(int i=(v.size()-1)/2;i>=0;i--)
            PercDown(v,i,v.size());  /* 从有孩子的节点开始，构建大顶堆 */
        for(int i=v.size()-1;i>0;i--)  /*逐个从堆顶取出最大值，相当于弹出堆顶元素，放在数组后面*/
        {
            swap(v[0],v[i]);
            PercDown(v,0,i);  /*针对堆顶元素被交换，重新构造有序堆，堆元素逐渐减少*/
        }
    }
    /*参照手写算法手册，写递归版*/
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
   /*把位置为idx的元素下沉到合适位置，使以idx为根节点的子树满足大顶堆的要求*/
   /*第三个参数 n 是当前要排序的堆元素个数*/
    void PercDown(vector<int>&v, int idx, int n)
    {
        int tmp;  /*临时存放目标节点值*/
        int child;
        /*当idx元素至少有一个孩子时，才有可能需要下沉*/
        for(tmp=v[idx]; (idx<<1)+1 < n; idx=child)
        {
            child=(idx<<1)+1;  /*idx的左孩子*/
            if(child<n-1 && v[child]<v[child+1])
                ++child; /*如果有右孩子且右孩子比左孩子大，就选择右孩子*/
            if(tmp<v[child])  /*idx节点与最大的孩子比较*/
                v[idx]=v[child];
            else
                break;
        }
        v[idx]=tmp;  /*原idx值被下放到合适位置*/
    }

    /* 递归版，需要3个参数的快速排序函数   */
    void q_sort(vector<int>&v,int Start,int End)
    {
        if(Start<End)
        {
            int pv=part(v,Start,End);
            q_sort(v,Start,pv-1);
            q_sort(v,pv+1,End);
        }
    }

   /* 快速排序的划分函数 */
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
/*利用c 库函数产生随机数，用于排序。*/
/* C库的时间函数也是有用的 */


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

    srand( tt );/* 用当前时间（unsigned int类型）来做随机数种子 */

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
    cout<<"归并排序 "<<n<<" 个元素用了 "<<t2-t1<<" 秒 ："<<endl;
    for(int i=0,j=0;i<M;i++,j=j+step)
        cout<<' '<<v1[j];
    cout<<endl;


    vector<int>v2(v);
    t1=time( NULL );
    sm.heap_sort(v2);
    t2=time( NULL );
    cout<<"堆排序  "<<n<<" 个元素用了 "<<t2-t1<<" 秒 ："<<endl;
    for(int i=0,j=0;i<M;i++,j=j+step)
        cout<<' '<<v2[j];
    cout<<endl;

    vector<int>v3(v);
    t1=time( NULL );
    sm.quick_sort(v3);
    t2=time( NULL );
    cout<<"快速排序 "<<n<<" 个元素用了 "<<t2-t1<<" 秒 ："<<endl;
    for(int i=0,j=0;i<M;i++,j=j+step)
        cout<<' '<<v3[j];
    cout<<endl;

  //  cout<<INT_MAX<<endl;





    return 0;
}
