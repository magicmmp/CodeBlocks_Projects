#include <iostream>
#include<string>
using namespace std;

int main()
{
    string s,t;
    s="asdfgtyhhj";
    t="dfgts";
    unsigned int npo=s.find(t);
    if(npo==string::npos)
        cout<<"û�ҵ���"<<endl;
    else
        cout <<s<<".find("<<t<< ")= "<<s.find(t) << endl;
    return 0;
}
