#pragma once
#include "Node.h"
#include <list>
#include <string>

class ListIterator {
public:
	Node* NodeList;

	ListIterator();
	ListIterator(Node* n);

	void init(Node* n);

	bool check_current();
	bool check_next();

	void go_next();
	int  get_value();

	Node* del_cur(Node* n);

	Node* insert(int val);

};


ListIterator::ListIterator()
{
	NodeList = nullptr;
}

inline ListIterator::ListIterator(Node* n)
{
	if (n != nullptr)
	{
		NodeList = n;
	}
}

inline void ListIterator::init(Node* n)
{
	if (n != nullptr)
	{
		NodeList = n;
	}
}

inline bool ListIterator::check_current()
{
	if (NodeList != nullptr)
	{
		return true;
	}
	else { return false; }
}

inline bool ListIterator::check_next()
{
	if (NodeList->Next != nullptr)
	{
		return true;
	}
	else { return false; }
}

inline void ListIterator::go_next()
{
	if (check_current())
	{
		if (check_next())
		{
			NodeList = NodeList->Next;
		}
	}
}

inline int ListIterator::get_value()
{
	if (check_current())
	{
		return NodeList->data;
	}
}

inline Node* ListIterator::del_cur(Node* n)
{
	NodeList = n;
	Node* tmp = NodeList;
	
	NodeList = NodeList->Next;
	delete tmp;
	return NodeList;
}

inline Node* ListIterator::insert(int val)
{
	if (check_current())
	{
		NodeList = NodeList->Next;
		NodeList->data = val;
		return NodeList;
	}
	return nullptr;
}
