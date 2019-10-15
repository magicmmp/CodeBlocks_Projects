#include <iostream>
#include<string>
using namespace std;
 int maxlen(const string& s)
 {

        int i,j,k,len,maxlen,strlen;
        int offset;
        int flag;
        if(s.empty())
            maxlen=0;
        else
    {
        strlen=s.length();
        len=1;maxlen=1;
        for(i=0;i<strlen;i=i+offset)
      {

        if(len>1)
            len=len-1;
        else
            len=1;
        for(j=i+len;j<strlen;j++)
        {
            flag=1;
            for(k=i;k<j;k++)
            if(s[k]==s[j])
            {
                offset=k-i+1;
                j=strlen; k=j;flag=0;
            }

            if(flag)
            {
             len=len+1;
            }

         }
            if(maxlen<len)
                maxlen=len;
            len=len-offset;
       }
    }
        return maxlen;
    }
int main()
{
    string s;
    while(cin>>s)
    cout<<s<<" 的不重复字串最大长度= "<<maxlen(s)<<endl;
    return 0;
}
