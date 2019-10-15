#include <iostream>

using namespace std;
class base
{
public:
    base(string st,int i):name(st),age(i)
    {
        cout<<"调用了基类的构造函数。"<<endl;
    }

    base(const base&rhs):name(rhs.name),age(rhs.age)
    {
        cout<<"调用了基类的复制构造函数。"<<endl;
    }

    void print()
    {
        cout<<"base.name= "<<name<<" ,base.age= "<<age<<endl;
    }
protected:
    string name;  /*如果name是private，则派生类不再有这个成员变量*/
    int age;
};

class deriv:public base
{
public:
    deriv(string st,int i,string colr):base(st,i),color(colr)
    {
        cout<<"调用了派生类的构造函数。"<<endl;
    }
    /*故意不调用基类的复制构造函数，看看会怎样复制*/

    deriv(const deriv& rhs):base(rhs),color(rhs.color)
    {
        cout<<"调用了派生类的复制构造函数。"<<endl;
    }

    void print()
    {
        cout<<"deriv.name= "<<name<<" ,deriv.age= "<<age<<" ,deriv.color= "<<color<<endl;
    }
private:
    string color;
};
/*
经过测试，可知：
（1）如果基类自定义了copy函数，则派生类的copy函数也要调用它们，
     以初始化基类部分成员变量。如果基类没有定义，则不用。
（2）这里的copy函数是指：复制构造函数和赋值复制函数（重载=）。
     当自定义它们时，要确保考虑到每个成员变量的复制，否则，被遗忘的变量将不会被正确复制。
*/

int main()
{
    base b1("爸爸",5);
    base b2(b1);
    deriv d1("儿子",3,"黄皮肤");
    deriv d2(d1);
    b1.print();
    b2.print();
    d1.print();
    d2.print();
    return 0;
}
