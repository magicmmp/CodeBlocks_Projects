#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int main()
{
    stack <int>stk;//入栈
    for(int i=0;i<10;i++)
    {
      stk.push(i+1);
    }
    cout<<"栈的大小:"<<stk.size()<<endl;
    while(!stk.empty())
    {
        cout<<stk.top()<<" ";
        stk.pop();
    }
    cout<<endl;
    cout<<"栈的大小:"<<stk.size()<<endl;

   queue<int> q;
   for(int i=0;i<10;i++)
    {
      q.push(i+1);
    }
    cout<<"队尾元素:"<<q.back()<<endl;
    cout<<"队列的大小:"<<q.size()<<endl;
    while(!q.empty())
    {
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;
    cout<<"队列的大小:"<<q.size()<<endl;
    string s="asdfghz";
    for(auto c:s)
        cout<<c<<" ";
    cout<<endl;

    return 0;
}
