#ifndef PARSE_H
#define PARSE_H

#include<list>
#include<experimental/filesystem>

namespace doc
{
    void parse(const char *filename,std::list<std::experimental::filesystem::path> *result);
};

#endif
