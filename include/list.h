#ifndef LIST_H
#define LIST_H

#include <filesystem>
#include <list>
namespace doc
{
    class list
    {
    public:
        list();
        void Compare(const list& l, list* result) const;
        void Remove(const list& l);
        bool isEmpty() const;
        void Apply(void func(const std::filesystem::path& p, void* par), void* par) const;
        ~list();

    protected:
        bool find(const std::filesystem::path& p) const;
        std::list<std::filesystem::path>* lst;
        bool isBase;
    };
}

#endif
