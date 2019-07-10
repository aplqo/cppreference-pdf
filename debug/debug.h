#ifndef DEBUG_H
#define DEBUG_H

#include<iostream>
#include"../include/list.h"

namespace doc
{
    std::ostream& operator<<(std::ostream &os,list &o);
    template<class T>
    void debug(const char *msg,const T &obj)
    {
      std::cout<<"\033[32m"<<"[DEBUG]"<<msg<<obj<<"\033[0m"<<std::endl;
    }
    template<typename T>
    std::ostream& operator<<(std::ostream &os,const std::list<T> &o)
    {
      debug("std::list output:","");
      for(const auto &i: o)
      {
        std::cout<<"\t"<<i<<std::endl;
      }
      return os;
    }
}
#endif
