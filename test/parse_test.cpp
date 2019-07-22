#include "../include/parse.h"
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using fs::path;
namespace tt = boost::test_tools;
namespace bdata = boost::unit_test::data;

namespace parse_test
{
    struct file
    {
        const path p;
        const std::list<path> link;
    };
    std::ostream& operator<<(std::ostream& os, const file& f)
    {
        return os << f.p << std::endl;
    }

    struct data
    {
        static const path tmp, src, dest;

        static const file files[];
    };
    const path data::tmp = fs::canonical(fs::absolute(fs::temp_directory_path()));
    const path data::dest = tmp / "tmp-test";
    const path data::src = path(SOURCE) / "test" / "data" / "parse";

    const file data::files[] = {
        { dest / "simple.html", { "link1", "in-table", "with-style" } },
        { dest / "args.html", { "../t", "arg", "encode-args", "section" } },
        { dest / "encode.html", { "./te", "encode=one+", "encode=many++" } },
        { dest / "contentsub.html", { "Normal1", "normal2" } },
        { dest / "navbar.html", { "normal1", "normal2" } }
    };

    class fixture : public data
    {
    public:
        fixture();
        ~fixture();
    };
    fixture::fixture()
    {
        fs::copy(src, dest, fs::copy_options::recursive);
    }
    fixture::~fixture()
    {
        fs::remove_all(dest);
    }
}

namespace pt = parse_test;

BOOST_FIXTURE_TEST_SUITE(test_parse, pt::fixture)

BOOST_DATA_TEST_CASE(parse, bdata::make(pt::data::files), f)
{
    std::list<path> l;
    const std::list<path>& res = f.link;
    doc::parse(f.p.c_str(), &l);
    BOOST_TEST(l == res, tt::per_element());
}

BOOST_AUTO_TEST_SUITE_END()