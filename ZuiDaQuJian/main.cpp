#include <iostream>
#include<vector>
using namespace std;

int main()
{
    cout << "Input n and an array:" << endl;
    int n;
    cin>>n;
    vector<int>arr(n);
    int res=0,lf,rh,sum;
    int tmp;
    for(int i=0;i<n;i++)
        cin>>arr[i];
    for(int i=0;i<arr.size();i++)
    {
        sum=arr[i];
        lf=i;
        while(lf-1>=0&&arr[lf-1]>=arr[i])
        {
            lf--;
            sum=sum+arr[lf];
        }

        rh=i;
        while(rh+1<arr.size()&&arr[rh+1]>=arr[i])
            {
                rh++;
                sum=sum+arr[rh];
            }
        tmp=sum*arr[i];
        if(res<tmp)
            res=tmp;
    }
    cout<<res<<endl;



    return 0;
}
