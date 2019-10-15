#include <iostream>

using namespace std;
class base
{
public:
    base(string st,int i):name(st),age(i)
    {
        cout<<"�����˻���Ĺ��캯����"<<endl;
    }

    base(const base&rhs):name(rhs.name),age(rhs.age)
    {
        cout<<"�����˻���ĸ��ƹ��캯����"<<endl;
    }

    void print()
    {
        cout<<"base.name= "<<name<<" ,base.age= "<<age<<endl;
    }
protected:
    string name;  /*���name��private���������಻���������Ա����*/
    int age;
};

class deriv:public base
{
public:
    deriv(string st,int i,string colr):base(st,i),color(colr)
    {
        cout<<"������������Ĺ��캯����"<<endl;
    }
    /*���ⲻ���û���ĸ��ƹ��캯������������������*/

    deriv(const deriv& rhs):base(rhs),color(rhs.color)
    {
        cout<<"������������ĸ��ƹ��캯����"<<endl;
    }

    void print()
    {
        cout<<"deriv.name= "<<name<<" ,deriv.age= "<<age<<" ,deriv.color= "<<color<<endl;
    }
private:
    string color;
};
/*
�������ԣ���֪��
��1����������Զ�����copy���������������copy����ҲҪ�������ǣ�
     �Գ�ʼ�����ಿ�ֳ�Ա�������������û�ж��壬���á�
��2�������copy������ָ�����ƹ��캯���͸�ֵ���ƺ���������=����
     ���Զ�������ʱ��Ҫȷ�����ǵ�ÿ����Ա�����ĸ��ƣ����򣬱������ı��������ᱻ��ȷ���ơ�
*/

int main()
{
    base b1("�ְ�",5);
    base b2(b1);
    deriv d1("����",3,"��Ƥ��");
    deriv d2(d1);
    b1.print();
    b2.print();
    d1.print();
    d2.print();
    return 0;
}
