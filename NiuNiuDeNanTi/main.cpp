#include <iostream>

using namespace std;

int main()
{
    int t;
    cin>>t;
    for(int z=0;z<t;z++)
    {
        int A,B,C;
        cin>>A>>B>>C;
        int c=A%B;
        int a=A;
        bool flag=false;
        while(!flag)
        {
            if(a%B==C)
                flag=true;
            a=a+A;
            if(a%B==c)
                break;
        }
        if(flag)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }





    return 0;
}
