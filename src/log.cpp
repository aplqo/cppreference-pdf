#include"../include/log.h"
#include<fstream>
#include<filesystem>

using std::cout;
using std::endl;
using std::filesystem::path;
using std::ofstream;
using std::ios;

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
    //callback for log
    void cb_log(const path &p,void *par)
    {
        ofstream *o=reinterpret_cast<ofstream*>(par);
        (*o)<<p.c_str()<<endl;
    }
    void log(list &l,const char *file,const char* out)
    {
        path o_path=(path(out).parent_path())/path(file);
        ofstream o(o_path.c_str(),ios::out);
        if(!o.is_open()) return;
        l.Apply(cb_log,&o);
        o.close();
    }
}
