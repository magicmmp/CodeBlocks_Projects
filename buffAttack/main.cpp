#include<iostream>

using namespace std;

int main()
{
    int HP;
    int bf;
    int nr;
    int n=0;
    std::cin>>HP;
    std::cin>>nr;
    std::cin>>bf;
    if(nr*2<bf)
    {
        n=HP/bf;
        n=n*2;
        HP=HP%bf;
        if(HP)
        if(HP>nr)
            n=n+2;
        else
            n=n+1;
    }
    else
    {
        n=HP/nr;
        HP=HP%nr;
        if(HP)
            n++;
    }
    cout<<n<<endl;


}
