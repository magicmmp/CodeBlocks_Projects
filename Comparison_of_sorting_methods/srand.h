#ifndef SRAND_H_INCLUDED
#define SRAND_H_INCLUDED
#include <stdlib.h>
#include <time.h>
void random(int a[],int n)
{
    int i=0;
    srand( (unsigned)time( NULL ) );
    while(i<n)
    {
       a[i++]=rand();
    }
}



#endif // SRAND_H_INCLUDED
