#include "Singleton.h"
#include <iostream>

using namespace std;

Singleton* Singleton::_instance = 0;

Singleton::Singleton(int i)
{
    x=i;
    cout<<"Singleton...."<<endl;
}
Singleton::~Singleton()
{
    delete _instance;
}

Singleton* Singleton::Instance(int i)
{
    if (_instance == 0)
    {
        _instance = new Singleton(i);
    }
    return _instance;
}
