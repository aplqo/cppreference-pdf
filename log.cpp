#include<iostream>

using std::cout;
using std::endl;

namespace doc
{
    inline void info(const char *msg)
    {
        cout<<""<<msg<<endl;
    }
    inline void warning(const char *msg)
    {
        cout<<""<<msg<<endl;
    }
    inline void error(const char *msg)
    {
        cout<<""<<msg<<endl;
    }
}