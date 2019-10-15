#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Solution {
public:
    void Permutation(string str) {
        vector<string> res;
        f(str,0,res);
        sort(res.begin(),res.end());/*������*/
        auto it=unique(res.begin(),res.end());/*�������ظ�Ԫ�ذᵽ���棬���ص�һ���ظ�Ԫ�صĵ�����*/
        res.erase(it,res.end()); /*ɾ���ظ�Ԫ��*/
        for(auto e:res)
            cout<<e<<endl;
    }
private:
    void f(string &str,int pos,vector<string>&res)
    {
        if(pos==str.size()-1)
        {
            res.push_back(str);
        }
        else
        {
            for(int i=pos;i<str.size();i++)
            {
                char tmp=str[i];
                str[i]=str[pos];
                str[pos]=tmp;
                /**/
                f(str,pos+1,res);
                /*�Ļ����Ա������һ��ѭ��*/
                tmp=str[i];
                str[i]=str[pos];
                str[pos]=tmp;
            }
        }
    }

};

int main()
{
    string s;
    cout<<"Input a string :"<<endl;
    cin>>s;
    Solution S;
    cout<<endl<<"The result"<<endl;
    S.Permutation(s);

    return 0;




}



















