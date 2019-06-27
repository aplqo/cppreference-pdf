#ifndef LINK_H
#define LINK_H

#include"list.h"
#include<filesystem>

namespace doc
{
    class link : public list
    {
    public:
        link(const std::filesystem::path &p);
        link(std::list<std::filesystem::path>::iterator i);
        void Read();
        bool Check();
        void Release();
        ~link();
    };
};

#endif
