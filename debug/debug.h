#ifndef DEBUG_H
#define DEBUG_H

#include "../include/list.h"
#include <algorithm>
#include <iostream>

namespace doc
{
    std::ostream& operator<<(std::ostream& os, list& o);
    template <class T>
    void debug(const char* msg, const T& obj)
    {
        std::cout << "\033[32m"
                  << "[DEBUG]" << msg << obj << "\033[0m" << std::endl;
    }
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::list<T>& o)
    {
        debug("std::list output:", "");
        for (const auto& i : o)
        {
            std::cout << "\t" << i << std::endl;
        }
        return os;
    }
    template <typename T>
    bool operator==(const std::list<T>& fact, const std::list<T>& expect)
    {
        if (std::equal(fact.begin(), fact.end(), expect.begin()))
        {
            return true;
        }
        else
        {
            std::cout << "Expected:" << std::endl;
            std::for_each(expect.begin(), expect.end(), [](const T& a) { std::cout << "\t" << a << std::endl; });
            std::cout << "Actually:" << std::endl;
            std::for_each(fact.begin(), fact.end(), [](const T& a) { std::cout << "\t" << a << std::endl; });
            return false;
        }
    }
}
#endif
