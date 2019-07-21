#include "../include/filelist.h"
#include <algorithm>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <filesystem>
#include <fstream>

using doc::filelist;
using std::endl;
using std::find;
using std::ios;
using std::ofstream;
namespace fs = std::filesystem;
using fs::absolute;
using fs::canonical;
using fs::create_directory;
using fs::current_path;
using fs::path;
using fs::remove_all;
using fs::temp_directory_path;
namespace tt = boost::test_tools;
namespace bdata = boost::unit_test::data;

namespace filelist_test
{
    struct data
    {
        static const path tmp;
        static const path dest;

        static const path dirs[4];
        static const path files[8];

        static const path lists[2];
        static const char* s[];
    };
    const path data::tmp = canonical(absolute(temp_directory_path()));
    const path data::dest = tmp / "test-tmp";

    const path data::dirs[4] = { dest / "dir1", dest / "dir2", dest / "dir1" / "dir1.1", dest / "dir1" / "dir1.2" };
    const path data::files[8] = {
        dest / "dir1.html", dest / "file2",
        dirs[0] / "file1", dirs[0] / "file2",
        dirs[2] / "file1", dirs[2] / "file2",
        dirs[3] / "file1", dirs[3] / "file2"
    };
    const path data::lists[2] = { dest / "normal.txt", dest / "emptyline.txt" };
    const char* data::s[] = {
        files[0].c_str(),
        files[2].c_str(), files[3].c_str(),
        files[4].c_str(), files[5].c_str(),
        files[6].c_str(), files[7].c_str()
    };

    class fixture : public data
    {
    public:
        fixture();
        ~fixture();
    };
    fixture::fixture()
    {
        create_directory(dest);
        for (auto& i : dirs)
        {
            create_directory(i);
        }

        for (auto& i : files)
        {
            ofstream of(i, ios::out);
            of << "Test file" << endl;
            of.close();
        }

        ofstream of(lists[0], ios::out);
        for (auto& i : s)
        {
            of << i << endl;
        }
        of.close();

        ofstream e(lists[1], ios::out);
        for (auto& i : s)
        {
            e << i << endl
              << endl;
        }
        e.close();

        current_path(data::dest);
    }
    fixture::~fixture()
    {
        remove_all(dest);
    }

    class test : public filelist
    {
    public:
        test(const char* s)
            : filelist(s){};
        test(const path& p)
            : filelist(p){};
        using list::lst;
    };
}
namespace ft = filelist_test;
BOOST_FIXTURE_TEST_SUITE(filelist_test, filelist_test::fixture)

BOOST_AUTO_TEST_CASE(from_path)
{
    ft::test t(ft::data::files[0]);
    t.lst->sort();

    std::list<path> exp;
    for (auto& i : ft::data::files)
    {
        exp.push_back(i);
    }
    exp.remove(ft::data::files[1]);
    exp.sort();

    BOOST_TEST(*(t.lst) == exp, tt::per_element());
}

BOOST_DATA_TEST_CASE(from_file, bdata::make(ft::data::lists), file)
{
    ft::test t(file.c_str());
    t.lst->sort();

    std::list<path> res;
    for (auto& i : ft::data::files)
    {
        res.push_back(i);
    }
    res.remove(data::files[1]);
    res.sort();

    BOOST_TEST(*(t.lst) == res, tt::per_element());
}

BOOST_AUTO_TEST_SUITE_END()