#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
using namespace std;
/*不能在类内自定义的比较函数，要定义成全局的*/
bool cmp(const string &s1,const string &s2)
{
    return (s1+s2)<(s2+s1);
}

class Solution {
public:
    string PrintMinNumber(vector<int> &numbers) {
        vector<string>v;
        char cs[16];
        for(int i=0;i<numbers.size();i++)
        {
            for(int j=0;j<16;j++)
                cs[j]=0;
            sprintf(cs,"%d",numbers[i]);
            string s(cs);
            v.push_back(s);
        }
        sort(v.begin(),v.end(),cmp);
        string res;
        for(auto e:v)
            res.append(e);
        return res;
    }



};



int main()
{
    cout << "Input array size n and its numbers:" << endl;
    int n;
    cin>>n;
    vector<int> v;
    for(int i=0;i<n;i++)
    {
        int tmp;
        cin>>tmp;
        v.push_back(tmp);
    }
    Solution Solu;
    string res=Solu.PrintMinNumber(v);
    cout<<"s= "<<res<<endl;
    return 0;
}
