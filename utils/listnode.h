#ifndef _LISTNODE_H_
#define _LISTNODE_H_

template <class T>
class ListNode
{
public:
	ListNode(T);
	T& get_data();
	void set_next(ListNode<T> *);
	ListNode<T> *get_next();

private:
	T _data;
	ListNode<T> *_next;
};

#include "listnode.cpp"
#endif
