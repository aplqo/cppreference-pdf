#include<iostream>

using std::cout;
using std::endl;

namespace doc
{
    inline void info(const char *msg)
    {
        cout<<"\033[33m"<<msg<<"\033[0m"<<endl; //blue
    }
    inline void warning(const char *msg)
    {
        cout<<"\033[33m"<<msg<<"\033[0m"<<endl;
    }
    inline void error(const char *msg)
    {
        cout<<"\033[31m"<<msg<<"\033[0m"<<endl;
    }
}