#ifndef QUICK_SORT_H_INCLUDED
#define QUICK_SORT_H_INCLUDED
void quicksort(int*a,int left,int right)
{
    if(left>=right)
        return;
    int base;
    base=a[left];
    int i,j;
    i=left;
    j=right;
    while(i<j)
    {
        while(i<j&&a[j]>=base)
            j--;
        a[i]=a[j];
        while(i<j&&a[i]<=base)
            i++;
        a[j]=a[i];
    }
    a[i]=base;
    quicksort(a,left,i-1);
    quicksort(a,i+1,right);
}





#endif // QUICK_SORT_H_INCLUDED
