#include<iostream>
#include<filesystem>
#include"../include/list.h"
#include"debug.h"

using std::cout;
using std::endl;
using std::ostream;
using std::filesystem::path;

namespace doc
{
    ostream& operator<<(ostream &os,list &o)
    {
      debug("List output:","");
      auto cb=[](const path &p,void *par){
        ostream &os=*(reinterpret_cast<ostream*>(par));
        os<<"\t"<<p<<endl;
      };
      o.Apply(cb,&os);
      return os;
    }
}
