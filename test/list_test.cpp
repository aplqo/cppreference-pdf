#define BOOST_TEST_MODULE cppreference-test
#include<boost/test/unit_test.hpp>
#include"../include/list.h"
#include"../debug/debug.h"
#include<fstream>

namespace fs=std::filesystem;
using fs::path;
using fs::remove_all;
using fs::temp_directory_path;
using fs::absolute;
using fs::canonical;
using fs::create_directory;
using std::ofstream;
using std::ios;
using std::endl;

//test class
class list_test: public doc::list
{
public:
  list_test();
  void add(const path *p,unsigned int num);
  void Compare_test();
  void Remove_test();
  void Apply_test();
  void find_test();
};

struct list_fixture
{
  public:
    list_fixture();
    ~list_fixture();

    //test path
    const path dest=canonical(absolute(temp_directory_path()/"tmp-test"));
    //test files
    const path both[3]={dest/"include1.html",dest/"include2.html",dest/"include3.html"};
    const path include_1[2]={dest/"include1_1.html",dest/"include2_1.html"};
    const path include_2[2]={dest/"include1_2.html",dest/"include2_2.html"};
    const path exclude[2]={dest/"exclude1.html",dest/"exclude2.html"};
    //test_object:
    list_test list1,list2;
  private:
    static void create(const path *p,unsigned int num);
};
list_fixture::list_fixture()
{
  create_directory(dest);
  //create files
  create(both,3);
  create(include_1,2);
  create(include_2,2);
  create(exclude,2);
  //create object
  list1.add(both,3);
  list1.add(include_1,2);
  list2.add(both,3);
  list2.add(include_2,2);
}
list_fixture::~list_fixture()
{
  remove_all(dest);
}
void list_fixture::create(const path *p,unsigned int num)
{
  const path *end=p+num;
  for(auto i=p;i<end;i++)
  {
    ofstream of(*i,ios::out);
    of<<"Test file"<<endl;
    of.close();
  }
}
BOOST_FIXTURE_TEST_SUITE(test_list,list_fixture)
BOOST_AUTO_TEST_SUITE_END()
