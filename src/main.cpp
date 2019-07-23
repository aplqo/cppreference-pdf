#include "../include/filelist.h"
#include "../include/link.h"
#include "../include/list.h"
#include "../include/log.h"
#include "../include/pdf.h"

//debug:
#include "../debug/debug.h"

using std::cout;
using std::endl;
namespace fs = std::filesystem;
using std::filesystem::exists;
using std::filesystem::path;

namespace doc
{
    inline void usage()
    {
        cout << "usage: doc [firstfile] [outputfile]" << endl;
        cout << "Convert cppreference doc to pdf" << endl;
    }
}
int main(int argc, char* argv[])
{
    auto toAbs = [](const char* p) -> path {
        return fs::canonical(fs::absolute(path(p)));
    };
    if (argc < 3)
    {
        doc::usage();
        return 0;
    }
    const path first = toAbs(argv[1]);
    const path current = fs::current_path();

    doc::debug("Current", current);

    if (!exists(first))
    {
        doc::error("Can't find first file");
        return -1;
    }

    doc::info("Generating link list...");
    doc::link lnk(first);
    lnk.Read();
    while (!lnk.Check())
        ;

    fs::current_path(current);
    doc::log(lnk, "links.log", argv[2]);

    doc::info("Checking if every file is included...");
    {
        doc::filelist flist(first);
        doc::log(flist, "filelist.log", argv[2]);
        doc::list diff;
        lnk.Compare(flist, &diff);
        {
            path p = (path(argv[2]).parent_path()) / "ignore.txt";
            if (exists(p))
            {
                doc::filelist ign(p.c_str());
                diff.Remove(ign);
            }
            else
            {
                doc::warning("Can't find ignore.txt");
            }
        }
        if (!diff.isEmpty())
        {
            doc::error("These file aren't included:");
            auto cb = [](const path& p, void* par) { cout << "\t" << p << endl; };
            diff.Apply(cb, nullptr);
            doc::log(diff, "Missing.log", argv[2]);
            return -1;
        }
    }

    doc::pdf(lnk, argv[2]);
    return 0;
}
