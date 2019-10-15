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
    cout<<"条款17  以独立语句将newed（被申请的）对象置入智能指针："<<endl;
    cout<<"不要这样使用智能指针：fb(shared_ptr<widget>ptr(new widget), fa());"<<endl;
    cout<<"因为这样有可能造成内存泄漏。详见书中 P76。"<<endl;
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
    shared_ptr<widget>ptr(new widget);  /*正确做法，以独立语句将newed（被申请的）对象置入智能指针*/
    fb(ptr,fa());
    return 0;
}
