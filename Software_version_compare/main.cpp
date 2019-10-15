#include <iostream>
#include<string>
#include <cstdlib>
#include<vector>
#include<map>
using namespace std;
/*
题目地址 https://jinshuju.net/f/fQfQEN
请用您熟悉的编程语言，编程实现一个比较任意两个软件版本号大小的函数，
如 1.2.3a 和 1.2.4b 比较，后者版本号更大，请考虑各种情况，不可以使用系统提供的比较函数。
*/

vector<string> split(const string &s)
{
    /*本函数拆分版本数字的各个分量，若个数小于4个，填充为4个，便于比较*/
    int num=0;
    int p1=0;
    while(p1<s.size() && (s[p1]<'0' || s[p1]>'9') )
        p1++;
    int p2=p1;
    vector<string>res;
    while(p1<s.size())
    {
        while(p2<s.size() && s[p2]!='.')
            p2++;
        res.push_back(s.substr(p1,p2-p1));
        p2++;
        p1=p2;
        num++;
    }
    if(num==2)
    {
        res.push_back("0");
        res.push_back("r");  /*统一填充版本修饰词*/
    }
    if(num==3)
    {
        p1=0;
        while(p1<res[2].size() && res[2][p1]>='0'&& res[2][p1]<='9')
            p1++;
        if(p1<res[2].size())
        {
            res.push_back(res[2].substr(p1));
            res[2]=res[2].substr(0,p1);
        }
        else
            res.push_back("r");
    }
    return res;
}
/*返回1表示版本ver1大于ver2，0表示相等，-1表示小于。*/
int ver_cmp(string ver1,string ver2,map<string,int>&dict)
{
    int res=0;
    vector<string>vs1=split(ver1);
    vector<string>vs2=split(ver2);

    /*先比较主版本号，主版本号权值最大*/
    res=atoi(vs1[0].c_str())-atoi(vs2[0].c_str());
    if(res>0)
        return 1;
    if(res<0)
        return -1;
    /*主版本号相同时，比较次版本号*/
    res=atoi(vs1[1].c_str())-atoi(vs2[1].c_str());
    if(res>0)
        return 1;
    if(res<0)
        return -1;
     /*次版本号相同时，比较修正号*/
    res=atoi(vs1[2].c_str())-atoi(vs2[2].c_str());
    if(res>0)
        return 1;
    if(res<0)
        return -1;
    /*比较版本号修饰词*/
    res=dict[vs1[3]]-dict[vs2[3]];
    if(res>0)
        return 1;
    if(res<0)
        return -1;

    return 0;
}
/*只实现了版本号全为数字，或指定字母修饰词在最后的版本号比较*/

int main()
{
    map<string,int>dict;  /*设后面有这些修饰词。没有修饰词或有r，代表正式版*/
    dict["a"]=0;
    dict["b"]=1;
    dict["c"]=2;
    dict["d"]=3;
    dict["e"]=4;
    dict["r"]=5;
    cout << "版本大小比较，默认版本分量间用 点号 . 隔开，例如： 1.2.2a " << endl;
    cout << "输入2个待比较的版本号，以空格隔开：" << endl;
    while(1)
{
    string s1,s2;
    cin>>s1>>s2;
    auto res=split(s1);
    cout << "版本号1被分解为：" << endl;
    for(auto e:res)
        cout<<e<<' ';
    cout<<endl;

    res=split(s2);
    cout << "版本号2被分解为：" << endl;
    for(auto e:res)
        cout<<e<<' ';
    cout<<endl;
    cout<<"结果 ："<<endl;
    if(ver_cmp(s1,s2,dict)==0)
        cout<<s1<<" 等于 "<<s2<<endl;
    else if(ver_cmp(s1,s2,dict)>0)
        cout<<s1<<" 大于 "<<s2<<endl;
    else
        cout<<s1<<" 小于 "<<s2<<endl;
}

    return 0;
}
