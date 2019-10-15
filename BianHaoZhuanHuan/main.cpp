#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
string NumToZimu(string s) /*把数字列号转换为字母*/
{
    int p;
    p=1;
    while(s[p]!='C')
        p++;
    string s1,s2;
    s1=s.substr(1,p-1); /*数字行号*/
    s2=s.substr(p+1);   /*数字列号*/
    const char* ss2=s2.c_str();
    long long L=atoi(ss2);
    cout<<s<<",十进制列号是:"<<L<<endl;
    string Lstr;
    while(L)
    {
        char c=L%26+'A'-1;
        Lstr=c+Lstr;
        L=L/26;
    }
    return Lstr+s1;
}

string ZiMuToNum(string s)
{
    int p=0;
    int p1;
    while(p<s.size()&&s[p]>='A'&&s[p]<='Z')
        p++;
    p1=p-1;
    string col=s.substr(0,p);
    string row=s.substr(p);
    long long L=0;
    for(int i=0;i<p1;i++)
    {
        L=L+s[i]-'A'+1;
        L=L*26;
    }
    L=L+s[p1]-'A'+1;
    cout<<s<<",十进制列号是:"<<L<<endl;
    string Lstr;
    while(L)
    {
        char c=L%10+'0';
        Lstr.insert(Lstr.begin(),c);
        L=L/10;
    }
    return 'R'+row+'C'+Lstr;
}
bool isZiMu(string &s)
{
    int p=0;
    while(s[p]>='A'&&s[p]<='Z')
        p++;
    bool res=true;
    for(int i=p;i<s.size()&&res;i++)
    {
        if(s[i]>='A'&&s[i]<='Z')
            res=false;
    }
    return res;
}


int main()
{
    cout << "Please input:" << endl;
    int T;
    cin>>T;
    for(int i=0;i<T;i++)
    {
        string s;
        cin>>s;
        if(isZiMu(s))
            cout<<ZiMuToNum(s)<<endl;
        else
            cout<<NumToZimu(s)<<endl;
    }

    return 0;
}
