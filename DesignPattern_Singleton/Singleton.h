#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include <iostream>

using namespace std;

class Singleton
{
public:
    static Singleton* Instance(int i); /*������󲻴��ڣ��ʹ���һ��*/
    ~Singleton();
    int x;
protected:
    Singleton(int i);
private:
    static Singleton* _instance; /*ָ��Ψһ�Ķ����ָ��*/
};




#endif // SINGLETON_H_INCLUDED
