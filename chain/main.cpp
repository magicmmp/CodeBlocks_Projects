#include <iostream>
#include <vector>
using namespace std;


int main()
{   int i;
    const int n=100;
    bool f[n][n];
    vector<int> vec;
    for(i=0;i<10;i++)
        vec.push_back(i+1);
    cout<<vec[2]<<endl;
    cout << "&f[0][0]="<<&f[0][0]<<" f="<<f<< endl;
    return 0;
}
