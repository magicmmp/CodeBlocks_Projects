#include <iostream>
#include<string>
#include<vector>
using namespace std;

string IntAdd(string s1,string s2)
{
    string res;
    int len1=s1.size();
    int len2=s2.size();
    int maxlen;
    if(len1>=len2)
        maxlen=len1;
    else
        maxlen=len2;

    vector<int>v(maxlen,0);

    if(len1>=len2)
    {
        int cha=len1-len2;
        for(int i=0;i<maxlen;i++)
            v[i]=s1[i]-'0';
        for(int i=0;i<len2;i++)
            v[i+cha]=v[i+cha]+s2[i]-'0';
    }
    else
    {
        int cha=len2-len1;
        for(int i=0;i<maxlen;i++)
            v[i]=s2[i]-'0';
        for(int i=0;i<len1;i++)
            v[i+cha]=v[i+cha]+s1[i]-'0';
    }
    for(int i=v.size()-1;i>0;i--)
    {
        if(v[i]>9)
        {
            v[i-1]=v[i-1]+v[i]/10;
            v[i]=v[i]%10;
        }
    }
    if(v[0]>9)
    {
        int tmp=v[0]/10;
        v[0]=v[0]%10;
        v.insert(v.begin(),tmp);
    }
    for(int i=0;i<v.size();i++)
    {
        char c=v[i]+'0';
        res.push_back(c);
    }

    return res;
}

int main()
{
    string s1,s2;
    cout<<"please input s1,s2"<<endl;
    while(cin>>s1>>s2)
        cout<<s1<<" + "<<s2<<" = "<<IntAdd(s1,s2)<<endl;
    return 0;
}
