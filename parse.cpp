#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<filesystem>
#include<locale>
#include<gq/Document.h>
#include<gq/Node.h>

using std::filesystem::path;
using std::ifstream;
using std::stringstream;
using std::ios_base;
using std::string;
using std::locale;

namespace doc
{
	static const locale u8("en_US.UTF-8");
	static inline void read(const char *filename,string &s)
	{
		ifstream i(filename);
		i.seekg(2, ios_base::beg);
		if(!i.is_open())
		{
			return;
		}
		i.imbue(u8);
		stringstream buf;
		buf<<i.rdbuf();
		s=buf.str();
	}
	void parse(const char *filename,std::list<path> *result)
	{
		string s;
		read(filename,s);
		CDocument d;
		d.parse(s);
		CSelection sel=d.find("a");
		size_t num=sel.nodeNum();
		for(size_t i=0;i<num;i++)
		{
			CNode nod=sel.nodeAt(i);
			string tmp=nod.attribute("href");
			if(!tmp.empty())
			{
				result->push_back(tmp);
			}
		}
	}
}
