#include "../include/filelist.h"
#include "../include/list.h"
#include <filesystem>
#include <fstream>
#include <string>

using std::getline;
using std::ifstream;
using std::string;
namespace fs = std::filesystem;
using fs::absolute;
using fs::canonical;
using fs::current_path;
using fs::directory_entry;
using fs::is_regular_file;
using fs::path;
using fs::recursive_directory_iterator;

namespace doc
{
    filelist::filelist(const path& p)
    {
        lst = new std::list<path>;
        isBase = false;
        if (is_regular_file(p))
        {
            lst->push_back(p);
        }

        path tmp = (p.parent_path()) / (p.stem());
        recursive_directory_iterator dir(tmp);
        for (auto& i : dir)
        {
            if (is_regular_file(i))
            {
                lst->push_back(toAbsolute(i.path()));
            }
        }
    }
    filelist::filelist(const char* file)
    {
        ifstream i;
        i.open(file);
        if (!i.is_open())
        {
            return;
        }
        lst = new std::list<path>;
        isBase = false;
        string tmp;
        while (!i.eof())
        {
            getline(i, tmp);
            if (!tmp.empty())
            {
                lst->push_back(toAbsolute(path(tmp.c_str())));
            }
            tmp.clear();
        }
    }
    filelist::~filelist()
    {
        delete lst;
    }
    inline path filelist::toAbsolute(const path& p)
    {
        path res;
        res = absolute(p);
        res = canonical(res);
        return res;
    }
}
