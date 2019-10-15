#include <iostream>
using namespace std;
namespace folder_1
{
    int a;
    int b;
    void fun()
    {
        cout<<"我是命名空间 folder_1 的函数fun。"<<endl;
    }
}
namespace folder_2
{
    int a;
    int b;
    void fun()
    {
        cout<<"我是命名空间 folder_2 的函数fun。"<<endl;
    }
}

/*
（1）命名空间用于解决命名冲突。
（2）一个命名空间里可以有变量，函数，类等成员。
（3）不同命名空间可以有相同的名称。命名空间的作用就像文件夹：不同文件夹可以有同名文件，
     而同一个文件夹则不能有同名文件。
*/

int main()
{
    namespace f1=folder_1;  /*给命名空间起个简短的别名*/
    f1::a=1;
    cout<<"f1::a= "<<f1::a<<endl;
    f1::fun();

    namespace f2=folder_2;
    f2::a=2;
    cout<<"f2::a= "<<f2::a<<endl;
    f2::fun();

    return 0;
}
