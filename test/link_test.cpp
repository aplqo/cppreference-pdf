#include "../include/link.h"
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using fs::path;
using std::list;
namespace tt = boost::test_tools;
namespace bdata = boost::unit_test::data;
using bdata::make;

namespace link_test
{
    struct file
    {
        const path& p;
        list<path> read, check;
    };
    std::ostream& operator<<(std::ostream& os, const file& f)
    {
        return (os << f.p << std::endl);
    }

    struct data
    {
        static const path tmp;
        static const path src;
        static const path dest;

        static const file files[];
    };
    const path data::tmp = fs::canonical(fs::absolute(fs::temp_directory_path()));
    const path data::src = path(SOURCE) / "test" / "data" / "link";
    const path data::dest = tmp / "tmp-test";
    const file data::files[] = {
        { dest / "single.html",
            { dest / "single.html", dest / "single" / "link2.html", dest / "single" / "link1.html", dest / "single" / "link3.html" },
            { dest / "single.html", dest / "single" / "link2.html", dest / "single" / "link1.html", dest / "single" / "link3.html" } },
        { dest / "check.html",
            { dest / "check.html",
                dest / "check" / "link1.html", dest / "check" / "link1" / "link1.html", dest / "check" / "link1" / "link2.html",
                dest / "check" / "link2.html", dest / "check" / "link2" / "link2.html" },
            { dest / "check.html",
                dest / "check" / "link1.html",
                dest / "check" / "link1" / "link1.html",
                dest / "check" / "link2" / "check.html", dest / "check" / "link1" / "check.html", dest / "check" / "link2" / "check" / "link.html",
                dest / "check" / "link1" / "link2.html",
                dest / "check" / "link2.html", dest / "check" / "link2" / "link2.html" } }
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

    class test : public doc::link
    {
    public:
        test(const path& p)
            : doc::link(p){};
        using doc::link::lst;
    };
}

namespace lt = link_test;
BOOST_FIXTURE_TEST_SUITE(test_link, lt::fixture)

BOOST_DATA_TEST_CASE(read, make(lt::data::files), file)
{
    lt::test t(file.p);
    t.Read();
    BOOST_TEST(*(t.lst) == file.read, tt::per_element());
}
BOOST_DATA_TEST_CASE(check, make(lt::data::files), file)
{
    lt::test t(file.p);
    t.Read();
    t.Check();
    BOOST_TEST(*(t.lst) == file.check, tt::per_element());
}
BOOST_DATA_TEST_CASE(release, make(lt::data::files), file)
{
    lt::test t(file.p);
    t.Read();
    t.Check();
    t.Release();
}

BOOST_AUTO_TEST_SUITE_END()