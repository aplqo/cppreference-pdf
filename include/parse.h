#ifndef PARSE_H
#define PARSE_H

#include <filesystem>
#include <list>

namespace doc
{
    void parse(const char* filename, std::list<std::filesystem::path>* result);
};

#endif
