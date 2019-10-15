#include <iostream>
#include<unordered_set>
using namespace std;

int main()
{
    int N;
    cin>>N;
    int res=0;
    int d=0;
    unordered_set<pair<int,int>>st;
    for(int a=1;a<N;a++)
    {
        for(int b=a;b<N;b++)
        {
            for(int c=b+1;c<=N;c++)
            {
                if(a*a+b*b==c*c)
                {
                    res++;



                }
            }
        }
    }
    cout<<res;
    return 0;
}
