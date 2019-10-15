#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    vector<string> v;
    int num;
    cout<<"please input num and string:"<<endl;
    cin>>num;
    for(int i=0;i<num;i++)
    {
        string s;
        cin>>s;
        v.push_back(s);
    }
    cout<<"what you input, num= "<<num<<endl;
    cout<<"before sort:"<<endl;
    for(auto e:v)
        cout<<e<<endl;
    for(int num=0;num<v.size()-1;num++)
    for(int idx=0;idx<v.size()-num-1;idx++)
        if(v[idx]+v[idx+1] < v[idx+1]+v[idx])
            swap(v[idx],v[idx+1]);
    cout<<"after sort:"<<endl;
    for(auto e:v)
        cout<<e<<endl;
}
