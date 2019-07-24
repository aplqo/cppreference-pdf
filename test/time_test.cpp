#include "../include/time.h"
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

using std::string;
namespace fs = std::filesystem;
using fs::path;
namespace bdata = boost::unit_test::data;

namespace time_test
{
    struct data
    {
        static const path tmp;
        static const path dest;
        static const path src;

        static const path file[6];
        static const path js_t;
    };
    const path data::tmp = fs::canonical(fs::absolute(fs::temp_directory_path()));
    const path data::dest = tmp / "tmp-test";
    const path data::src = path(SOURCE) / "test" / "data" / "time";
    const path data::file[6] = {
        dest / "t1.html", dest / "t2.html", dest / "t3.html",
        dest / "t4.html", dest / "t5.html", dest / "t6.html"
    };
    const path data::js_t = dest / "js" / "time.js";

    class dataset
    {
    public:
        enum
        {
            arity = 1
        };

        struct iterator
        {
            iterator()
                : time(5){};

            string operator*() const;
            void operator++();

        private:
            void create(const path& p, const unsigned int time) const;
            unsigned int time;

            static constexpr unsigned int step = 80;
            static constexpr unsigned int dif = 2;
            static constexpr unsigned int num = 2;

            static const path out[num * 2 + 1];
        };

        dataset(){};
        bdata::size_t size() const { return s; };
        iterator begin() const { return iterator(); };

    private:
        static constexpr unsigned int s = 5;
    };
    const path dataset::iterator::out[] = {
        data::dest / "js" / "time1.js", data::dest / "js" / "time2.js",
        data::dest / "js" / "time3.js", data::dest / "js" / "time4.js",
        data::dest / "js" / "time5.js"
    };
    void dataset::iterator::create(const path& p, const unsigned int ti) const
    {
        string in;
        {
            std::ifstream i(data::js_t, std::ios::in);
            std::stringstream s;
            s << i.rdbuf();
            in = s.str();
            i.close();
        }
        string t = std::to_string(ti);
        std::ofstream of(p, std::ios::out);
        of << "var time=" << t << ";" << std::endl;
        of << in << std::endl;
        of.close();
    }
    string dataset::iterator::operator*() const
    {
        unsigned int j = time;
        const path* p = out;
        for (unsigned int i = num; i > 0; i--, p++)
        {
            create(*p, j);
            j -= dif;
        }
        j = time - dif;
        for (unsigned int i = num + 1; i > 0; i--, p++)
        {
            create(*p, j);
            j += dif;
        }
        return std::to_string(time);
    }
    void dataset::iterator::operator++()
    {
        time += step;
    }

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

    class tlist : public doc::list, public data
    {
    public:
        tlist();
    };
    tlist::tlist()
    {
        lst = new std::list<path>;
        for (auto& i : file)
        {
            lst->push_back(i);
        }
    }
}
namespace ttest = time_test;

//registering dataset
namespace boost
{
    namespace unit_test
    {
        namespace data
        {
            namespace monomorphic
            {
                template <>
                struct is_dataset<ttest::dataset> : boost::mpl::true_
                {
                };
            }
        }
    }
}

BOOST_FIXTURE_TEST_SUITE(test_time, ttest::fixture)

BOOST_DATA_TEST_CASE(time, ttest::dataset(), res)
{
    ttest::tlist l;
    string s = doc::time(l);
    BOOST_TEST(s == res);
}

BOOST_AUTO_TEST_SUITE_END()