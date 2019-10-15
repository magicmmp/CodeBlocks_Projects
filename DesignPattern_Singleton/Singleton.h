#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include <iostream>

using namespace std;

class Singleton
{
public:
    static Singleton* Instance(int i); /*如果对象不存在，就创建一个*/
    ~Singleton();
    int x;
protected:
    Singleton(int i);
private:
    static Singleton* _instance; /*指向唯一的对象的指针*/
};




#endif // SINGLETON_H_INCLUDED
