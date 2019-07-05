#ifndef FILELIST_H
#define FILELIST_H

#include"list.h"
#include<filesystem>
namespace doc
{
    class filelist:public list
    {
        public:
        filelist(const std::filesystem::path &p);
        filelist(const char * file);
        ~filelist();
      private:
        inline std::filesystem::path toAbsolute(const std::filesystem::path &p);
    };
}

#endif
