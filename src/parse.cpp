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
	static void get_link(CDocument &doc,const char *key,void func(const string &str,void *par),void *par)
	{
		CSelection s=doc.find(key);
		CSelection link=s.find("a");
		size_t num=link.nodeNum();
		for(size_t i=0;i<num;i++)
		{
			CNode nod=link.nodeAt(i);
			string tmp=nod.attribute("href");
			if(!tmp.empty())
			{
				func(tmp,par);
			}
		}
	}
	void parse(const char *filename,std::list<path> *result)
	{
		std::list<path> all;
		std::list<path>::size_type exclude=0;

		auto count=[](const string &str,void *par)->void{
			std::list<path>::size_type &p=*reinterpret_cast<std::list<path>::size_type*>(par);
			p++;
		};
		auto add=[](const string &str,void *par)->void{
			std::list<path> *l=reinterpret_cast<std::list<path>*>(par);
			l->push_back(str);
		};

		string s;
		read(filename,s);
		CDocument d;
		d.parse(s);
		get_link(d,"a",add,&all);
		get_link(d,"div[id=\"contentSub\"]",count,&exclude);
		get_link(d,"div[class=\"t-navbar\"]",count,&exclude);
		auto all_num=all.size();
		auto it=all.begin();
		for(size_t i=0;i<exclude;i++) it++;
		for(auto i=exclude;i<all_num;i++,it++)
		{
			result->push_back(*it);
		}
	}
}
