#include <iostream>
#include<string>
#include <cstdlib>
#include<vector>
#include<map>
using namespace std;
/*
��Ŀ��ַ https://jinshuju.net/f/fQfQEN
��������Ϥ�ı�����ԣ����ʵ��һ���Ƚ�������������汾�Ŵ�С�ĺ�����
�� 1.2.3a �� 1.2.4b �Ƚϣ����߰汾�Ÿ����뿼�Ǹ��������������ʹ��ϵͳ�ṩ�ıȽϺ�����
*/

vector<string> split(const string &s)
{
    /*��������ְ汾���ֵĸ���������������С��4�������Ϊ4�������ڱȽ�*/
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
        res.push_back("r");  /*ͳһ���汾���δ�*/
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
/*����1��ʾ�汾ver1����ver2��0��ʾ��ȣ�-1��ʾС�ڡ�*/
int ver_cmp(string ver1,string ver2,map<string,int>&dict)
{
    int res=0;
    vector<string>vs1=split(ver1);
    vector<string>vs2=split(ver2);

    /*�ȱȽ����汾�ţ����汾��Ȩֵ���*/
    res=atoi(vs1[0].c_str())-atoi(vs2[0].c_str());
    if(res>0)
        return 1;
    if(res<0)
        return -1;
    /*���汾����ͬʱ���Ƚϴΰ汾��*/
    res=atoi(vs1[1].c_str())-atoi(vs2[1].c_str());
    if(res>0)
        return 1;
    if(res<0)
        return -1;
     /*�ΰ汾����ͬʱ���Ƚ�������*/
    res=atoi(vs1[2].c_str())-atoi(vs2[2].c_str());
    if(res>0)
        return 1;
    if(res<0)
        return -1;
    /*�Ƚϰ汾�����δ�*/
    res=dict[vs1[3]]-dict[vs2[3]];
    if(res>0)
        return 1;
    if(res<0)
        return -1;

    return 0;
}
/*ֻʵ���˰汾��ȫΪ���֣���ָ����ĸ���δ������İ汾�űȽ�*/

int main()
{
    map<string,int>dict;  /*���������Щ���δʡ�û�����δʻ���r��������ʽ��*/
    dict["a"]=0;
    dict["b"]=1;
    dict["c"]=2;
    dict["d"]=3;
    dict["e"]=4;
    dict["r"]=5;
    cout << "�汾��С�Ƚϣ�Ĭ�ϰ汾�������� ��� . ���������磺 1.2.2a " << endl;
    cout << "����2�����Ƚϵİ汾�ţ��Կո������" << endl;
    while(1)
{
    string s1,s2;
    cin>>s1>>s2;
    auto res=split(s1);
    cout << "�汾��1���ֽ�Ϊ��" << endl;
    for(auto e:res)
        cout<<e<<' ';
    cout<<endl;

    res=split(s2);
    cout << "�汾��2���ֽ�Ϊ��" << endl;
    for(auto e:res)
        cout<<e<<' ';
    cout<<endl;
    cout<<"��� ��"<<endl;
    if(ver_cmp(s1,s2,dict)==0)
        cout<<s1<<" ���� "<<s2<<endl;
    else if(ver_cmp(s1,s2,dict)>0)
        cout<<s1<<" ���� "<<s2<<endl;
    else
        cout<<s1<<" С�� "<<s2<<endl;
}

    return 0;
}
