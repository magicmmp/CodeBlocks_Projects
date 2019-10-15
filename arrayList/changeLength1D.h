#ifndef CHANGELENGTH1D_H_INCLUDED
#define CHANGELENGTH1D_H_INCLUDED
#include "myExceptions.h"

using namespace std;

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
   if (newLength < 0)
      throw illegalParameterValue("new length must be >= 0");

   T* temp = new T[newLength];              // new array
   int number = min(oldLength, newLength);  // number to copy
   copy(a, a + number, temp);
   delete [] a;                             // deallocate old memory
   a = temp;
}



#endif // CHANGELENGTH1D_H_INCLUDED
