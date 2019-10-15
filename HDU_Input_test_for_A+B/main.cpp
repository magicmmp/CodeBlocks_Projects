#include <iostream>

using namespace std;

int main()
{
    int N;
    cin>>N;
    for(int i=0;i<N;i++)
    {
        int M;
        cin>>M;
        int sum=0;
        for(int j=0;j<M;j++)
        {
            int tmp;
            cin>>tmp;
            sum=sum+tmp;
        }
        cout<<sum<<endl;
        cout<<endl;
    }
    return 0;
}
