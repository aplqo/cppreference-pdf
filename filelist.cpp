#include"list.h"
#include<fstream>
#include<string>
#include<filesystem>

using std::ifstream;
using std::getline;
using std::string;
namespace fs=std::filesystem;
using fs::path;
using fs::directory_entry;
using fs::recursive_directory_iterator;
using fs::is_regular_file;

namespace doc
{
    class filelist:public list
    {
        public:
        filelist(const path &p);
        filelist(const char * file);
        ~filelist();
    };
    filelist::filelist(const path &p)
    {
        lst=new std::list<path>;
        isBase=false;
        if(is_regular_file(p))
        {
            lst->push_back(p);
        }
        
        path tmp=(p.parent_path())/(p.filename());
        recursive_directory_iterator dir(tmp);
        for(auto &i :dir)
        {
            if(is_regular_file(i))
            {
                lst->push_back(i.path());
            }
        }
    }
    filelist::filelist(const char *file)
    {
        ifstream i;
        i.open(file);
        if(!i.is_open())
        {
            return;
        }
        lst=new std::list<path>;
        isBase=false;
        string tmp;
        while(!i.eof())
        {
            getline(i,tmp);
            if(!tmp.empty())
            {
                lst->push_back(path(tmp));
            }
            tmp.clear();
        }
    }
    filelist::~filelist()
    {
        delete lst;
    }
}
