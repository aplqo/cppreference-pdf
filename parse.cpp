#include<list>
#include<fstream>
#include<string>
#include<filesystem>
#include<gq/Document.h>
#include<gq/Node.h>

using std::filesystem::path;
using std::ifstream;
using std::string;
using std::getline;

namespace doc
{
	static inline void read(const char *filename,string *result)
	{
		ifstream i(filename);
		if(!i.is_open())
		{
			return;
		}
		string tmp;
		while(!i.eof())
		{
			getline(i,tmp);
			(*result)+=tmp;
			tmp.clear();
		}
	}
	void parse(const char *filename,std::list<path> *result)
	{
		string s;
		read(filename,&s);
		CDocument d;
		d.parse(s);
		CSelection sel=d.find("a");
		d.release();
		size_t num=sel.nodeNum();
		for(size_t i=0;i<num;i++)
		{
			CNode nod=sel.nodeAt(i);
			result->push_back(nod.attribute("href"));
		}
	}
}
