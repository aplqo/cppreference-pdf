#define BOOST_TEST_MODULE cppreference-test
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include "../include/list.h"
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
namespace bdata=boost::unit_test::data;

namespace list_test
{
  //test class
  class test : public doc::list
  {
  public:
    test();
    void add(const path *p, unsigned int num);
    using doc::list::lst;
    using doc::list::find;
  };
  test::test()
  {
    lst = new std::list<path>;
  }
  void test::add(const path *p, unsigned int num)
  {
    const path *end = p + num;
    for (const path *i = p; i < end; i++)
    {
      lst->push_back(*i);
    }
  }

  struct data
  {
    //test path
    static const path dest;
    //test files
    static const path both[3];
    static const path include_1[2];
    static const path include_2[2];
    static const path exclude[2];
  };
  //test path
  const path data::dest = canonical(absolute(temp_directory_path() / "tmp-test"));
  //test files
  const path data::both[3] = {dest / "include1.html", dest / "include2.html", dest / "include3.html"};
  const path data::include_1[2] = {dest / "include1_1.html", dest / "include2_1.html"};
  const path data::include_2[2] = {dest / "include1_2.html", dest / "include2_2.html"};
  const path data::exclude[2] = {dest / "exclude1.html", dest / "exclude2.html"};

  struct fixture:public data
  {
  public:
    fixture();
    ~fixture();

    //test object
  private:
    static void create(const path *p, unsigned int num);
  };
  fixture::fixture()
  {
    create_directory(dest);
    //create files
    create(both, 3);
    create(include_1, 2);
    create(include_2, 2);
    create(exclude, 2);
  }
  fixture::~fixture()
  {
    remove_all(dest);
  }
  void fixture::create(const path *p, unsigned int num)
  {
    const path *end = p + num;
    for (auto i = p; i < end; i++)
    {
      ofstream of(*i, ios::out);
      of << "Test file" << endl;
      of.close();
    }
  }
}
BOOST_FIXTURE_TEST_SUITE(test_list, list_test::fixture)

BOOST_AUTO_TEST_CASE(dest)
{
  doc::list l;
}
BOOST_AUTO_TEST_CASE(isEmpty)
{
  doc::list l;
  BOOST_TEST(l.isEmpty());
}

BOOST_AUTO_TEST_SUITE_END()