#define BOOST_TEST_MODULE cppreference - test
#include "../include/list.h"
#include <boost/test/data/test_case.hpp>
#include <boost/test/included/unit_test.hpp>
#include <fstream>

namespace fs = std::filesystem;
using fs::absolute;
using fs::canonical;
using fs::create_directory;
using fs::path;
using fs::remove_all;
using fs::temp_directory_path;
using std::endl;
using std::ios;
using std::ofstream;
namespace bdata = boost::unit_test::data;
namespace tt = boost::test_tools;

namespace list_test
{
    struct data
    {
        static const path tmp;
        //test path
        static const path dest;
        //test files
        static const path both[3];
        static const path include[2][3];
        static const path exclude[2];
        static const unsigned int num[];
    };
    const path data::tmp = canonical(absolute(temp_directory_path()));
    //test path
    const path data::dest = tmp / "tmp-test";
    //test files
    const path data::both[3] = { dest / "include1.html", dest / "include2.html", dest / "include3.html" };
    const path data::include[2][3] = {
        { dest / "include1_1.html", dest / "include2_1.html" },
        { dest / "include1_2.html", dest / "include2_2.html", dest / "include2_3.html" }
    };
    const path data::exclude[2] = { dest / "exclude1.html", dest / "exclude2.html" };
    const unsigned int data::num[] = { 2, 3 };

    //test class
    class test : public doc::list
    {
    public:
        test() = default;
        test(const path p[], unsigned int num);
        void add(const path* p, unsigned int num);

        using doc::list::find;
        using doc::list::lst;
    };
    test::test(const path p[], unsigned int num)
    {
        lst = new std::list<path>;
        add(data::both, 3);
        add(p, num);
    }
    void test::add(const path* p, unsigned int num)
    {
        const path* end = p + num;
        for (const path* i = p; i < end; i++)
        {
            lst->push_back(*i);
        }
    }

    struct fixture : public data
    {
    public:
        fixture();
        ~fixture();

        //test object
    private:
        static void create(const path* p, unsigned int num);
    };
    fixture::fixture()
    {
        create_directory(dest);
        //create files
        create(both, 3);
        create(include[0], num[0]);
        create(include[1], num[1]);
        create(exclude, 2);
    }
    fixture::~fixture()
    {
        remove_all(dest);
    }
    void fixture::create(const path* p, unsigned int num)
    {
        const path* end = p + num;
        for (auto i = p; i < end; i++)
        {
            ofstream of(*i, ios::out);
            of << "Test file" << endl;
            of.close();
        }
    }
}
namespace lt = list_test;
BOOST_FIXTURE_TEST_SUITE(test_list, list_test::fixture)

BOOST_AUTO_TEST_CASE(dest)
{
    doc::list l;
}
BOOST_DATA_TEST_CASE(compare, (bdata::make(0, 1) * bdata::make(0, 1)) ^ bdata::make(-1, 1, 0, -1), list1, list2, res)
{
    list_test::test t1(lt::data::include[list1], lt::data::num[list1]), t2(lt::data::include[list2], lt::data::num[list2]);
    list_test::test l;
    t1.Compare(t2, &l);
    if (res == -1)
    {
        BOOST_TEST(*(l.lst) == std::list<path>{}, tt::per_element());
    }
    else
    {
        BOOST_CHECK_EQUAL_COLLECTIONS(l.lst->begin(), l.lst->end(), lt::data::include[res], lt::data::include[res] + lt::data::num[res]);
    }
}
BOOST_DATA_TEST_CASE(remove, (bdata::make(0, 1) * bdata::make(0, 1)) ^ bdata::make(-1, 0, 1, -1), list1, list2, res)
{
    list_test::test t1(lt::data::include[list1], lt::data::num[list1]), t2(lt::data::include[list2], lt::data::num[list2]);
    t1.Remove(t2);
    std::list<path>& l = *(t1.lst);
    const path* r = lt::data::include[res];
    if (res == -1)
    {
        BOOST_TEST(l == std::list<path>{}, tt::per_element());
    }
    else
    {
        BOOST_CHECK_EQUAL_COLLECTIONS(l.begin(), l.end(), r, r + lt::data::num[res]);
    }
}

BOOST_AUTO_TEST_SUITE(isEmpty)
BOOST_AUTO_TEST_CASE(empty)
{
    doc::list l;
    BOOST_TEST(l.isEmpty());
}
BOOST_AUTO_TEST_CASE(not_empty)
{
    lt::test l(lt::data::include[0], lt::data::num[0]);
    BOOST_TEST(!l.isEmpty());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Apply)
auto cb = [](const path& p, void* var) {
    std::list<path>* l = reinterpret_cast<std::list<path>*>(var);
    l->push_back(p);
};
BOOST_AUTO_TEST_CASE(not_empty)
{
    lt::test t(lt::data::include[0], lt::data::num[0]);
    std::list<path> p;
    t.Apply(cb, &p);
    BOOST_TEST(p == *(t.lst), tt::per_element());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_DATA_TEST_CASE(find,
    bdata::make(lt::data::both) * bdata::make(true) + bdata::make(lt::data::exclude) * bdata::make(false), elem, res)
{
    lt::test t(lt::data::include[0], lt::data::num[0]);
    if (res)
    {
        BOOST_TEST(t.find(elem));
    }
    else
    {
        BOOST_TEST(!t.find(elem));
    }
}

BOOST_AUTO_TEST_SUITE_END()
