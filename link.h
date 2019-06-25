#ifndef LINK_H
#define LINK_H

#include"list.h"
#include<experimental/filesystem>

using std::experimental::filesystem::path;

namespace doc
{
    class link : public list
    {
    public:
        link(const path &p);
        link(std::list<path>::iterator i);
        void Read();
        bool Check();
        void Release();
        ~link();
    };
};

#endif