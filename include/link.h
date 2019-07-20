#ifndef LINK_H
#define LINK_H

#include "../include/list.h"

namespace doc
{
    class link : public list
    {
    public:
        link(const std::filesystem::path& p);
        link(std::list<std::filesystem::path>::iterator i);
        void Read();
        bool Check();
        void Release();
        ~link();

    private:
        std::filesystem::path toAbsolute(const std::filesystem::path& p);
        bool isFirst(const std::filesystem::path& p); // check if a file should be
            // included in the first time
        bool isInScope(const std::filesystem::path& p); //check if file is in subdir of root file
        /*---var---*/
        std::list<std::filesystem::path>* links;

        static link* root;
        std::list<link> child;

        std::list<std::filesystem::path>::iterator it;
    };
    //insert a object after a iterator
    template <class T>
    typename std::list<T>::iterator ins(std::list<T>& lst, const typename std::list<T>::iterator pos, T obj)
    {
        auto i = pos;
        i++;
        return lst.insert(i, obj);
    }
};

#endif
