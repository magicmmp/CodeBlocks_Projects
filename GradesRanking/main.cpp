#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
struct student{
    string name;
    int val;
};
bool cmp(struct student& st1,struct student& st2)
{
    return st1.val<st2.val;
}
int main()
{
    int n;
    int order;
    struct student st0;
    cin>>n;
    cin>>order;
    vector<struct student> v(n,st0);
    for(int i=0;i<n;i++)
    {
        cin>>v[i].name>>v[i].val;
    }
    sort(v.begin(),v.end(),cmp);
    if(order==0)
        reverse(v.begin(),v.end());
    for(auto e:v)
        cout<<e.name<<' '<<e.val<<endl;

}
