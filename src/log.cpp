#include<iostream>

using std::cout;
using std::endl;

namespace doc
{
    void info(const char *msg)
    {
        cout<<"\033[36m"<<"[INFO]"<<msg<<"\033[0m"<<endl; //blue
    }
    void warning(const char *msg)
    {
        cout<<"\033[33m"<<"[WARN]"<<msg<<"\033[0m"<<endl;
    }
    void error(const char *msg)
    {
        cout<<"\033[31m"<<"[ERROR]"<<msg<<"\033[0m"<<endl;
    }
}
