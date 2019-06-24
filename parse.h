#ifndef PARSE_H
#define PARSE_H

#include<list>
#include<experimental/filesystem>

namespace doc
{
    std::list<std::experimental::filesystem::path> parse(const char *filename);
};

#endif