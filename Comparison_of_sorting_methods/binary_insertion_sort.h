#ifndef BINARY_INSERTION_SORT_H_INCLUDED
#define BINARY_INSERTION_SORT_H_INCLUDED
void binary_insertion_sort(int *a, const int p1, const int p2)
{
    int i,j;
    int tmp;
    int left,right,mid;
    for(i=p1+1;i<=p2;i++)
    {
        tmp=a[i];
        left=p1;
        right=i-1;
        while(left<=right)
        {
            mid=(left+right)/2;
            if(a[mid]>tmp)
                right=mid-1;
            else
                left=mid+1;
        }
       for(j=i-1;j>=left;j--)
         a[j+1]=a[j];
        a[left]=tmp;
    }

}


#endif // BINARY_INSERTION_SORT_H_INCLUDED
