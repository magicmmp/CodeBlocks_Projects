#include <iostream>
#include <algorithm>
using namespace std;
bool cmp(int& a,int& b)
{
    return a<b;
}
int main()
{
    int a[20]={2,4,1,23,5,76,0,43,24,65};
    int i;
    for(i=0;i<20;i++)
    cout<<a[i]<<" ";
    cout<<endl;
    sort(a,a+20,cmp);
    for(i=0;i<20;i++)
    cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
