#include <iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
bool cmp(const vector<int>&v1,const vector<int>&v2)
{
    int i=v1.size()-2;
    while(i>0&&v1[i]==v2[i])
        i--;
    return v1[i]>v2[i];
}
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
/*程序已通过*/
int main()
{
    int n;
    cin>>n;  /*待输入的字母串数量*/
    vector<string>v;/*存放输入的大写字母串*/
    int maxlen=0; /*字母串的最大位数*/
    for(int i=0;i<n;i++)
    {
       string s;
       cin>>s;
       if(maxlen<s.size())
          maxlen=s.size();
       v.push_back(s);
    }
    set<char>st;/*不能被映射为0的字母*/
    for(int i=0;i<n;i++)
    if(st.find(v[i][0])==st.end())
            st.insert(v[i][0]);
    set<char>cnum;/*所有不同的字母集合*/
    for(int i=0;i<n;i++)
    for(int j=0;j<v[i].size();j++)
        if(cnum.find(v[i][j])==cnum.end())
            cnum.insert(v[i][j]);
    map<char,vector<int>>mp;/*每个字母在不同的位出现了几次，即获得的权值*/
    for(auto e:cnum) /*先初始化这个 mp*/
    {
        vector<int>tmp(maxlen+1,0);
        tmp[maxlen]=e;
        mp[e]=tmp;
    }
    for(int i=0;i<n;i++)
    {
        int len=v[i].size();
        for(int j=0;j<len;j++)
            mp[v[i][j]][len-j-1]++;
    }
    vector<vector<int>>csort; /*取出带有权值的数组，每个数组最后一个数是该字母*/
    for(auto it=mp.begin();it!=mp.end();it++)
    {
        csort.push_back(it->second);
    }
    for(int i=0;i<csort.size();i++)  /*权值的进位处理，应该按10进制*/
    {
        for(int j=0;j<maxlen-1;j++)
        if(csort[i][j]>10)
        {
                csort[i][j+1]=csort[i][j+1]+csort[i][j]/10;
                csort[i][j]=csort[i][j]%10;
        }
    }
    sort(csort.begin(),csort.end(),cmp);/*排序，获得最大权值的字母在前面*/
    vector<char>res;
    for(int i=0;i<csort.size();i++)
        res.push_back(csort[i][maxlen]);
    if(st.find(res.back())!=st.end() && res.size()>9) /*最后一个字母不能映射为0时*/
    {
        int i=res.size()-2;
        while(st.find(res[i])!=st.end()&&i>0)
            i--;
        char tmp=res[i];
        while(i<res.size()-1)
        {
            res[i]=res[i+1];
            i++;
        }
        res[i]=tmp;
    }
    map<char,char>YS;/*存放大写字母和数字字符的映射结果*/
    for(int i=0,j=9;i<res.size();i++,j--)
        YS[res[i]]=j+'0';

    cout<<"Different letter numbers= "<<res.size()<<endl;
    for(auto it=YS.begin();it!=YS.end();it++)
        cout<<it->first<<" -> "<<it->second<<endl;

    for(int i=0;i<n;i++)
    for(int j=0;j<v[i].size();j++)
        v[i][j]=YS[v[i][j]];  /*将字母改为对应数字字符*/
    string sum;
    for(int i=0;i<n;i++)
        sum=IntAdd(sum,v[i]);  /*大整数相加*/
    cout<<sum<<endl;


    return 0;
}
