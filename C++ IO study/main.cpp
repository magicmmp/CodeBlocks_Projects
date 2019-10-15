#include <iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int main()
{

    ifstream ifile("tiger0_cfg_log.txt");  /*���ļ�*/
    if(!ifile)
    {
        cerr<<"cannot open file."<<endl;
        return -1;
    }
    string line;
    vector<string> words;
    while(getline(ifile,line)) /*���ļ���һ��*/
    {
        words.push_back(line);
    }
    ifile.close();  /*�ر��ļ�*/
    for(auto e:words)  /*print vector*/
        cout<< e <<endl;

    return 0;
}
