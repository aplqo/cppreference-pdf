#include<filesystem>
#include<iostream>
#include<fstream>
#include<string>
#include"list.h"
#include"filelist.h"
#include"link.h"
#include"log.h"
#include"pdf.h"

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
    void log(list &l,const char *file)
    {
        ofstream o(file,ios::out);
        if(!o.is_open()) return;
        l.Apply(cb_log,&o);
        o.close();
    }
    int main(char *argv[],int argc)
    {
        if(argc<2)
        {
            usage();
            return 0;
        }
        path first(argv[1]);
        if(!exists(first))
        {
            error("Can't find first file");
            return -1;
        }

        info("Generating link list...");
        link lnk(first);
        lnk.Read();
        while(!lnk.Check());
        log(lnk,"links.log");
        
        info("Checking if every file is included...");
        {
            filelist flist(first);
            log(flist,"filelist.log");
            list diff;
            lnk.Compare(flist,&diff);
            {
                path p("ignore.txt");
                if(exists(p))
                {
                    filelist ign("ignore.txt");
                    diff.Remove(ign);
                }
                else
                {
                    warning("Can't find ignore.txt");
                }
            }
            if(!diff.isEmpty())
            {
                error("These file aren't included:");
                auto cb=[](const path &p,void *par){cout<<"\t"<<p<<endl;};
                diff.Apply(cb,nullptr);
                return -1;
            }
        }

        pdf(lnk,argv[2]);
        return 0;
    }
}