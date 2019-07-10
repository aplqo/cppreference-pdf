#include"../include/list.h"

using std::filesystem::path;
using std::filesystem::equivalent;

namespace doc
{
	list::list()
	{
		isBase=true;
		lst=nullptr;
	}
	void list::Compare(const list &l,list *result)
	{
		if((this->lst)==nullptr||result==nullptr)
		{
			return;
		}
		if(result->lst==nullptr)
		{
			result->lst=new std::list<path>;
		}
		std::list<path> *res=result->lst;
		for(auto &i: *(l.lst))
		{
			if(!find(i))
			{
				res->push_back(i);
			}
		}
	}
	void list::Remove(const list &l)
	{
		if(lst==nullptr||l.lst==nullptr)
		{
			return;
		}
		for(auto &i: *(l.lst))
		{
			lst->remove(i);
		}
	}
	bool list::isEmpty()
	{
		if(lst==nullptr)
		{
			return true;
		}
		return lst->empty();
	}
	bool list::find(const path &p)
	{
		for(auto &i: *lst)
		{
			if(equivalent(i,p))
			{
				return true;
			}
		}
		return false;
	}
	list::~list()
	{
		if(isBase)
		{
			delete lst;
			lst=nullptr;
		}
	}
	void list::Apply(void func(const path &p,void *par),void *par)
	{
		if(lst==nullptr)
		{
			return;
		}
		for(auto &i : *lst)
		{
			func(i,par);
		}
	}
}
