#include <iostream>
using namespace std;
namespace folder_1
{
    int a;
    int b;
    void fun()
    {
        cout<<"���������ռ� folder_1 �ĺ���fun��"<<endl;
    }
}
namespace folder_2
{
    int a;
    int b;
    void fun()
    {
        cout<<"���������ռ� folder_2 �ĺ���fun��"<<endl;
    }
}

/*
��1�������ռ����ڽ��������ͻ��
��2��һ�������ռ�������б�������������ȳ�Ա��
��3����ͬ�����ռ��������ͬ�����ơ������ռ�����þ����ļ��У���ͬ�ļ��п�����ͬ���ļ���
     ��ͬһ���ļ���������ͬ���ļ���
*/

int main()
{
    namespace f1=folder_1;  /*�������ռ������̵ı���*/
    f1::a=1;
    cout<<"f1::a= "<<f1::a<<endl;
    f1::fun();

    namespace f2=folder_2;
    f2::a=2;
    cout<<"f2::a= "<<f2::a<<endl;
    f2::fun();

    return 0;
}
