#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main()
{
    stack <int>stk;//��ջ
    for(int i=0;i<10;i++)
    {
      stk.push(i+1);
    }
    cout<<"ջ�Ĵ�С:"<<stk.size()<<endl;
    while(!stk.empty())
    {
        cout<<stk.top()<<" ";
        stk.pop();
    }
    cout<<endl;
    cout<<"ջ�Ĵ�С:"<<stk.size()<<endl;

   queue<int> q;
   for(int i=0;i<10;i++)
    {
      q.push(i+1);
    }
    cout<<"��βԪ��:"<<q.back()<<endl;
    cout<<"���еĴ�С:"<<q.size()<<endl;
    while(!q.empty())
    {
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;
    cout<<"���еĴ�С:"<<q.size()<<endl;
    string s="asdfghz";
    for(auto c:s)
        cout<<c<<" ";
    cout<<endl;

    return 0;
}
