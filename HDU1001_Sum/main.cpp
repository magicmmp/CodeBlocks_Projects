#include <iostream>

using namespace std;

int main()
{
    int n;
    while(cin>>n)
    {
        int res=0;
        if(n%2)
            res=n*((n+1)>>1);
        else
            res=(n+1)*(n>>1);
        cout<<res<<endl<<endl;

    }
    return 0;
}
