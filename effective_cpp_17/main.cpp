#include <iostream>
#include<memory>
using namespace std;
struct widget
{
    widget(string s0="abcdef",int n0=8):s(s0),num(n0){}
    string s;
    int num;
};

int fa()
{
    cout<<"����17  �Զ�����佫newed��������ģ�������������ָ�룺"<<endl;
    cout<<"��Ҫ����ʹ������ָ�룺fb(shared_ptr<widget>ptr(new widget), fa());"<<endl;
    cout<<"��Ϊ�����п�������ڴ�й©��������� P76��"<<endl;
    return 2;
}

void fb(shared_ptr<widget>ptr,int x)
{
    cout<<"ptr->s = "<<ptr->s<<endl;
    cout<<"ptr->num = "<<ptr->num<<endl;
    cout<<"fa() = "<<x<<endl;
}


int main()
{
    shared_ptr<widget>ptr(new widget);  /*��ȷ�������Զ�����佫newed��������ģ�������������ָ��*/
    fb(ptr,fa());
    return 0;
}
