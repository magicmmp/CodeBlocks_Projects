#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<int>s1;
    set<int> s2;
    s1.insert(1);
    for(int i=2;i<10;i++)
        s2.insert(i);
    cout<<"s1:"<<endl;
    for(auto e:s1)
        cout << e<<" ";
    cout<<endl;

    cout<<"s2:"<<endl;
    for(auto e:s2)
        cout << e<<" ";
    cout<<endl;
    s1.insert(s2.begin(),s2.end());
    cout<<"afetr add s2, s1="<<endl;
    for(auto e:s1)
        cout << e<<" ";
    cout<<endl;

    return 0;
}
