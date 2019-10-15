#include "Singleton.h"
#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    Singleton* sgn = Singleton::Instance(8);
    cout<<"Singleton Pattern,  sgn->x = "<<sgn->x<<endl;
    return 0;
}
