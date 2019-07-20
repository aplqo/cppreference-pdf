#include <filesystem>
#include <fstream>
#include <gq/Document.h>
#include <gq/Node.h>
#include <list>
#include <locale>
#include <sstream>
#include <string>

using std::ifstream;
using std::ios_base;
using std::locale;
using std::stoi;
using std::string;
using std::stringstream;
using std::filesystem::path;

namespace doc
{
    static const locale u8("en_US.UTF-8");
    static inline void read(const char* filename, string& s)
    {
        ifstream i(filename);
        i.seekg(2, ios_base::beg);
        if (!i.is_open())
        {
            return;
        }
        i.imbue(u8);
        stringstream buf;
        buf << i.rdbuf();
        s = buf.str();
    }
    static inline string arg(const string& s)
    {
        string::size_type pos = s.find('#');
        string::size_type pos2 = s.find('?');
        return (pos > pos2 ? s.substr(0, pos2) : s.substr(0, pos));
    }
    static inline void decode(string& url)
    {
        string::size_type pos, beg = 0;
        for (pos = url.find('%'); pos != string::npos; pos = url.find('%', beg))
        {
            string&& tmp = url.substr(pos + 1, 2);
            char&& i = static_cast<char>(stoi(tmp, nullptr, 16));
            url.replace(pos, 3, 1, i);
            beg = pos + 1;
        }
    }
    static void add(const string& str, void* par)
    {
        std::list<path>* l = reinterpret_cast<std::list<path>*>(par);
        string&& s = arg(str);
        decode(s);
        l->push_back(s);
    }
    static void get_link(CDocument& doc, const char* key, void func(const string& str, void* par), void* par)
    {
        CSelection s = doc.find(key);
        CSelection link = s.find("a");
        size_t num = link.nodeNum();
        for (size_t i = 0; i < num; i++)
        {
            CNode nod = link.nodeAt(i);
            string tmp = nod.attribute("href");
            if (!tmp.empty())
            {
                func(tmp, par);
            }
        }
    }
    void parse(const char* filename, std::list<path>* result)
    {
        std::list<path> all;
        std::list<path>::size_type exclude = 0;

        auto count = [](const string& str, void* par) -> void {
            std::list<path>::size_type& p = *reinterpret_cast<std::list<path>::size_type*>(par);
            p++;
        };

        string s;
        read(filename, s);
        CDocument d;
        d.parse(s);
        get_link(d, "a", add, &all);
        get_link(d, "div[id=\"contentSub\"]", count, &exclude);
        get_link(d, "div[class=\"t-navbar\"]", count, &exclude);
        auto all_num = all.size();
        auto it = all.begin();
        for (size_t i = 0; i < exclude; i++)
            it++;
        for (auto i = exclude; i < all_num; i++, it++)
        {
            result->push_back(*it);
        }
    }
}
