#ifndef FILELIST_H
#define FILELIST_H

#include"list.h"
#include<experimental/filesystem>
namespace doc
{
    class filelist:public list
    {
        public:
        filelist(const std::experimental::filesystem::path &p);
        filelist(const char * file);
        ~filelist();
    };
}

#endif