#include <iostream>
#include<string>
#include<stack>
#include<sstream>

using namespace std;

int main()
{
    stack<string>st;
    string s;
   while(getline(cin,s)) /*����һ��,ѭ���ǲ���ͣ��*/
 {
    istringstream in(s); /*���ַ������뵽in*/
    string tmp;
    while(in>>tmp)
        st.push(tmp);
    while(!st.empty())
    {
        cout<<st.top()<<' ';
        st.pop();
    }
    cout<<endl;
 }


    return 0;
}
