#ifndef LOG_H
#define LOG_H

#include "../include/list.h"
#include <iostream>

namespace doc
{
    void info(const char* msg);
    void error(const char* msg);
    void warning(const char* msg);
    void log(list& l, const char* file, const char* out);
}
#endif
