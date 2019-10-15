#include <iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int main()
{

    ifstream ifile("tiger0_cfg_log.txt");  /*打开文件*/
    if(!ifile)
    {
        cerr<<"cannot open file."<<endl;
        return -1;
    }
    string line;
    vector<string> words;
    while(getline(ifile,line)) /*从文件读一行*/
    {
        words.push_back(line);
    }
    ifile.close();  /*关闭文件*/
    for(auto e:words)  /*print vector*/
        cout<< e <<endl;

    return 0;
}
