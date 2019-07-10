#include<filesystem>
#include<iostream>
#include<fstream>
#include<string>
#include"../include/list.h"
#include"../include/filelist.h"
#include"../include/link.h"
#include"../include/log.h"
#include"../include/pdf.h"

using std::filesystem::path;
using std::filesystem::exists;
using std::cout;
using std::endl;
using std::ios;
using std::string;
using std::ofstream;

namespace doc
{
    inline void usage()
    {
        cout<<"usage: doc [firstfile] [outputfile]"<<endl;
        cout<<"Convert cppreference doc to pdf"<<endl;
    }
    //callback for log
    void cb_log(const path &p,void *par)
    {
        ofstream *o=reinterpret_cast<ofstream*>(par);
        (*o)<<p<<endl;
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
int main(int argc,char *argv[])
{
    if (argc < 3)
    {
        doc::usage();
        return 0;
    }
    path first(argv[1]);
    if (!exists(first))
    {
        doc::error("Can't find first file");
        return -1;
    }

    doc::info("Generating link list...");
    doc::link lnk(first);
    lnk.Read();
    while (!lnk.Check())
        ;
    doc::log(lnk, "links.log",argv[2]);

    doc::info("Checking if every file is included...");
    {
        doc::filelist flist(first);
        doc::log(flist, "filelist.log",argv[2]);
        doc::list diff;
        lnk.Compare(flist, &diff);
        {
            path p=(path(argv[2]).parent_path())/"ignore.txt";
            if (exists(p))
            {
                doc::filelist ign(p.c_str());
                diff.Remove(ign);
            }
            else
            {
                doc::warning("Can't find ignore.txt");
            }
        }
        if (!diff.isEmpty())
        {
            doc::error("These file aren't included:");
            auto cb = [](const path &p, void *par) { cout << "\t" << p << endl; };
            diff.Apply(cb, nullptr);
            return -1;
        }
    }

    doc::pdf(lnk, argv[2]);
    return 0;
}
