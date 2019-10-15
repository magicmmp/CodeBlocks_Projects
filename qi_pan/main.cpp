#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<string> v;
    int N;
    int M;
    cin>>N>>M;
    for(int i=0;i<N;i++)
    {
        string s;
        cin>>s;
        v.push_back(s);
    }
    int o_num;
    int w;
    int x; //position of x.
    for(int k=0;k<M;k++)
    {

        w=0;
        x=-1;
        int i=0;
        o_num=0;
        while(i<N)
        {
            if(v[i][k]=='x')
            {
                x=i;
                for(int j=x-1;j>x-1-o_num;j--)
                    v[j][k]='o';
                for(int j=x-1-o_num;j>=w;j--)
                    v[j][k]='.';
                o_num=0;
            }
            else if(v[i][k]=='o')
            {
                if(i-1>=0 && v[i-1][k]=='x')
                    w=i;
                o_num++;
            }
            else
            {
                if(i-1>=0 && v[i-1][k]=='x')
                    w=i;
            }
            i++;
        }

        int xx=N-1;
        while(v[xx][k]!='x')
        {
            v[xx][k]='.';
            xx--;
            if(xx<0)
                break;
        }

    }
    cout<<"The sesult:"<<endl;
    for(auto e:v)
        cout<<e<<endl;


}
