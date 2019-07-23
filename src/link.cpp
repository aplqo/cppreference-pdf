#include "../include/link.h"
#include "../include/parse.h"

namespace fs = std::filesystem;
using fs::absolute;
using fs::canonical;
using fs::current_path;
using fs::equivalent;
using fs::exists;
using fs::is_regular_file;
using fs::path;

namespace doc
{
    link* link::root = nullptr;
    link::link(const path& p)
    {
        root = this;
        this->isBase = false;
        links = nullptr;
        lst = new std::list<path>;
        lst->push_back(canonical(absolute(p)));
        it = lst->begin();
    }
    link::link(std::list<path>::iterator i)
    {
        links = nullptr;
        this->lst = root->lst;
        this->isBase = false;
        this->it = i;
    }
    void link::Read()
    {
        links = new std::list<path>;
        parse(it->c_str(), links);
        std::list<path>::iterator now = it;
        for (auto i = links->begin(); i != (links->end()); i++)
        {
            auto e = [l = this->links](std::list<path>::iterator pos) -> std::list<path>::iterator {
                auto j = pos;
                pos++;
                l->erase(j);
                pos--;
                return pos;
            };
            path p = toAbsolute(*i);
            if (!(exists(p) && is_regular_file(p)))
            {
                i = e(i);
                continue;
            }
            if (!isInScope(p))
            {
                i = e(i);
                continue;
            }
            if (find(p))
            {
                i = e(i);
                continue;
            }
            if (isFirst(p))
            {
                now = ins(*lst, now, p);
                child.push_back(now);
                continue;
            }
        }
        for (auto& i : child)
        {
            i.Read();
        }
    }
    bool link::Check()
    {
        bool result = true;
        std::list<path>::iterator now = it;
        std::list<link>::iterator c_now = child.begin();
        for (auto& j : *links)
        {
            path p = toAbsolute(j);
            if (!find(p))
            {
                now = ins(*lst, now, p);
                result = false;
                c_now = ins(child, c_now, link(now));
                c_now->Read();
            }
            now++;
            c_now++;
        }
        for (auto& i : child)
        {
            result &= i.Check();
        }
        return result;
    }
    void link::Release()
    {
        delete links;
        links = nullptr;
        child.clear();
    }
    link::~link()
    {
        delete links;
        if (root == this)
        {
            delete lst;
        }
    }
    path link::toAbsolute(const path& p)
    {
        path res;
        current_path(it->parent_path());
        res = absolute(p);
        if (exists(res))
        {
            res = canonical(res);
        }
        return res;
    }
    bool link::isFirst(const path& p)
    {
        path dir = (it->parent_path()) / (it->stem()) / (p.filename());
        if (exists(dir))
        {
            return equivalent(dir, p);
        }
        else
        {
            return false;
        }
    }
    bool link::isInScope(const path& p)
    {
        const path& dir = (root->it->parent_path()) / (root->it->stem());
        auto j = p.begin();
        for (const auto& i : dir)
        {
            if (i != *j)
            {
                return false;
            }
            j++;
        }
        return true;
    }
}
