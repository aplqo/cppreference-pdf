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
      private:
        inline std::filesystem::path toAbsolute(const std::filesystem::path &p);
        inline bool isFirst(const std::filesystem::path &p); // check if a file should be
                                            // included in the first time
        /*---var---*/
        std::list<std::filesystem::path> *links;

        static link *root;
        std::list<link> child;

        std::list<std::filesystem::path>::iterator it;
    };
};

#endif
