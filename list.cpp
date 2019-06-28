#include<list>
#include<filesystem>

using std::filesystem::path;

namespace doc
{
	class list
	{
	public:
		list();
		void Compare(const list &l,list *result);
		void Remove(const list &l);
		bool isEmpty();
		bool Apply(bool func(const path &p,void *par),void *par);
		~list();
	protected:
		bool find(const path &p);
		std::list<path> *lst;
		bool isBase;
	};
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
			if(i==p)
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
	bool list::Apply(bool func(const path &p,void *par),void *par)
	{
		bool result=true;
		if(lst==nullptr)
		{
			return true;
		}
		for(auto &i : *lst)
		{
			result&=func(i,par);
		}
		return result;
	}
}
