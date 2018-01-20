template <class T>
ListNode<T>::ListNode(
	T data) : _data(data), _next(NULL)
{
}

template <class T>
T& ListNode<T>::get_data()
{
	return _data;
}

template <class T>
void ListNode<T>::set_next(
	ListNode<T> *next)
{
	_next = next;
}

template <class T>
ListNode<T> *ListNode<T>::get_next()
{
	return _next;
}
