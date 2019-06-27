#ifndef PARSE_H
#define PARSE_H

#include<list>
#include<filesystem>

namespace doc
{
    void parse(const char *filename,std::list<std::filesystem::path> *result);
};

#endif
