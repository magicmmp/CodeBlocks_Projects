#include <iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
using namespace std;

int main()
{
    int T;
    cin>>T;
for(int i=0;i<T;i++)
{
    string s;
    cin>>s;

    map<char,int>cn; /*记录这个字符串的每个字母出现了几次*/
    for(int j=0;j<s.size();j++)
        cn[s[j]]++;
    vector<string>Nu;
    Nu.push_back("EIGHT");
    Nu.push_back("NINE");
    Nu.push_back("ZERO");
    Nu.push_back("ONE");
    Nu.push_back("TWO");
    Nu.push_back("THREE");
    Nu.push_back("FOUR");
    Nu.push_back("FIVE");
    Nu.push_back("SIX");
    Nu.push_back("SEVEN");

    vector<int>res(10,0);
    while(cn['Z']>0)
    {
        for(auto e:Nu[2])
            cn[e]--;
        res[2]++;
    }
     while(cn['W']>0)
    {
        for(auto e:Nu[4])
            cn[e]--;
        res[4]++;
    }
    while(cn['U']>0)
    {
        for(auto e:Nu[6])
            cn[e]--;
        res[6]++;
    }
    while(cn['O']>0)
    {
        for(auto e:Nu[3])
            cn[e]--;
        res[3]++;
    }
    while(cn['R']>0)
    {
        for(auto e:Nu[5])
            cn[e]--;
        res[5]++;
    }
    while(cn['T']>0)
    {
        for(auto e:Nu[0])
            cn[e]--;
        res[0]++;
    }
    while(cn['X']>0)
    {
        for(auto e:Nu[8])
            cn[e]--;
        res[8]++;
    }
    while(cn['F']>0)
    {
        for(auto e:Nu[7])
            cn[e]--;
        res[7]++;
    }
    while(cn['S']>0)
    {
        for(auto e:Nu[9])
            cn[e]--;
        res[9]++;
    }
    while(cn['N']>0)
    {
        for(auto e:Nu[1])
            cn[e]--;
        res[1]++;
    }
    string ss;
    for(int i=0;i<10;i++)
    {
        char cc='0'+i;
        for(int j=0;j<res[i];j++)
            ss.push_back(cc);
    }
    cout<<ss<<endl;
}
    return 0;
}
