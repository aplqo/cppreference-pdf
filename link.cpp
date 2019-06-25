#include<list>
#include<experimental/filesystem>
#include"list.h"
#include"parse.h"

namespace fs=std::experimental::filesystem;
using fs::path;
using fs::absolute;
using fs::exists;

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
		if(!exists(p))
		{
			return;
		}
		lst=new std::list<path>;
		lst->push_back(absolute(p));
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
		for(auto &i:(*links))
		{
			if(find(i))
			{
				links->remove(i);
				continue;
			}
			path p=toAbsolute(i);
			if(!exists(p))
			{
				links->remove(i);
				continue;
			}
			if(isFirst(i))
			{
				lst->insert(now,i);
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
		return absolute(p,it->parent_path());
	}
	inline bool link::isFirst(const path &p)
	{
		path dir=(it->parent_path())/(it->filename());
		return dir==(p.parent_path());
	}
}
