#ifndef LIST_H
#define LIST_H

#include<list>
#include<filesystem>
namespace doc
{
	class list
	{
	public:
		list();
		void Compare(const list &l,list *result);
		void Remove(const list &l);
		bool isEmpty();
		~list();
	protected:
		bool find(const std::filesystem::path &p);
		std::list<std::filesystem::path> *lst;
		bool isBase;
	};
}

#endif
