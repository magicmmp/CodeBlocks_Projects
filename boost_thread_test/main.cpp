#include <iostream>
#include <boost/timer.hpp>
#include "D:/CodeBlocks_Project/Include_Self_Defined_Libs_test/Include_files_test.h"
using namespace boost;
using namespace std;


int main()
{
    timer t;
    PP p;
    p.print_hello();
    cout <<"min time span: "<<t.elapsed_min()<<endl;
    return 0;
}
