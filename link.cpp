#include<list>
#include<filesystem>
#include"list.h"
#include"parse.h"

namespace fs=std::filesystem;
using fs::path;
using fs::absolute;
using fs::exists;
using fs::current_path;
using fs::canonical;

namespace doc
{
	class link :public list
	{
	public:
		link(const path &p);
		link(std::list<path>::iterator i);
		void Read();
		bool Check();
		void Release();
		~link();
	private:
		inline path toAbsolute(const path &p);
		inline bool isFirst(const path &p); //check if a file should be included in the first time 
		/*---var---*/
		std::list<path> *links;
		
		static link* root;
		std::list<link> child;
		
		std::list<path>::iterator it;
	};
	link* link::root=nullptr;
	link::link(const path &p)
	{
		root=this;
		this->isBase=false;
		links=nullptr;
		lst=new std::list<path>;
		lst->push_back(canonical(absolute(p)));
		it=lst->begin();
	}
	link::link(std::list<path>::iterator i)
	{
		links=nullptr;
		this->isBase=false;
		this->it=i;
	}
	void link::Read()
	{
		links=new std::list<path>;
		parse(it->c_str(),links);
		std::list<path>::iterator now=it;
		for(auto i=links->begin();i!=(links->end());i++)
		{
			auto e=[l=this->lst](std::list<path>::iterator pos)->std::list<path>::iterator{
				auto j=pos;
				pos++;
				l->erase(j);
				pos--;
				return pos;
				};
			if(find(*i))
			{
				e(i);
				continue;
			}
			path p=toAbsolute(*i);
			if(!exists(p))
			{
				e(i);
				continue;
			}
			if(isFirst(*i))
			{
				lst->insert(now,*i);
				child.push_back(now);
				now++;
				continue;
			}
		}
	}
	bool link::Check()
	{
		bool result=true;
		std::list<path>::iterator now=it;
		std::list<link>::iterator c_now=child.begin();
		for(auto &j: *links)
		{
			if(!find(j))
			{
				lst->insert(now,j);
				result=false;
				child.insert(c_now,now);
				c_now->Read();
			}
			now++;
			c_now++;
		}
		for (auto &i : child)
		{
			result&=i.Check();
		}
		return result;
	}
	void link::Release()
	{
		delete links;
		links=nullptr;
		child.clear();
	}
	link::~link()
	{
		delete links;
		if(root==this)
		{
			delete lst;
		}
	}
	inline path link::toAbsolute(const path &p)
	{
		path res;
		path cu=current_path();
		current_path(it->parent_path());
		res=absolute(p);
		res=canonical(res);
		current_path(cu);
		return res;
	}
	inline bool link::isFirst(const path &p)
	{
		path dir=(it->parent_path())/(it->filename());
		return dir==(p.parent_path());
	}
}
