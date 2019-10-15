#include <iostream>
#include<ctime>
#include "Straight_Insertion_Sort.h"
#include "binary_insertion_sort.h"
#include "quick_sort.h"
#include "shell_sort.h"
#include "srand.h"
const int len = 50;
using namespace std;

void print(int a[], int len)
{
    int i;
    for (i = 0; i < len; i++)
      cout<<a[i]<<" ";
    cout<<endl;
}

int main()
{
    int a[len];
    clock_t start,finish;

    random(a,len);
    cout <<"straight_insertion_sort,before sort:"<<endl;
 //   print(a,len);
    start=clock();
    straight_insertion_sort(a,0,len-1);
    finish=clock();
    cout <<"after sort:"<<endl;
//    print(a,len);
    cout << "start="<<start<<",finish="<<finish<<","<<finish-start<< "/" << CLOCKS_PER_SEC  << " (s) "<< endl;

    random(a,len);
    cout <<"binary_insertion_sort,before sort:"<<endl;
//    print(a,len);
    start=clock();
    binary_insertion_sort(a,0,len-1);
    finish=clock();
    cout <<"after sort:"<<endl;
    cout << "start="<<start<<",finish="<<finish<<","<<finish-start<< "/" << CLOCKS_PER_SEC  << " (s) "<< endl;
 //   print(a,len);

    random(a,len);
    cout <<"quicksort,before sort:"<<endl;
//    print(a,len);
    start=clock();
    quicksort(a,0,len-1);
    finish=clock();
    cout <<"after sort:"<<endl;
    cout << "start="<<start<<",finish="<<finish<<","<<finish-start<< "/" << CLOCKS_PER_SEC  << " (s) "<< endl;
//    print(a,len);

    random(a,len);
    cout <<"shellsort,before sort:"<<endl;
    print(a,len);
    start=clock();
    shell(a,len);
    finish=clock();
    cout <<"after sort:"<<endl;
    cout << "start="<<start<<",finish="<<finish<<","<<finish-start<< "/" << CLOCKS_PER_SEC  << " (s) "<< endl;
    print(a,len);

    return 0;
}
