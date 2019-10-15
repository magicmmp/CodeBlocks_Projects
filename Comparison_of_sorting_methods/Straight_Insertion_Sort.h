#ifndef STRAIGHT_INSERTION_SORT_H_INCLUDED
#define STRAIGHT_INSERTION_SORT_H_INCLUDED
void straight_insertion_sort(int *a, const int p1, const int p2)
{
    int i,j;
    int tmp;
    for(i=p1+1;i<=p2;i++)
    {
        tmp=a[i];
        for(j=i-1;j>=p1&&tmp<a[j];j--)
            a[j+1]=a[j];
        a[j+1]=tmp;
    }
}





#endif // STRAIGHT_INSERTION_SORT_H_INCLUDED
