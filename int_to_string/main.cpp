#include <iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
    string s;
    int n;
    char cs[16];
    cin>>n;

    cout << "int to string :" << endl;
    sprintf(cs,"%d",n);
    cs[5]=0;
    s=cs;
    cout<<"c_string= "<<s<<endl;

    cout << "string to int :" << endl;
    n=0;
    n=atoi(cs);
    cout<<"n= "<<n<<endl;
    return 0;
}
