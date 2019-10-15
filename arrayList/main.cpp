#include "arrayListWithIterator.h"




using namespace std;

int main()
{
    arrayList<int> arr;
    for(int i=0;i<100;i++)
    arr.insert(i,i*2);
    cout << "arr : "<<arr << endl;
    for(auto it=arr.begin();it!=arr.end();it++)
       cout << "*it=  "<<*it << endl;
    return 0;
}
