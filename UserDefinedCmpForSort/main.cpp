#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib> //to use atoi()
using namespace std;
bool cmp(const string &s1,const string &s2)
{
    int p1,p2;
    p1=s1.size()-1;
    p2=s2.size()-1;
    while(s1[p1]!='/')
        p1--;
    while(s2[p2]!='/')
        p2--;
    p1++;
    p2++;
    string sb1=s1.substr(p1);
    string sb2=s2.substr(p2);
    return atoi(sb1.c_str()) < atoi(sb2.c_str());
}
int MaskLen(const string& s)
{
    int pos;
    pos=s.size()-1;
    while(s[pos]!='/')
        pos--;
    pos++;
    string sb=s.substr(pos);
    return atoi(sb.c_str());
}
int IntAddr(const string& s)
{
    int p1,p2;
    unsigned int n,val;
    string sb;
    val=0;
    p1=0;
    p2=0;
    while(s[p2]!='.')
        p2++;
    sb=s.substr(p1,p2-p1);
    n=atoi(sb.c_str());
    val=val|n<<24;

    p1=p2+1;
    p2=p1;
    while(s[p2]!='.')
        p2++;
    sb=s.substr(p1,p2-p1);
    n=atoi(sb.c_str());
    val=val|n<<16;

    p1=p2+1;
    p2=p1;
    while(s[p2]!='.')
        p2++;
    sb=s.substr(p1,p2-p1);
    n=atoi(sb.c_str());
    val=val|n<<8;

    p1=p2+1;
    p2=p1;
    while(s[p2]!='/')
        p2++;
    sb=s.substr(p1,p2-p1);
    n=atoi(sb.c_str());
    val=val|n;
    return val;
}


int main()
{
    string s1("192.168.0.1/22");
    string s2("19.1.1.0/2");
    string s3("1.1.0.9/25");
    cout<<"s1= 0x"<<hex<<IntAddr(s1)<<endl;
    cout<<"s2= 0x"<<hex<<IntAddr(s2)<<endl;
    cout<<"s3= 0x"<<hex<<IntAddr(s3)<<endl;
    vector<string>v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);
    cout<<"Before sort:"<<endl;
    for(auto e:v)
        cout<<e<<" , mask len = "<<MaskLen(e)<<endl;
    sort(v.begin(),v.end(),cmp);
    cout<<"After sort:"<<endl;
    for(auto e:v)
        cout<<e<<" , mask len = "<<MaskLen(e)<<endl;

    return 0;
}
