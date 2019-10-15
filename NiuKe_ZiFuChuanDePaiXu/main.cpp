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
        sort(res.begin(),res.end());/*先排序*/
        auto it=unique(res.begin(),res.end());/*把相邻重复元素搬到后面，返回第一个重复元素的迭代器*/
        res.erase(it,res.end()); /*删除重复元素*/
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
                /*改回来以便进行下一次循环*/
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



















