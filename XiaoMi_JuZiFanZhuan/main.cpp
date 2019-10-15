#include <iostream>
#include<string>
#include<stack>
#include<sstream>

using namespace std;

int main()
{
    stack<string>st;
    string s;
   while(getline(cin,s)) /*读入一行,循环是不会停的*/
 {
    istringstream in(s); /*从字符串读入到in*/
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
