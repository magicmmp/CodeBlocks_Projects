#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total;
        total=nums1.size()+nums2.size();
        if(total&0x1)
            return find_kth(nums1,0,nums2,0,total/2+1);
        else
        {
            double a,b;
            a=find_kth(nums1,0,nums2,0,total/2);
            b=find_kth(nums1,0,nums2,0,total/2+1);
            cout<<"a="<<a<<", b="<<b<<endl;
            return (a+b)/2.0;
        }
    }
private:
    int find_kth(vector<int>& num1,int m, vector<int>& num2,int n,int k)
    {
        if((int(num1.size())-m)>(int(num2.size())-n))
            return find_kth(num2,n,num1,m,k);
        if(int(num1.size())==m)
            return num2[n+k-1];
        if(k==1 )
            return min(num1[m],num2[n]);
        int ka,kb;
        ka=min(k/2,(int(num1.size())-m));kb=k-ka;
        if(num1[m+ka-1]<num2[n+kb-1])
            return find_kth(num1,m+ka,num2,n,k-ka);
        else if(num1[m+ka-1]>num2[n+kb-1])
            return find_kth(num1,m,num2,n+kb,k-kb);
        else
            return num1[m+ka-1];
    }
};



int main()
{   vector<int> v1;
    vector<int> v2;
//    v1.push_back(1);
    v1.push_back(2);
    v2.push_back(3);
    Solution s;
    cout << "M_num="<<s.findMedianSortedArrays(v1,v2) << endl;
    return 0;
}
